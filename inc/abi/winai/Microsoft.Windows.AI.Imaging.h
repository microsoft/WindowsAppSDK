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
#ifndef __microsoft2Ewindows2Eai2Eimaging_h__
#define __microsoft2Ewindows2Eai2Eimaging_h__
#ifndef __microsoft2Ewindows2Eai2Eimaging_p_h__
#define __microsoft2Ewindows2Eai2Eimaging_p_h__


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
#if !defined(MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION)
#define MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION)

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
#include "Microsoft.Graphics.Imaging.h"
#include "Microsoft.Windows.AI.h"
#include "Microsoft.Windows.AI.ContentSafety.h"
#include "Windows.Graphics.h"
#include "Windows.Graphics.Imaging.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageDescriptionGenerator;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator ABI::Microsoft::Windows::AI::Imaging::IImageDescriptionGenerator

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageDescriptionGeneratorStatics;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics ABI::Microsoft::Windows::AI::Imaging::IImageDescriptionGeneratorStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageDescriptionResult;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult ABI::Microsoft::Windows::AI::Imaging::IImageDescriptionResult

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageObjectExtractor;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor ABI::Microsoft::Windows::AI::Imaging::IImageObjectExtractor

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageObjectExtractorHint;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint ABI::Microsoft::Windows::AI::Imaging::IImageObjectExtractorHint

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageObjectExtractorHintFactory;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory ABI::Microsoft::Windows::AI::Imaging::IImageObjectExtractorHintFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageObjectExtractorStatics;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics ABI::Microsoft::Windows::AI::Imaging::IImageObjectExtractorStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageObjectRemover;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover ABI::Microsoft::Windows::AI::Imaging::IImageObjectRemover

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageObjectRemoverStatics;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics ABI::Microsoft::Windows::AI::Imaging::IImageObjectRemoverStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageScaler;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler ABI::Microsoft::Windows::AI::Imaging::IImageScaler

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IImageScalerStatics;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics ABI::Microsoft::Windows::AI::Imaging::IImageScalerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IRecognizedLine;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine ABI::Microsoft::Windows::AI::Imaging::IRecognizedLine

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IRecognizedText;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText ABI::Microsoft::Windows::AI::Imaging::IRecognizedText

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface IRecognizedWord;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord ABI::Microsoft::Windows::AI::Imaging::IRecognizedWord

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface ITextRecognizer;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer ABI::Microsoft::Windows::AI::Imaging::ITextRecognizer

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    interface ITextRecognizerStatics;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics ABI::Microsoft::Windows::AI::Imaging::ITextRecognizerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    class ImageDescriptionGenerator;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("1ebb676d-c291-55ef-8d3f-847ff701ef72"))
IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionGenerator*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionGenerator*, ABI::Microsoft::Windows::AI::Imaging::IImageDescriptionGenerator*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.AI.Imaging.ImageDescriptionGenerator>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionGenerator*> __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("1e25454f-c3e0-526a-8376-56b637b350d0"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionGenerator*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionGenerator*, ABI::Microsoft::Windows::AI::Imaging::IImageDescriptionGenerator*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.AI.Imaging.ImageDescriptionGenerator>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionGenerator*> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    class ImageObjectExtractor;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("0f52d3c6-6444-5bc9-a7f2-b8a6006934aa"))
IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::ImageObjectExtractor*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageObjectExtractor*, ABI::Microsoft::Windows::AI::Imaging::IImageObjectExtractor*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.AI.Imaging.ImageObjectExtractor>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::ImageObjectExtractor*> __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("0beeabbb-8fb8-519c-a098-140cfe7a77d4"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::ImageObjectExtractor*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageObjectExtractor*, ABI::Microsoft::Windows::AI::Imaging::IImageObjectExtractor*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.AI.Imaging.ImageObjectExtractor>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::ImageObjectExtractor*> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    class ImageObjectRemover;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("2ae992c6-ca47-51bc-8a4d-65fd3b2a2ec2"))
IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::ImageObjectRemover*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageObjectRemover*, ABI::Microsoft::Windows::AI::Imaging::IImageObjectRemover*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.AI.Imaging.ImageObjectRemover>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::ImageObjectRemover*> __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("0e698b30-7d04-518e-8570-56f2eae55173"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::ImageObjectRemover*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageObjectRemover*, ABI::Microsoft::Windows::AI::Imaging::IImageObjectRemover*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.AI.Imaging.ImageObjectRemover>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::ImageObjectRemover*> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    class ImageScaler;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("afbdba2c-fa3c-551c-8570-350aae1c53ab"))
IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::ImageScaler*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageScaler*, ABI::Microsoft::Windows::AI::Imaging::IImageScaler*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.AI.Imaging.ImageScaler>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::ImageScaler*> __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("58962921-0a74-5f0d-b231-d494d294d2cc"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::ImageScaler*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageScaler*, ABI::Microsoft::Windows::AI::Imaging::IImageScaler*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.AI.Imaging.ImageScaler>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::ImageScaler*> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    class RecognizedText;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("3103ec71-2340-5b2b-8833-cc4ed639e936"))
IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::RecognizedText*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::RecognizedText*, ABI::Microsoft::Windows::AI::Imaging::IRecognizedText*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.AI.Imaging.RecognizedText>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::RecognizedText*> __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("27584192-a176-5f6e-a6e0-e769be5de471"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::RecognizedText*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::RecognizedText*, ABI::Microsoft::Windows::AI::Imaging::IRecognizedText*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.AI.Imaging.RecognizedText>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::RecognizedText*> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    class TextRecognizer;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("740b5d43-1472-53d9-92ec-8465f678d0c3"))
IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::TextRecognizer*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::TextRecognizer*, ABI::Microsoft::Windows::AI::Imaging::ITextRecognizer*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.AI.Imaging.TextRecognizer>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Windows::AI::Imaging::TextRecognizer*> __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("9aa12e4e-55af-531f-bff7-846f2d0b42d6"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::TextRecognizer*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::TextRecognizer*, ABI::Microsoft::Windows::AI::Imaging::ITextRecognizer*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.AI.Imaging.TextRecognizer>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::TextRecognizer*> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                class AIFeatureReadyResult;
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                interface IAIFeatureReadyResult;
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult ABI::Microsoft::Windows::AI::IAIFeatureReadyResult

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__

#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_USE
#define DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("ceea7604-5166-549f-8844-03192865a975"))
IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::AI::AIFeatureReadyResult*, double> : IAsyncOperationWithProgressCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::AIFeatureReadyResult*, ABI::Microsoft::Windows::AI::IAIFeatureReadyResult*>, double>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationWithProgressCompletedHandler`2<Microsoft.Windows.AI.AIFeatureReadyResult, Double>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::AI::AIFeatureReadyResult*, double> __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_t;
#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double ABI::Windows::Foundation::__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_USE */

#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_USE
#define DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("39c32af0-c9b4-595f-9e9b-c6c289ad9ea1"))
IAsyncOperationWithProgress<ABI::Microsoft::Windows::AI::AIFeatureReadyResult*, double> : IAsyncOperationWithProgress_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::AIFeatureReadyResult*, ABI::Microsoft::Windows::AI::IAIFeatureReadyResult*>, double>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperationWithProgress`2<Microsoft.Windows.AI.AIFeatureReadyResult, Double>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgress<ABI::Microsoft::Windows::AI::AIFeatureReadyResult*, double> __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_t;
#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double ABI::Windows::Foundation::__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_USE */

#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_USE
#define DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("5b37e602-8caa-581f-9ece-5dc72ab6ae7e"))
IAsyncOperationProgressHandler<ABI::Microsoft::Windows::AI::AIFeatureReadyResult*, double> : IAsyncOperationProgressHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::AIFeatureReadyResult*, ABI::Microsoft::Windows::AI::IAIFeatureReadyResult*>, double>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationProgressHandler`2<Microsoft.Windows.AI.AIFeatureReadyResult, Double>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationProgressHandler<ABI::Microsoft::Windows::AI::AIFeatureReadyResult*, double> __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_t;
#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double ABI::Windows::Foundation::__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_USE */

#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    class ImageDescriptionResult;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_USE
#define DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("253bf69f-d270-57d8-a287-2a6d1b234353"))
IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionResult*, HSTRING> : IAsyncOperationWithProgressCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionResult*, ABI::Microsoft::Windows::AI::Imaging::IImageDescriptionResult*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationWithProgressCompletedHandler`2<Microsoft.Windows.AI.Imaging.ImageDescriptionResult, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionResult*, HSTRING> __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_t;
#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING ABI::Windows::Foundation::__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_USE
#define DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("cb8eead4-f793-58c5-96cc-08b56d595f39"))
IAsyncOperationWithProgress<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionResult*, HSTRING> : IAsyncOperationWithProgress_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionResult*, ABI::Microsoft::Windows::AI::Imaging::IImageDescriptionResult*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperationWithProgress`2<Microsoft.Windows.AI.Imaging.ImageDescriptionResult, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgress<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionResult*, HSTRING> __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_t;
#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING ABI::Windows::Foundation::__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_USE
#define DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("f09f3cdf-54d7-52ee-b4af-f27111ed1625"))
IAsyncOperationProgressHandler<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionResult*, HSTRING> : IAsyncOperationProgressHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionResult*, ABI::Microsoft::Windows::AI::Imaging::IImageDescriptionResult*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationProgressHandler`2<Microsoft.Windows.AI.Imaging.ImageDescriptionResult, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationProgressHandler<ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionResult*, HSTRING> __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_t;
#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING ABI::Windows::Foundation::__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_USE */

#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Windows {
        namespace Graphics {
            typedef struct PointInt32 PointInt32;
        } /* Graphics */
    } /* Windows */
} /* ABI */

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#ifndef DEF___FIIterator_1_Windows__CGraphics__CPointInt32_USE
#define DEF___FIIterator_1_Windows__CGraphics__CPointInt32_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("c4c6f428-e11f-5266-a012-783e25ad266f"))
IIterator<struct ABI::Windows::Graphics::PointInt32> : IIterator_impl<struct ABI::Windows::Graphics::PointInt32>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Graphics.PointInt32>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<struct ABI::Windows::Graphics::PointInt32> __FIIterator_1_Windows__CGraphics__CPointInt32_t;
#define __FIIterator_1_Windows__CGraphics__CPointInt32 ABI::Windows::Foundation::Collections::__FIIterator_1_Windows__CGraphics__CPointInt32_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Windows__CGraphics__CPointInt32_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#ifndef DEF___FIIterable_1_Windows__CGraphics__CPointInt32_USE
#define DEF___FIIterable_1_Windows__CGraphics__CPointInt32_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("5802f68e-f696-5c18-9f52-169f079dbba3"))
IIterable<struct ABI::Windows::Graphics::PointInt32> : IIterable_impl<struct ABI::Windows::Graphics::PointInt32>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Graphics.PointInt32>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<struct ABI::Windows::Graphics::PointInt32> __FIIterable_1_Windows__CGraphics__CPointInt32_t;
#define __FIIterable_1_Windows__CGraphics__CPointInt32 ABI::Windows::Foundation::Collections::__FIIterable_1_Windows__CGraphics__CPointInt32_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Windows__CGraphics__CPointInt32_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

namespace ABI {
    namespace Windows {
        namespace Graphics {
            typedef struct RectInt32 RectInt32;
        } /* Graphics */
    } /* Windows */
} /* ABI */

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#ifndef DEF___FIIterator_1_Windows__CGraphics__CRectInt32_USE
#define DEF___FIIterator_1_Windows__CGraphics__CRectInt32_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("1abdf3f6-23f1-55ad-babd-f4cd908406e7"))
IIterator<struct ABI::Windows::Graphics::RectInt32> : IIterator_impl<struct ABI::Windows::Graphics::RectInt32>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Graphics.RectInt32>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<struct ABI::Windows::Graphics::RectInt32> __FIIterator_1_Windows__CGraphics__CRectInt32_t;
#define __FIIterator_1_Windows__CGraphics__CRectInt32 ABI::Windows::Foundation::Collections::__FIIterator_1_Windows__CGraphics__CRectInt32_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Windows__CGraphics__CRectInt32_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#ifndef DEF___FIIterable_1_Windows__CGraphics__CRectInt32_USE
#define DEF___FIIterable_1_Windows__CGraphics__CRectInt32_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("d6222360-b82e-5eed-9eab-2e275b36e47e"))
IIterable<struct ABI::Windows::Graphics::RectInt32> : IIterable_impl<struct ABI::Windows::Graphics::RectInt32>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Graphics.RectInt32>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<struct ABI::Windows::Graphics::RectInt32> __FIIterable_1_Windows__CGraphics__CRectInt32_t;
#define __FIIterable_1_Windows__CGraphics__CRectInt32 ABI::Windows::Foundation::Collections::__FIIterable_1_Windows__CGraphics__CRectInt32_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Windows__CGraphics__CRectInt32_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#ifndef DEF___FIVectorView_1_Windows__CGraphics__CPointInt32_USE
#define DEF___FIVectorView_1_Windows__CGraphics__CPointInt32_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("3c3a4b61-a864-5cb4-a996-2bbee4922757"))
IVectorView<struct ABI::Windows::Graphics::PointInt32> : IVectorView_impl<struct ABI::Windows::Graphics::PointInt32>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Windows.Graphics.PointInt32>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<struct ABI::Windows::Graphics::PointInt32> __FIVectorView_1_Windows__CGraphics__CPointInt32_t;
#define __FIVectorView_1_Windows__CGraphics__CPointInt32 ABI::Windows::Foundation::Collections::__FIVectorView_1_Windows__CGraphics__CPointInt32_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Windows__CGraphics__CPointInt32_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#ifndef DEF___FIVectorView_1_Windows__CGraphics__CRectInt32_USE
#define DEF___FIVectorView_1_Windows__CGraphics__CRectInt32_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("4f5e243f-3812-5200-b70c-30dcfc61717b"))
IVectorView<struct ABI::Windows::Graphics::RectInt32> : IVectorView_impl<struct ABI::Windows::Graphics::RectInt32>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Windows.Graphics.RectInt32>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<struct ABI::Windows::Graphics::RectInt32> __FIVectorView_1_Windows__CGraphics__CRectInt32_t;
#define __FIVectorView_1_Windows__CGraphics__CRectInt32 ABI::Windows::Foundation::Collections::__FIVectorView_1_Windows__CGraphics__CRectInt32_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Windows__CGraphics__CRectInt32_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#ifndef DEF___FIVector_1_Windows__CGraphics__CPointInt32_USE
#define DEF___FIVector_1_Windows__CGraphics__CPointInt32_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("0a15cbe9-ee02-5823-8a2b-fca63940e84f"))
IVector<struct ABI::Windows::Graphics::PointInt32> : IVector_impl<struct ABI::Windows::Graphics::PointInt32>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Windows.Graphics.PointInt32>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<struct ABI::Windows::Graphics::PointInt32> __FIVector_1_Windows__CGraphics__CPointInt32_t;
#define __FIVector_1_Windows__CGraphics__CPointInt32 ABI::Windows::Foundation::Collections::__FIVector_1_Windows__CGraphics__CPointInt32_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Windows__CGraphics__CPointInt32_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#ifndef DEF___FIVector_1_Windows__CGraphics__CRectInt32_USE
#define DEF___FIVector_1_Windows__CGraphics__CRectInt32_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b4c6b283-6002-5af2-afa2-88a5be7ff16f"))
IVector<struct ABI::Windows::Graphics::RectInt32> : IVector_impl<struct ABI::Windows::Graphics::RectInt32>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Windows.Graphics.RectInt32>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<struct ABI::Windows::Graphics::RectInt32> __FIVector_1_Windows__CGraphics__CRectInt32_t;
#define __FIVector_1_Windows__CGraphics__CRectInt32 ABI::Windows::Foundation::Collections::__FIVector_1_Windows__CGraphics__CRectInt32_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Windows__CGraphics__CRectInt32_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Imaging {
                class ImageBuffer;
            } /* Imaging */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Imaging {
                interface IImageBuffer;
            } /* Imaging */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer ABI::Microsoft::Graphics::Imaging::IImageBuffer

#endif // ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                typedef enum AIFeatureReadyState : int AIFeatureReadyState;
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    class ContentFilterOptions;
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    interface IContentFilterOptions;
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions ABI::Microsoft::Windows::AI::ContentSafety::IContentFilterOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__

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
            typedef struct Point Point;
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

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    typedef enum ImageDescriptionKind : int ImageDescriptionKind;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    typedef enum ImageDescriptionResultStatus : int ImageDescriptionResultStatus;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    typedef enum RecognizedLineStyle : int RecognizedLineStyle;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    typedef struct RecognizedTextBoundingBox RecognizedTextBoundingBox;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    class ImageObjectExtractorHint;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    class RecognizedLine;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    class RecognizedWord;
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.AI.Imaging.ImageDescriptionKind
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    enum ImageDescriptionKind : int
                    {
                        ImageDescriptionKind_BriefDescription = 0,
                        ImageDescriptionKind_DetailedDescription = 1,
                        ImageDescriptionKind_DiagramDescription = 2,
                        ImageDescriptionKind_AccessibleDescription = 3,
                    };
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.Imaging.ImageDescriptionResultStatus
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    enum ImageDescriptionResultStatus : int
                    {
                        ImageDescriptionResultStatus_Complete = 0,
                        ImageDescriptionResultStatus_InProgress = 1,
                        ImageDescriptionResultStatus_BlockedByPolicy = 2,
                        ImageDescriptionResultStatus_ImageBlockedByContentModeration = 3,
                        ImageDescriptionResultStatus_TextInImageBlockedByContentModeration = 4,
                        ImageDescriptionResultStatus_DescriptionTextBlockedByContentModeration = 5,
                        ImageDescriptionResultStatus_ImageHasTooMuchText = 6,
                        ImageDescriptionResultStatus_InternalError = 7,
                    };
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.Imaging.RecognizedLineStyle
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    enum RecognizedLineStyle : int
                    {
                        RecognizedLineStyle_Handwritten = 0,
                    };
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.Imaging.RecognizedTextBoundingBox
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    struct RecognizedTextBoundingBox
                    {
                        ABI::Windows::Foundation::Point BottomLeft;
                        ABI::Windows::Foundation::Point BottomRight;
                        ABI::Windows::Foundation::Point TopLeft;
                        ABI::Windows::Foundation::Point TopRight;
                    };
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageDescriptionGenerator
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageDescriptionGenerator
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageDescriptionGenerator[] = L"Microsoft.Windows.AI.Imaging.IImageDescriptionGenerator";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("576b989e-9829-5682-91b0-a7110fa7d51e")
                    IImageDescriptionGenerator : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE DescribeAsync(
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer* image,
                            ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionKind kind,
                            ABI::Microsoft::Windows::AI::ContentSafety::IContentFilterOptions* contentFilterOptions,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageDescriptionGenerator = _uuidof(IImageDescriptionGenerator);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageDescriptionGeneratorStatics
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageDescriptionGenerator
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageDescriptionGeneratorStatics[] = L"Microsoft.Windows.AI.Imaging.IImageDescriptionGeneratorStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("5fb50b2a-5700-55a7-b413-6073b4b7f175")
                    IImageDescriptionGeneratorStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetReadyState(
                            ABI::Microsoft::Windows::AI::AIFeatureReadyState* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsureReadyAsync(
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateAsync(
                            __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageDescriptionGeneratorStatics = _uuidof(IImageDescriptionGeneratorStatics);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageDescriptionResult
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageDescriptionResult
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageDescriptionResult[] = L"Microsoft.Windows.AI.Imaging.IImageDescriptionResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("a066dd0c-110b-5275-a635-52bed7519a2f")
                    IImageDescriptionResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Description(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            ABI::Microsoft::Windows::AI::Imaging::ImageDescriptionResultStatus* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageDescriptionResult = _uuidof(IImageDescriptionResult);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectExtractor
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectExtractor
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectExtractor[] = L"Microsoft.Windows.AI.Imaging.IImageObjectExtractor";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("2919fdc0-d772-5fd9-a8b7-ffb56010c99c")
                    IImageObjectExtractor : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetSoftwareBitmapObjectMask(
                            ABI::Microsoft::Windows::AI::Imaging::IImageObjectExtractorHint* hint,
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetImageBufferObjectMask(
                            ABI::Microsoft::Windows::AI::Imaging::IImageObjectExtractorHint* hint,
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageObjectExtractor = _uuidof(IImageObjectExtractor);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectExtractorHint
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectExtractorHint
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectExtractorHint[] = L"Microsoft.Windows.AI.Imaging.IImageObjectExtractorHint";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("1bd8d67c-8a7a-5fe7-98a5-cbdfeb509452")
                    IImageObjectExtractorHint : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IncludeRects(
                            __FIVectorView_1_Windows__CGraphics__CRectInt32** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IncludePoints(
                            __FIVectorView_1_Windows__CGraphics__CPointInt32** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExcludePoints(
                            __FIVectorView_1_Windows__CGraphics__CPointInt32** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageObjectExtractorHint = _uuidof(IImageObjectExtractorHint);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectExtractorHintFactory
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectExtractorHint
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectExtractorHintFactory[] = L"Microsoft.Windows.AI.Imaging.IImageObjectExtractorHintFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("5028f206-145d-5a70-9a51-e17e60cfbad8")
                    IImageObjectExtractorHintFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            __FIVector_1_Windows__CGraphics__CRectInt32* includeRects,
                            __FIVector_1_Windows__CGraphics__CPointInt32* includePoints,
                            __FIVector_1_Windows__CGraphics__CPointInt32* excludePoints,
                            ABI::Microsoft::Windows::AI::Imaging::IImageObjectExtractorHint** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageObjectExtractorHintFactory = _uuidof(IImageObjectExtractorHintFactory);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectExtractorStatics
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectExtractor
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectExtractorStatics[] = L"Microsoft.Windows.AI.Imaging.IImageObjectExtractorStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("38fa261e-2c33-54cb-9e10-98d50685743d")
                    IImageObjectExtractorStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateWithSoftwareBitmapAsync(
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* softwareBitmap,
                            __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateWithImageBufferAsync(
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer* imageBuffer,
                            __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetReadyState(
                            ABI::Microsoft::Windows::AI::AIFeatureReadyState* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsureReadyAsync(
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageObjectExtractorStatics = _uuidof(IImageObjectExtractorStatics);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectRemover
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectRemoverContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectRemover
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectRemover[] = L"Microsoft.Windows.AI.Imaging.IImageObjectRemover";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("cfa20faf-5ae1-5b8c-b0d8-e7c64db59d26")
                    IImageObjectRemover : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE RemoveFromSoftwareBitmap(
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* softwareBitmap,
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* softwareBitmapMask,
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemoveFromImageBuffer(
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer* imageBuffer,
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer* imageBufferMask,
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageObjectRemover = _uuidof(IImageObjectRemover);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectRemoverStatics
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectRemoverContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectRemover
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectRemoverStatics[] = L"Microsoft.Windows.AI.Imaging.IImageObjectRemoverStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("cbcbd7e1-5b81-503f-8fcb-66ae1d6e5b9c")
                    IImageObjectRemoverStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetReadyState(
                            ABI::Microsoft::Windows::AI::AIFeatureReadyState* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsureReadyAsync(
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateAsync(
                            __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageObjectRemoverStatics = _uuidof(IImageObjectRemoverStatics);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageScaler
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageScalerContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageScaler
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageScaler[] = L"Microsoft.Windows.AI.Imaging.IImageScaler";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("06eec88e-91c5-5326-8128-2807faafa571")
                    IImageScaler : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE ScaleSoftwareBitmap(
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* softwareBitmap,
                            INT32 width,
                            INT32 height,
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ScaleImageBuffer(
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer* imageBuffer,
                            INT32 width,
                            INT32 height,
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MaxSupportedScaleFactor(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageScaler = _uuidof(IImageScaler);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageScalerStatics
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageScalerContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageScaler
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageScalerStatics[] = L"Microsoft.Windows.AI.Imaging.IImageScalerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("75380c81-9c7f-544b-9337-6e638cfb464a")
                    IImageScalerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetReadyState(
                            ABI::Microsoft::Windows::AI::AIFeatureReadyState* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsureReadyAsync(
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateAsync(
                            __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageScalerStatics = _uuidof(IImageScalerStatics);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IRecognizedLine
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.RecognizedLine
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IRecognizedLine[] = L"Microsoft.Windows.AI.Imaging.IRecognizedLine";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("612a6be6-f6bb-53c9-84ce-f0a5e565faa7")
                    IRecognizedLine : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Text(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_BoundingBox(
                            ABI::Microsoft::Windows::AI::Imaging::RecognizedTextBoundingBox* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Words(
                            UINT32* valueLength,
                            ABI::Microsoft::Windows::AI::Imaging::IRecognizedWord*** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Style(
                            ABI::Microsoft::Windows::AI::Imaging::RecognizedLineStyle* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LineStyleConfidence(
                            FLOAT* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRecognizedLine = _uuidof(IRecognizedLine);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IRecognizedText
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.RecognizedText
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IRecognizedText[] = L"Microsoft.Windows.AI.Imaging.IRecognizedText";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("ae4766d3-2924-57a6-b3d3-b866f59b9972")
                    IRecognizedText : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Lines(
                            UINT32* valueLength,
                            ABI::Microsoft::Windows::AI::Imaging::IRecognizedLine*** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TextAngle(
                            FLOAT* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRecognizedText = _uuidof(IRecognizedText);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IRecognizedWord
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.RecognizedWord
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IRecognizedWord[] = L"Microsoft.Windows.AI.Imaging.IRecognizedWord";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("6b53daab-3410-5088-826a-0788a1ee3b52")
                    IRecognizedWord : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Text(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_BoundingBox(
                            ABI::Microsoft::Windows::AI::Imaging::RecognizedTextBoundingBox* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MatchConfidence(
                            FLOAT* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRecognizedWord = _uuidof(IRecognizedWord);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.ITextRecognizer
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.TextRecognizer
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_ITextRecognizer[] = L"Microsoft.Windows.AI.Imaging.ITextRecognizer";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("be7bf6c0-30f6-570d-bd92-3ffe5665d933")
                    ITextRecognizer : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE RecognizeTextFromImageAsync(
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer* imageBuffer,
                            __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RecognizeTextFromImage(
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer* imageBuffer,
                            ABI::Microsoft::Windows::AI::Imaging::IRecognizedText** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextRecognizer = _uuidof(ITextRecognizer);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.ITextRecognizerStatics
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.TextRecognizer
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_ITextRecognizerStatics[] = L"Microsoft.Windows.AI.Imaging.ITextRecognizerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Imaging {
                    MIDL_INTERFACE("3788c2fd-e496-53ab-85a7-e54a135824e9")
                    ITextRecognizerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetReadyState(
                            ABI::Microsoft::Windows::AI::AIFeatureReadyState* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsureReadyAsync(
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateAsync(
                            __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextRecognizerStatics = _uuidof(ITextRecognizerStatics);
                } /* Imaging */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageDescriptionGenerator
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Imaging.IImageDescriptionGeneratorStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.ImageDescriptionContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageDescriptionGenerator ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageDescriptionGenerator_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageDescriptionGenerator_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageDescriptionGenerator[] = L"Microsoft.Windows.AI.Imaging.ImageDescriptionGenerator";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageDescriptionResult
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageDescriptionResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageDescriptionResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageDescriptionResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageDescriptionResult[] = L"Microsoft.Windows.AI.Imaging.ImageDescriptionResult";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageObjectExtractor
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Imaging.IImageObjectExtractorStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageObjectExtractor ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectExtractor_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectExtractor_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageObjectExtractor[] = L"Microsoft.Windows.AI.Imaging.ImageObjectExtractor";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageObjectExtractorHint
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.Imaging.IImageObjectExtractorHintFactory interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageObjectExtractorHint ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectExtractorHint_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectExtractorHint_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageObjectExtractorHint[] = L"Microsoft.Windows.AI.Imaging.ImageObjectExtractorHint";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageObjectRemover
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectRemoverContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Imaging.IImageObjectRemoverStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.ImageObjectRemoverContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageObjectRemover ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectRemover_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectRemover_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageObjectRemover[] = L"Microsoft.Windows.AI.Imaging.ImageObjectRemover";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageScaler
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageScalerContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Imaging.IImageScalerStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.ImageScalerContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageScaler ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageScaler_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageScaler_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageScaler[] = L"Microsoft.Windows.AI.Imaging.ImageScaler";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.RecognizedLine
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IRecognizedLine ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedLine_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedLine_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_RecognizedLine[] = L"Microsoft.Windows.AI.Imaging.RecognizedLine";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.RecognizedText
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IRecognizedText ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedText_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedText_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_RecognizedText[] = L"Microsoft.Windows.AI.Imaging.RecognizedText";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.RecognizedWord
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IRecognizedWord ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedWord_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedWord_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_RecognizedWord[] = L"Microsoft.Windows.AI.Imaging.RecognizedWord";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.TextRecognizer
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Imaging.ITextRecognizerStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.TextRecognitionContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.ITextRecognizer ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_TextRecognizer_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_TextRecognizer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_TextRecognizer[] = L"Microsoft.Windows.AI.Imaging.TextRecognizer";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator;

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGeneratorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGeneratorVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGeneratorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGeneratorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGeneratorVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGeneratorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor;

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractorVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractorVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover;

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemoverVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemoverVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemoverVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemoverVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemoverVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemoverVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler;

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScalerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScalerVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScalerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScalerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScalerVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScalerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CImageScaler_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText;

#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedTextVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedTextVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedTextVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedTextVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedTextVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedTextVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer;

#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizerVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizerVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double;

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double;

#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double;

typedef struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_doubleVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_doubleVtbl;

interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double
{
    CONST_VTBL struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_doubleVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double;

typedef struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_doubleVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* handler);
    HRESULT (STDMETHODCALLTYPE* get_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** result);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult** result);

    END_INTERFACE
} __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_doubleVtbl;

interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double
{
    CONST_VTBL struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_doubleVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_put_Progress(This, handler) \
    ((This)->lpVtbl->put_Progress(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_get_Progress(This, result) \
    ((This)->lpVtbl->get_Progress(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_INTERFACE_DEFINED__)
#define ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double;

typedef struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_doubleVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double* asyncInfo,
        DOUBLE progressInfo);

    END_INTERFACE
} __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_doubleVtbl;

interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double
{
    CONST_VTBL struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_doubleVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_Invoke(This, asyncInfo, progressInfo) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, progressInfo))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING;

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING;

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING;

typedef struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRINGVtbl;

interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING
{
    CONST_VTBL struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING;

typedef struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* handler);
    HRESULT (STDMETHODCALLTYPE* get_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult** result);

    END_INTERFACE
} __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRINGVtbl;

interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING
{
    CONST_VTBL struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_put_Progress(This, handler) \
    ((This)->lpVtbl->put_Progress(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_get_Progress(This, result) \
    ((This)->lpVtbl->get_Progress(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_INTERFACE_DEFINED__)
#define ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING;

typedef struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING* asyncInfo,
        HSTRING progressInfo);

    END_INTERFACE
} __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRINGVtbl;

interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING
{
    CONST_VTBL struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_Invoke(This, asyncInfo, progressInfo) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, progressInfo))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

typedef struct __x_ABI_CWindows_CGraphics_CPointInt32 __x_ABI_CWindows_CGraphics_CPointInt32;

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000
#if !defined(____FIIterator_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__)
#define ____FIIterator_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Windows__CGraphics__CPointInt32 __FIIterator_1_Windows__CGraphics__CPointInt32;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Windows__CGraphics__CPointInt32;

typedef struct __FIIterator_1_Windows__CGraphics__CPointInt32Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Windows__CGraphics__CPointInt32* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Windows__CGraphics__CPointInt32* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Windows__CGraphics__CPointInt32* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Windows__CGraphics__CPointInt32* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Windows__CGraphics__CPointInt32* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Windows__CGraphics__CPointInt32* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Windows__CGraphics__CPointInt32* This,
        struct __x_ABI_CWindows_CGraphics_CPointInt32* result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Windows__CGraphics__CPointInt32* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Windows__CGraphics__CPointInt32* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Windows__CGraphics__CPointInt32* This,
        UINT32 itemsLength,
        struct __x_ABI_CWindows_CGraphics_CPointInt32* items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Windows__CGraphics__CPointInt32Vtbl;

interface __FIIterator_1_Windows__CGraphics__CPointInt32
{
    CONST_VTBL struct __FIIterator_1_Windows__CGraphics__CPointInt32Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Windows__CGraphics__CPointInt32_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Windows__CGraphics__CPointInt32_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Windows__CGraphics__CPointInt32_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Windows__CGraphics__CPointInt32_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Windows__CGraphics__CPointInt32_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Windows__CGraphics__CPointInt32_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Windows__CGraphics__CPointInt32_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Windows__CGraphics__CPointInt32_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Windows__CGraphics__CPointInt32_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Windows__CGraphics__CPointInt32_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000
#if !defined(____FIIterable_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__)
#define ____FIIterable_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Windows__CGraphics__CPointInt32 __FIIterable_1_Windows__CGraphics__CPointInt32;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Windows__CGraphics__CPointInt32;

typedef struct __FIIterable_1_Windows__CGraphics__CPointInt32Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Windows__CGraphics__CPointInt32* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Windows__CGraphics__CPointInt32* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Windows__CGraphics__CPointInt32* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Windows__CGraphics__CPointInt32* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Windows__CGraphics__CPointInt32* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Windows__CGraphics__CPointInt32* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Windows__CGraphics__CPointInt32* This,
        __FIIterator_1_Windows__CGraphics__CPointInt32** result);

    END_INTERFACE
} __FIIterable_1_Windows__CGraphics__CPointInt32Vtbl;

interface __FIIterable_1_Windows__CGraphics__CPointInt32
{
    CONST_VTBL struct __FIIterable_1_Windows__CGraphics__CPointInt32Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Windows__CGraphics__CPointInt32_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Windows__CGraphics__CPointInt32_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Windows__CGraphics__CPointInt32_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Windows__CGraphics__CPointInt32_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Windows__CGraphics__CPointInt32_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Windows__CGraphics__CPointInt32_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Windows__CGraphics__CPointInt32_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

typedef struct __x_ABI_CWindows_CGraphics_CRectInt32 __x_ABI_CWindows_CGraphics_CRectInt32;

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000
#if !defined(____FIIterator_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__)
#define ____FIIterator_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Windows__CGraphics__CRectInt32 __FIIterator_1_Windows__CGraphics__CRectInt32;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Windows__CGraphics__CRectInt32;

typedef struct __FIIterator_1_Windows__CGraphics__CRectInt32Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Windows__CGraphics__CRectInt32* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Windows__CGraphics__CRectInt32* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Windows__CGraphics__CRectInt32* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Windows__CGraphics__CRectInt32* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Windows__CGraphics__CRectInt32* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Windows__CGraphics__CRectInt32* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Windows__CGraphics__CRectInt32* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Windows__CGraphics__CRectInt32* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Windows__CGraphics__CRectInt32* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Windows__CGraphics__CRectInt32* This,
        UINT32 itemsLength,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Windows__CGraphics__CRectInt32Vtbl;

interface __FIIterator_1_Windows__CGraphics__CRectInt32
{
    CONST_VTBL struct __FIIterator_1_Windows__CGraphics__CRectInt32Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Windows__CGraphics__CRectInt32_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Windows__CGraphics__CRectInt32_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Windows__CGraphics__CRectInt32_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Windows__CGraphics__CRectInt32_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Windows__CGraphics__CRectInt32_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Windows__CGraphics__CRectInt32_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Windows__CGraphics__CRectInt32_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Windows__CGraphics__CRectInt32_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Windows__CGraphics__CRectInt32_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Windows__CGraphics__CRectInt32_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000
#if !defined(____FIIterable_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__)
#define ____FIIterable_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Windows__CGraphics__CRectInt32 __FIIterable_1_Windows__CGraphics__CRectInt32;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Windows__CGraphics__CRectInt32;

typedef struct __FIIterable_1_Windows__CGraphics__CRectInt32Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Windows__CGraphics__CRectInt32* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Windows__CGraphics__CRectInt32* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Windows__CGraphics__CRectInt32* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Windows__CGraphics__CRectInt32* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Windows__CGraphics__CRectInt32* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Windows__CGraphics__CRectInt32* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Windows__CGraphics__CRectInt32* This,
        __FIIterator_1_Windows__CGraphics__CRectInt32** result);

    END_INTERFACE
} __FIIterable_1_Windows__CGraphics__CRectInt32Vtbl;

interface __FIIterable_1_Windows__CGraphics__CRectInt32
{
    CONST_VTBL struct __FIIterable_1_Windows__CGraphics__CRectInt32Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Windows__CGraphics__CRectInt32_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Windows__CGraphics__CRectInt32_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Windows__CGraphics__CRectInt32_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Windows__CGraphics__CRectInt32_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Windows__CGraphics__CRectInt32_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Windows__CGraphics__CRectInt32_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Windows__CGraphics__CRectInt32_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000
#if !defined(____FIVectorView_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Windows__CGraphics__CPointInt32 __FIVectorView_1_Windows__CGraphics__CPointInt32;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Windows__CGraphics__CPointInt32;

typedef struct __FIVectorView_1_Windows__CGraphics__CPointInt32Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Windows__CGraphics__CPointInt32* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Windows__CGraphics__CPointInt32* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Windows__CGraphics__CPointInt32* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Windows__CGraphics__CPointInt32* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Windows__CGraphics__CPointInt32* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Windows__CGraphics__CPointInt32* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Windows__CGraphics__CPointInt32* This,
        UINT32 index,
        struct __x_ABI_CWindows_CGraphics_CPointInt32* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Windows__CGraphics__CPointInt32* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Windows__CGraphics__CPointInt32* This,
        struct __x_ABI_CWindows_CGraphics_CPointInt32 value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Windows__CGraphics__CPointInt32* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        struct __x_ABI_CWindows_CGraphics_CPointInt32* items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Windows__CGraphics__CPointInt32Vtbl;

interface __FIVectorView_1_Windows__CGraphics__CPointInt32
{
    CONST_VTBL struct __FIVectorView_1_Windows__CGraphics__CPointInt32Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Windows__CGraphics__CPointInt32_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Windows__CGraphics__CPointInt32_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Windows__CGraphics__CPointInt32_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Windows__CGraphics__CPointInt32_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Windows__CGraphics__CPointInt32_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Windows__CGraphics__CPointInt32_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Windows__CGraphics__CPointInt32_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Windows__CGraphics__CPointInt32_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Windows__CGraphics__CPointInt32_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Windows__CGraphics__CPointInt32_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000
#if !defined(____FIVectorView_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Windows__CGraphics__CRectInt32 __FIVectorView_1_Windows__CGraphics__CRectInt32;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Windows__CGraphics__CRectInt32;

typedef struct __FIVectorView_1_Windows__CGraphics__CRectInt32Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Windows__CGraphics__CRectInt32* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Windows__CGraphics__CRectInt32* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Windows__CGraphics__CRectInt32* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Windows__CGraphics__CRectInt32* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Windows__CGraphics__CRectInt32* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Windows__CGraphics__CRectInt32* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Windows__CGraphics__CRectInt32* This,
        UINT32 index,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Windows__CGraphics__CRectInt32* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Windows__CGraphics__CRectInt32* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Windows__CGraphics__CRectInt32* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Windows__CGraphics__CRectInt32Vtbl;

interface __FIVectorView_1_Windows__CGraphics__CRectInt32
{
    CONST_VTBL struct __FIVectorView_1_Windows__CGraphics__CRectInt32Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Windows__CGraphics__CRectInt32_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Windows__CGraphics__CRectInt32_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Windows__CGraphics__CRectInt32_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Windows__CGraphics__CRectInt32_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Windows__CGraphics__CRectInt32_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Windows__CGraphics__CRectInt32_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Windows__CGraphics__CRectInt32_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Windows__CGraphics__CRectInt32_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Windows__CGraphics__CRectInt32_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Windows__CGraphics__CRectInt32_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000
#if !defined(____FIVector_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__)
#define ____FIVector_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__

typedef interface __FIVector_1_Windows__CGraphics__CPointInt32 __FIVector_1_Windows__CGraphics__CPointInt32;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Windows__CGraphics__CPointInt32;

typedef struct __FIVector_1_Windows__CGraphics__CPointInt32Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Windows__CGraphics__CPointInt32* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Windows__CGraphics__CPointInt32* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        UINT32 index,
        struct __x_ABI_CWindows_CGraphics_CPointInt32* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        __FIVectorView_1_Windows__CGraphics__CPointInt32** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        struct __x_ABI_CWindows_CGraphics_CPointInt32 value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        UINT32 index,
        struct __x_ABI_CWindows_CGraphics_CPointInt32 value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        UINT32 index,
        struct __x_ABI_CWindows_CGraphics_CPointInt32 value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        struct __x_ABI_CWindows_CGraphics_CPointInt32 value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Windows__CGraphics__CPointInt32* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Windows__CGraphics__CPointInt32* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        struct __x_ABI_CWindows_CGraphics_CPointInt32* items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Windows__CGraphics__CPointInt32* This,
        UINT32 itemsLength,
        struct __x_ABI_CWindows_CGraphics_CPointInt32* items);

    END_INTERFACE
} __FIVector_1_Windows__CGraphics__CPointInt32Vtbl;

interface __FIVector_1_Windows__CGraphics__CPointInt32
{
    CONST_VTBL struct __FIVector_1_Windows__CGraphics__CPointInt32Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Windows__CGraphics__CPointInt32_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Windows__CGraphics__CPointInt32_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Windows__CGraphics__CPointInt32_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Windows__CGraphics__CPointInt32_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Windows__CGraphics__CPointInt32_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Windows__CGraphics__CPointInt32_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Windows__CGraphics__CPointInt32_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Windows__CGraphics__CPointInt32_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Windows__CGraphics__CPointInt32_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Windows__CGraphics__CPointInt32_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Windows__CGraphics__CPointInt32_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Windows__CGraphics__CPointInt32_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Windows__CGraphics__CPointInt32_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Windows__CGraphics__CPointInt32_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Windows__CGraphics__CPointInt32_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Windows__CGraphics__CPointInt32_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Windows__CGraphics__CPointInt32_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Windows__CGraphics__CPointInt32_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Windows__CGraphics__CPointInt32_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000
#if !defined(____FIVector_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__)
#define ____FIVector_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__

typedef interface __FIVector_1_Windows__CGraphics__CRectInt32 __FIVector_1_Windows__CGraphics__CRectInt32;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Windows__CGraphics__CRectInt32;

typedef struct __FIVector_1_Windows__CGraphics__CRectInt32Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Windows__CGraphics__CRectInt32* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Windows__CGraphics__CRectInt32* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        UINT32 index,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        __FIVectorView_1_Windows__CGraphics__CRectInt32** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        UINT32 index,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        UINT32 index,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Windows__CGraphics__CRectInt32* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Windows__CGraphics__CRectInt32* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Windows__CGraphics__CRectInt32* This,
        UINT32 itemsLength,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* items);

    END_INTERFACE
} __FIVector_1_Windows__CGraphics__CRectInt32Vtbl;

interface __FIVector_1_Windows__CGraphics__CRectInt32
{
    CONST_VTBL struct __FIVector_1_Windows__CGraphics__CRectInt32Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Windows__CGraphics__CRectInt32_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Windows__CGraphics__CRectInt32_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Windows__CGraphics__CRectInt32_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Windows__CGraphics__CRectInt32_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Windows__CGraphics__CRectInt32_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Windows__CGraphics__CRectInt32_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Windows__CGraphics__CRectInt32_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Windows__CGraphics__CRectInt32_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Windows__CGraphics__CRectInt32_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Windows__CGraphics__CRectInt32_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Windows__CGraphics__CRectInt32_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Windows__CGraphics__CRectInt32_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Windows__CGraphics__CRectInt32_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Windows__CGraphics__CRectInt32_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Windows__CGraphics__CRectInt32_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Windows__CGraphics__CRectInt32_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Windows__CGraphics__CRectInt32_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Windows__CGraphics__CRectInt32_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Windows__CGraphics__CRectInt32_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000

#ifndef ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer;

#endif // ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState;

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CPoint __x_ABI_CWindows_CFoundation_CPoint;

#ifndef ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
#define ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap;

#endif // ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CImageDescriptionKind __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CImageDescriptionKind;

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CImageDescriptionResultStatus __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CImageDescriptionResultStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CRecognizedLineStyle __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CRecognizedLineStyle;

typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CRecognizedTextBoundingBox __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CRecognizedTextBoundingBox;

/*
 *
 * Struct Microsoft.Windows.AI.Imaging.ImageDescriptionKind
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CImageDescriptionKind
{
    ImageDescriptionKind_BriefDescription = 0,
    ImageDescriptionKind_DetailedDescription = 1,
    ImageDescriptionKind_DiagramDescription = 2,
    ImageDescriptionKind_AccessibleDescription = 3,
};
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.Imaging.ImageDescriptionResultStatus
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CImageDescriptionResultStatus
{
    ImageDescriptionResultStatus_Complete = 0,
    ImageDescriptionResultStatus_InProgress = 1,
    ImageDescriptionResultStatus_BlockedByPolicy = 2,
    ImageDescriptionResultStatus_ImageBlockedByContentModeration = 3,
    ImageDescriptionResultStatus_TextInImageBlockedByContentModeration = 4,
    ImageDescriptionResultStatus_DescriptionTextBlockedByContentModeration = 5,
    ImageDescriptionResultStatus_ImageHasTooMuchText = 6,
    ImageDescriptionResultStatus_InternalError = 7,
};
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.Imaging.RecognizedLineStyle
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CRecognizedLineStyle
{
    RecognizedLineStyle_Handwritten = 0,
};
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.Imaging.RecognizedTextBoundingBox
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CRecognizedTextBoundingBox
{
    struct __x_ABI_CWindows_CFoundation_CPoint BottomLeft;
    struct __x_ABI_CWindows_CFoundation_CPoint BottomRight;
    struct __x_ABI_CWindows_CFoundation_CPoint TopLeft;
    struct __x_ABI_CWindows_CFoundation_CPoint TopRight;
};
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageDescriptionGenerator
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageDescriptionGenerator
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageDescriptionGenerator[] = L"Microsoft.Windows.AI.Imaging.IImageDescriptionGenerator";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* DescribeAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator* This,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* image,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CImageDescriptionKind kind,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* contentFilterOptions,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CImaging__CImageDescriptionResult_HSTRING** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_DescribeAsync(This, image, kind, contentFilterOptions, operation) \
    ((This)->lpVtbl->DescribeAsync(This, image, kind, contentFilterOptions, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGenerator_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageDescriptionGeneratorStatics
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageDescriptionGenerator
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageDescriptionGeneratorStatics[] = L"Microsoft.Windows.AI.Imaging.IImageDescriptionGeneratorStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetReadyState)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState* result);
    HRESULT (STDMETHODCALLTYPE* EnsureReadyAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation);
    HRESULT (STDMETHODCALLTYPE* CreateAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageDescriptionGenerator** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_GetReadyState(This, result) \
    ((This)->lpVtbl->GetReadyState(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_EnsureReadyAsync(This, operation) \
    ((This)->lpVtbl->EnsureReadyAsync(This, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_CreateAsync(This, operation) \
    ((This)->lpVtbl->CreateAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionGeneratorStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageDescriptionResult
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageDescriptionResult
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageDescriptionResult[] = L"Microsoft.Windows.AI.Imaging.IImageDescriptionResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Description)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CImageDescriptionResultStatus* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_get_Description(This, value) \
    ((This)->lpVtbl->get_Description(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageDescriptionResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectExtractor
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectExtractor
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectExtractor[] = L"Microsoft.Windows.AI.Imaging.IImageObjectExtractor";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetSoftwareBitmapObjectMask)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* hint,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap** result);
    HRESULT (STDMETHODCALLTYPE* GetImageBufferObjectMask)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* hint,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_GetSoftwareBitmapObjectMask(This, hint, result) \
    ((This)->lpVtbl->GetSoftwareBitmapObjectMask(This, hint, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_GetImageBufferObjectMask(This, hint, result) \
    ((This)->lpVtbl->GetImageBufferObjectMask(This, hint, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractor_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectExtractorHint
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectExtractorHint
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectExtractorHint[] = L"Microsoft.Windows.AI.Imaging.IImageObjectExtractorHint";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IncludeRects)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* This,
        __FIVectorView_1_Windows__CGraphics__CRectInt32** value);
    HRESULT (STDMETHODCALLTYPE* get_IncludePoints)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* This,
        __FIVectorView_1_Windows__CGraphics__CPointInt32** value);
    HRESULT (STDMETHODCALLTYPE* get_ExcludePoints)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint* This,
        __FIVectorView_1_Windows__CGraphics__CPointInt32** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_get_IncludeRects(This, value) \
    ((This)->lpVtbl->get_IncludeRects(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_get_IncludePoints(This, value) \
    ((This)->lpVtbl->get_IncludePoints(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_get_ExcludePoints(This, value) \
    ((This)->lpVtbl->get_ExcludePoints(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectExtractorHintFactory
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectExtractorHint
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectExtractorHintFactory[] = L"Microsoft.Windows.AI.Imaging.IImageObjectExtractorHintFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory* This,
        __FIVector_1_Windows__CGraphics__CRectInt32* includeRects,
        __FIVector_1_Windows__CGraphics__CPointInt32* includePoints,
        __FIVector_1_Windows__CGraphics__CPointInt32* excludePoints,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHint** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_CreateInstance(This, includeRects, includePoints, excludePoints, value) \
    ((This)->lpVtbl->CreateInstance(This, includeRects, includePoints, excludePoints, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorHintFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectExtractorStatics
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectExtractor
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectExtractorStatics[] = L"Microsoft.Windows.AI.Imaging.IImageObjectExtractorStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateWithSoftwareBitmapAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics* This,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* softwareBitmap,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor** operation);
    HRESULT (STDMETHODCALLTYPE* CreateWithImageBufferAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics* This,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* imageBuffer,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectExtractor** operation);
    HRESULT (STDMETHODCALLTYPE* GetReadyState)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState* result);
    HRESULT (STDMETHODCALLTYPE* EnsureReadyAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_CreateWithSoftwareBitmapAsync(This, softwareBitmap, operation) \
    ((This)->lpVtbl->CreateWithSoftwareBitmapAsync(This, softwareBitmap, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_CreateWithImageBufferAsync(This, imageBuffer, operation) \
    ((This)->lpVtbl->CreateWithImageBufferAsync(This, imageBuffer, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_GetReadyState(This, result) \
    ((This)->lpVtbl->GetReadyState(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_EnsureReadyAsync(This, operation) \
    ((This)->lpVtbl->EnsureReadyAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectExtractorStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectRemover
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectRemoverContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectRemover
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectRemover[] = L"Microsoft.Windows.AI.Imaging.IImageObjectRemover";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* RemoveFromSoftwareBitmap)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover* This,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* softwareBitmap,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* softwareBitmapMask,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap** result);
    HRESULT (STDMETHODCALLTYPE* RemoveFromImageBuffer)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover* This,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* imageBuffer,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* imageBufferMask,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_RemoveFromSoftwareBitmap(This, softwareBitmap, softwareBitmapMask, result) \
    ((This)->lpVtbl->RemoveFromSoftwareBitmap(This, softwareBitmap, softwareBitmapMask, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_RemoveFromImageBuffer(This, imageBuffer, imageBufferMask, result) \
    ((This)->lpVtbl->RemoveFromImageBuffer(This, imageBuffer, imageBufferMask, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemover_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageObjectRemoverStatics
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectRemoverContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageObjectRemover
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageObjectRemoverStatics[] = L"Microsoft.Windows.AI.Imaging.IImageObjectRemoverStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetReadyState)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState* result);
    HRESULT (STDMETHODCALLTYPE* EnsureReadyAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation);
    HRESULT (STDMETHODCALLTYPE* CreateAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageObjectRemover** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_GetReadyState(This, result) \
    ((This)->lpVtbl->GetReadyState(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_EnsureReadyAsync(This, operation) \
    ((This)->lpVtbl->EnsureReadyAsync(This, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_CreateAsync(This, operation) \
    ((This)->lpVtbl->CreateAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageObjectRemoverStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageScaler
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageScalerContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageScaler
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageScaler[] = L"Microsoft.Windows.AI.Imaging.IImageScaler";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ScaleSoftwareBitmap)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler* This,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* softwareBitmap,
        INT32 width,
        INT32 height,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap** result);
    HRESULT (STDMETHODCALLTYPE* ScaleImageBuffer)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler* This,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* imageBuffer,
        INT32 width,
        INT32 height,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer** result);
    HRESULT (STDMETHODCALLTYPE* get_MaxSupportedScaleFactor)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_ScaleSoftwareBitmap(This, softwareBitmap, width, height, result) \
    ((This)->lpVtbl->ScaleSoftwareBitmap(This, softwareBitmap, width, height, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_ScaleImageBuffer(This, imageBuffer, width, height, result) \
    ((This)->lpVtbl->ScaleImageBuffer(This, imageBuffer, width, height, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_get_MaxSupportedScaleFactor(This, value) \
    ((This)->lpVtbl->get_MaxSupportedScaleFactor(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScaler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IImageScalerStatics
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageScalerContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.ImageScaler
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IImageScalerStatics[] = L"Microsoft.Windows.AI.Imaging.IImageScalerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetReadyState)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState* result);
    HRESULT (STDMETHODCALLTYPE* EnsureReadyAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation);
    HRESULT (STDMETHODCALLTYPE* CreateAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CImageScaler** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_GetReadyState(This, result) \
    ((This)->lpVtbl->GetReadyState(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_EnsureReadyAsync(This, operation) \
    ((This)->lpVtbl->EnsureReadyAsync(This, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_CreateAsync(This, operation) \
    ((This)->lpVtbl->CreateAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIImageScalerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IRecognizedLine
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.RecognizedLine
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IRecognizedLine[] = L"Microsoft.Windows.AI.Imaging.IRecognizedLine";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLineVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Text)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_BoundingBox)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This,
        struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CRecognizedTextBoundingBox* value);
    HRESULT (STDMETHODCALLTYPE* get_Words)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This,
        UINT32* valueLength,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord*** value);
    HRESULT (STDMETHODCALLTYPE* get_Style)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CRecognizedLineStyle* value);
    HRESULT (STDMETHODCALLTYPE* get_LineStyleConfidence)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine* This,
        FLOAT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLineVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLineVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_get_Text(This, value) \
    ((This)->lpVtbl->get_Text(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_get_BoundingBox(This, value) \
    ((This)->lpVtbl->get_BoundingBox(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_get_Words(This, valueLength, value) \
    ((This)->lpVtbl->get_Words(This, valueLength, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_get_Style(This, value) \
    ((This)->lpVtbl->get_Style(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_get_LineStyleConfidence(This, value) \
    ((This)->lpVtbl->get_LineStyleConfidence(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IRecognizedText
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.RecognizedText
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IRecognizedText[] = L"Microsoft.Windows.AI.Imaging.IRecognizedText";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedTextVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Lines)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText* This,
        UINT32* valueLength,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedLine*** value);
    HRESULT (STDMETHODCALLTYPE* get_TextAngle)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText* This,
        FLOAT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedTextVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedTextVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_get_Lines(This, valueLength, value) \
    ((This)->lpVtbl->get_Lines(This, valueLength, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_get_TextAngle(This, value) \
    ((This)->lpVtbl->get_TextAngle(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.IRecognizedWord
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.RecognizedWord
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_IRecognizedWord[] = L"Microsoft.Windows.AI.Imaging.IRecognizedWord";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWordVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Text)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_BoundingBox)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord* This,
        struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CRecognizedTextBoundingBox* value);
    HRESULT (STDMETHODCALLTYPE* get_MatchConfidence)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord* This,
        FLOAT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWordVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWordVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_get_Text(This, value) \
    ((This)->lpVtbl->get_Text(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_get_BoundingBox(This, value) \
    ((This)->lpVtbl->get_BoundingBox(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_get_MatchConfidence(This, value) \
    ((This)->lpVtbl->get_MatchConfidence(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedWord_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.ITextRecognizer
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.TextRecognizer
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_ITextRecognizer[] = L"Microsoft.Windows.AI.Imaging.ITextRecognizer";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* RecognizeTextFromImageAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer* This,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* imageBuffer,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CRecognizedText** operation);
    HRESULT (STDMETHODCALLTYPE* RecognizeTextFromImage)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer* This,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* imageBuffer,
        __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CIRecognizedText** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_RecognizeTextFromImageAsync(This, imageBuffer, operation) \
    ((This)->lpVtbl->RecognizeTextFromImageAsync(This, imageBuffer, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_RecognizeTextFromImage(This, imageBuffer, result) \
    ((This)->lpVtbl->RecognizeTextFromImage(This, imageBuffer, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Imaging.ITextRecognizerStatics
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Imaging.TextRecognizer
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Imaging_ITextRecognizerStatics[] = L"Microsoft.Windows.AI.Imaging.ITextRecognizerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetReadyState)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState* result);
    HRESULT (STDMETHODCALLTYPE* EnsureReadyAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation);
    HRESULT (STDMETHODCALLTYPE* CreateAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CImaging__CTextRecognizer** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_GetReadyState(This, result) \
    ((This)->lpVtbl->GetReadyState(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_EnsureReadyAsync(This, operation) \
    ((This)->lpVtbl->EnsureReadyAsync(This, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_CreateAsync(This, operation) \
    ((This)->lpVtbl->CreateAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CImaging_CITextRecognizerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageDescriptionGenerator
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Imaging.IImageDescriptionGeneratorStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.ImageDescriptionContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageDescriptionGenerator ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageDescriptionGenerator_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageDescriptionGenerator_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageDescriptionGenerator[] = L"Microsoft.Windows.AI.Imaging.ImageDescriptionGenerator";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageDescriptionResult
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageDescriptionContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageDescriptionResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageDescriptionResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageDescriptionResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageDescriptionResult[] = L"Microsoft.Windows.AI.Imaging.ImageDescriptionResult";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEDESCRIPTIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageObjectExtractor
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Imaging.IImageObjectExtractorStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageObjectExtractor ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectExtractor_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectExtractor_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageObjectExtractor[] = L"Microsoft.Windows.AI.Imaging.ImageObjectExtractor";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageObjectExtractorHint
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.Imaging.IImageObjectExtractorHintFactory interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.ImageObjectExtractorContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageObjectExtractorHint ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectExtractorHint_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectExtractorHint_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageObjectExtractorHint[] = L"Microsoft.Windows.AI.Imaging.ImageObjectExtractorHint";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTEXTRACTORCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageObjectRemover
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageObjectRemoverContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Imaging.IImageObjectRemoverStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.ImageObjectRemoverContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageObjectRemover ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectRemover_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageObjectRemover_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageObjectRemover[] = L"Microsoft.Windows.AI.Imaging.ImageObjectRemover";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGEOBJECTREMOVERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.ImageScaler
 *
 * Introduced to Microsoft.Windows.AI.Imaging.ImageScalerContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Imaging.IImageScalerStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.ImageScalerContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IImageScaler ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageScaler_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_ImageScaler_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_ImageScaler[] = L"Microsoft.Windows.AI.Imaging.ImageScaler";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_IMAGESCALERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.RecognizedLine
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IRecognizedLine ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedLine_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedLine_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_RecognizedLine[] = L"Microsoft.Windows.AI.Imaging.RecognizedLine";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.RecognizedText
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IRecognizedText ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedText_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedText_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_RecognizedText[] = L"Microsoft.Windows.AI.Imaging.RecognizedText";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.RecognizedWord
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.IRecognizedWord ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedWord_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_RecognizedWord_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_RecognizedWord[] = L"Microsoft.Windows.AI.Imaging.RecognizedWord";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Imaging.TextRecognizer
 *
 * Introduced to Microsoft.Windows.AI.Imaging.TextRecognitionContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Imaging.ITextRecognizerStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Imaging.TextRecognitionContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Imaging.ITextRecognizer ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Imaging_TextRecognizer_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Imaging_TextRecognizer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Imaging_TextRecognizer[] = L"Microsoft.Windows.AI.Imaging.TextRecognizer";
#endif
#endif // MICROSOFT_WINDOWS_AI_IMAGING_TEXTRECOGNITIONCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eai2Eimaging_p_h__

#endif // __microsoft2Ewindows2Eai2Eimaging_h__
