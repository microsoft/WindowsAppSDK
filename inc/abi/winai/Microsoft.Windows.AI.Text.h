
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
#ifndef __microsoft2Ewindows2Eai2Etext_h__
#define __microsoft2Ewindows2Eai2Etext_h__
#ifndef __microsoft2Ewindows2Eai2Etext_p_h__
#define __microsoft2Ewindows2Eai2Etext_p_h__


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
#if !defined(MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION 0x60000
#endif // defined(MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION)

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
#include "Microsoft.Windows.AI.h"
#include "Microsoft.Windows.AI.ContentSafety.h"
#include "Microsoft.Windows.AI.Foundation.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface IConversationItem;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem ABI::Microsoft::Windows::AI::Text::IConversationItem

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface IConversationSummaryOptions;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions ABI::Microsoft::Windows::AI::Text::IConversationSummaryOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ILanguageModel;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel ABI::Microsoft::Windows::AI::Text::ILanguageModel

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ILanguageModel2;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2 ABI::Microsoft::Windows::AI::Text::ILanguageModel2

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ILanguageModelContext;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext ABI::Microsoft::Windows::AI::Text::ILanguageModelContext

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ILanguageModelEmbeddingVectorResult;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult ABI::Microsoft::Windows::AI::Text::ILanguageModelEmbeddingVectorResult

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ILanguageModelOptions;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions ABI::Microsoft::Windows::AI::Text::ILanguageModelOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ILanguageModelResponseResult;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult ABI::Microsoft::Windows::AI::Text::ILanguageModelResponseResult

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ILanguageModelStatics;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics ABI::Microsoft::Windows::AI::Text::ILanguageModelStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextRewriter;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter ABI::Microsoft::Windows::AI::Text::ITextRewriter

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextRewriter2;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2 ABI::Microsoft::Windows::AI::Text::ITextRewriter2

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextRewriterFactory;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory ABI::Microsoft::Windows::AI::Text::ITextRewriterFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextSummarizer;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer ABI::Microsoft::Windows::AI::Text::ITextSummarizer

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextSummarizer2;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2 ABI::Microsoft::Windows::AI::Text::ITextSummarizer2

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextSummarizer3;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3 ABI::Microsoft::Windows::AI::Text::ITextSummarizer3

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextSummarizer4;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4 ABI::Microsoft::Windows::AI::Text::ITextSummarizer4

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextSummarizerFactory;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory ABI::Microsoft::Windows::AI::Text::ITextSummarizerFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextToTableConverter;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter ABI::Microsoft::Windows::AI::Text::ITextToTableConverter

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextToTableConverterFactory;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory ABI::Microsoft::Windows::AI::Text::ITextToTableConverterFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextToTableResponseResult;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult ABI::Microsoft::Windows::AI::Text::ITextToTableResponseResult

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    interface ITextToTableRow;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow ABI::Microsoft::Windows::AI::Text::ITextToTableRow

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class LanguageModel;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("172f62b5-1d49-535f-8c07-4ddd02066f36"))
IAsyncOperation<ABI::Microsoft::Windows::AI::Text::LanguageModel*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::LanguageModel*, ABI::Microsoft::Windows::AI::Text::ILanguageModel*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.AI.Text.LanguageModel>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Windows::AI::Text::LanguageModel*> __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("9be75163-9cd2-5a27-8f31-6d6beae7629a"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Text::LanguageModel*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::LanguageModel*, ABI::Microsoft::Windows::AI::Text::ILanguageModel*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.AI.Text.LanguageModel>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Text::LanguageModel*> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

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
                namespace Text {
                    class LanguageModelResponseResult;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_USE
#define DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("f936a4d3-cdb2-5356-adc5-adb43b59a6bc"))
IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::AI::Text::LanguageModelResponseResult*, HSTRING> : IAsyncOperationWithProgressCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::LanguageModelResponseResult*, ABI::Microsoft::Windows::AI::Text::ILanguageModelResponseResult*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationWithProgressCompletedHandler`2<Microsoft.Windows.AI.Text.LanguageModelResponseResult, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::AI::Text::LanguageModelResponseResult*, HSTRING> __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_t;
#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING ABI::Windows::Foundation::__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_USE
#define DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("5aec37a6-a5fa-5c0d-9da7-7614e0b4ed76"))
IAsyncOperationWithProgress<ABI::Microsoft::Windows::AI::Text::LanguageModelResponseResult*, HSTRING> : IAsyncOperationWithProgress_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::LanguageModelResponseResult*, ABI::Microsoft::Windows::AI::Text::ILanguageModelResponseResult*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperationWithProgress`2<Microsoft.Windows.AI.Text.LanguageModelResponseResult, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgress<ABI::Microsoft::Windows::AI::Text::LanguageModelResponseResult*, HSTRING> __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_t;
#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING ABI::Windows::Foundation::__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_USE
#define DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("f4a5a68d-50cf-502d-84e5-f41c62830b58"))
IAsyncOperationProgressHandler<ABI::Microsoft::Windows::AI::Text::LanguageModelResponseResult*, HSTRING> : IAsyncOperationProgressHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::LanguageModelResponseResult*, ABI::Microsoft::Windows::AI::Text::ILanguageModelResponseResult*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationProgressHandler`2<Microsoft.Windows.AI.Text.LanguageModelResponseResult, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationProgressHandler<ABI::Microsoft::Windows::AI::Text::LanguageModelResponseResult*, HSTRING> __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_t;
#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING ABI::Windows::Foundation::__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class TextToTableResponseResult;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_USE
#define DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("1fab5408-2f63-54cd-b5d1-80224a632477"))
IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::AI::Text::TextToTableResponseResult*, HSTRING> : IAsyncOperationWithProgressCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::TextToTableResponseResult*, ABI::Microsoft::Windows::AI::Text::ITextToTableResponseResult*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationWithProgressCompletedHandler`2<Microsoft.Windows.AI.Text.TextToTableResponseResult, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::AI::Text::TextToTableResponseResult*, HSTRING> __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_t;
#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING ABI::Windows::Foundation::__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_USE
#define DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("cff503d4-0ecb-5924-acbf-796ca6c7d373"))
IAsyncOperationWithProgress<ABI::Microsoft::Windows::AI::Text::TextToTableResponseResult*, HSTRING> : IAsyncOperationWithProgress_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::TextToTableResponseResult*, ABI::Microsoft::Windows::AI::Text::ITextToTableResponseResult*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperationWithProgress`2<Microsoft.Windows.AI.Text.TextToTableResponseResult, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgress<ABI::Microsoft::Windows::AI::Text::TextToTableResponseResult*, HSTRING> __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_t;
#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING ABI::Windows::Foundation::__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_USE
#define DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("57351f20-f3a6-5410-8284-8c4ccbeee776"))
IAsyncOperationProgressHandler<ABI::Microsoft::Windows::AI::Text::TextToTableResponseResult*, HSTRING> : IAsyncOperationProgressHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::TextToTableResponseResult*, ABI::Microsoft::Windows::AI::Text::ITextToTableResponseResult*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationProgressHandler`2<Microsoft.Windows.AI.Text.TextToTableResponseResult, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationProgressHandler<ABI::Microsoft::Windows::AI::Text::TextToTableResponseResult*, HSTRING> __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_t;
#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING ABI::Windows::Foundation::__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Foundation {
                    class EmbeddingVector;
                } /* Foundation */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Foundation {
                    interface IEmbeddingVector;
                } /* Foundation */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector ABI::Microsoft::Windows::AI::Foundation::IEmbeddingVector

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__

#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("8bf09d27-f9e7-5478-9747-9dd91f872831"))
IIterator<ABI::Microsoft::Windows::AI::Foundation::EmbeddingVector*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Foundation::EmbeddingVector*, ABI::Microsoft::Windows::AI::Foundation::IEmbeddingVector*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.AI.Foundation.EmbeddingVector>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::AI::Foundation::EmbeddingVector*> __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_t;
#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_USE */

#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("3314d513-49dd-5f89-8402-a6b673818d80"))
IIterable<ABI::Microsoft::Windows::AI::Foundation::EmbeddingVector*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Foundation::EmbeddingVector*, ABI::Microsoft::Windows::AI::Foundation::IEmbeddingVector*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.AI.Foundation.EmbeddingVector>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::AI::Foundation::EmbeddingVector*> __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_t;
#define __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_USE */

#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class ConversationItem;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("c3ee8c8e-5e58-57c3-a87a-8dab3cf1d079"))
IIterator<ABI::Microsoft::Windows::AI::Text::ConversationItem*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::ConversationItem*, ABI::Microsoft::Windows::AI::Text::IConversationItem*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.AI.Text.ConversationItem>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::AI::Text::ConversationItem*> __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_t;
#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e42a9615-3b0e-5a95-8f46-33b5dca2e59c"))
IIterable<ABI::Microsoft::Windows::AI::Text::ConversationItem*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::ConversationItem*, ABI::Microsoft::Windows::AI::Text::IConversationItem*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.AI.Text.ConversationItem>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::AI::Text::ConversationItem*> __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_t;
#define __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("30811f60-718e-550e-b121-4ee1e955b472"))
IVectorView<ABI::Microsoft::Windows::AI::Foundation::EmbeddingVector*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Foundation::EmbeddingVector*, ABI::Microsoft::Windows::AI::Foundation::IEmbeddingVector*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.AI.Foundation.EmbeddingVector>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::AI::Foundation::EmbeddingVector*> __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_t;
#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_USE */

#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("639207c3-ae0c-5851-a501-2668decf1448"))
IVectorView<ABI::Microsoft::Windows::AI::Text::ConversationItem*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Text::ConversationItem*, ABI::Microsoft::Windows::AI::Text::IConversationItem*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.AI.Text.ConversationItem>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::AI::Text::ConversationItem*> __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_t;
#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_USE */

#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

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
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    typedef enum InputKind : int InputKind;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    typedef enum LanguageModelResponseStatus : int LanguageModelResponseStatus;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    typedef enum TextRewriteTone : int TextRewriteTone;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class ConversationSummaryOptions;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class LanguageModelContext;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class LanguageModelEmbeddingVectorResult;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class LanguageModelOptions;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class TextRewriter;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class TextSummarizer;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class TextToTableConverter;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    class TextToTableRow;
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.AI.Text.InputKind
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    enum InputKind : int
                    {
                        InputKind_GeneralConversation = 0,
                        InputKind_Email = 1,
                    };
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.Text.LanguageModelResponseStatus
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    enum LanguageModelResponseStatus : int
                    {
                        LanguageModelResponseStatus_Complete = 0,
                        LanguageModelResponseStatus_InProgress = 1,
                        LanguageModelResponseStatus_BlockedByPolicy = 2,
                        LanguageModelResponseStatus_PromptLargerThanContext = 3,
                        LanguageModelResponseStatus_PromptBlockedByContentModeration = 4,
                        LanguageModelResponseStatus_ResponseBlockedByContentModeration = 5,
                        LanguageModelResponseStatus_Error = 6,
                    };
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.Text.TextRewriteTone
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 6.0
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x60000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    enum TextRewriteTone : int
                    {
                        TextRewriteTone_Default = 0,
                        TextRewriteTone_General = 1,
                        TextRewriteTone_Casual = 2,
                        TextRewriteTone_Concise = 3,
                        TextRewriteTone_Formal = 4,
                    };
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.AI.Text.IConversationItem
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.ConversationItem
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_IConversationItem[] = L"Microsoft.Windows.AI.Text.IConversationItem";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("957b0b85-4d7e-5788-baae-af7cf256bb8e")
                    IConversationItem : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Participant(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Participant(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Message(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Message(
                            HSTRING value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IConversationItem = _uuidof(IConversationItem);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.IConversationSummaryOptions
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.ConversationSummaryOptions
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_IConversationSummaryOptions[] = L"Microsoft.Windows.AI.Text.IConversationSummaryOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("360bce9f-fd14-5d0e-bd24-fd78ed3038e6")
                    IConversationSummaryOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_InputKind(
                            ABI::Microsoft::Windows::AI::Text::InputKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_InputKind(
                            ABI::Microsoft::Windows::AI::Text::InputKind value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IncludeMessageCitations(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IncludeMessageCitations(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IncludeParticipantAttribution(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IncludeParticipantAttribution(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MaxKeyPoints(
                            UINT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MaxKeyPoints(
                            UINT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Language(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Language(
                            HSTRING value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IConversationSummaryOptions = _uuidof(IConversationSummaryOptions);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModel
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModel
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModel[] = L"Microsoft.Windows.AI.Text.ILanguageModel";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("6331c629-8c86-5bfe-8c4e-9ca5573cc14b")
                    ILanguageModel : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ILanguageModel = _uuidof(ILanguageModel);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModel2
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModel
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModel2[] = L"Microsoft.Windows.AI.Text.ILanguageModel2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("653b714e-f9b3-51cb-954f-5ea58f63ab89")
                    ILanguageModel2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GenerateResponseAsync(
                            HSTRING prompt,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GenerateResponseAsync2(
                            HSTRING prompt,
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GenerateResponseAsync3(
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelContext* context,
                            HSTRING prompt,
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GenerateResponseFromEmbeddingsAsync(
                            __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* promptEmbedding,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GenerateResponseFromEmbeddingsAsync2(
                            __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* promptEmbedding,
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GenerateResponseFromEmbeddingsAsync3(
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelContext* context,
                            __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* promptEmbedding,
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GenerateEmbeddingVectors(
                            HSTRING prompt,
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelEmbeddingVectorResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GenerateEmbeddingVectors2(
                            HSTRING prompt,
                            ABI::Microsoft::Windows::AI::ContentSafety::IContentFilterOptions* contentFilterOptions,
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelEmbeddingVectorResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetUsablePromptLength(
                            HSTRING prompt,
                            UINT64* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetUsablePromptLength2(
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelContext* context,
                            HSTRING prompt,
                            UINT64* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetVectorSpaceId(
                            GUID* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateContext(
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelContext** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateContext2(
                            HSTRING systemPrompt,
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelContext** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateContext3(
                            HSTRING systemPrompt,
                            ABI::Microsoft::Windows::AI::ContentSafety::IContentFilterOptions* contentFilterOptions,
                            ABI::Microsoft::Windows::AI::Text::ILanguageModelContext** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ILanguageModel2 = _uuidof(ILanguageModel2);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModelContext
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModelContext
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModelContext[] = L"Microsoft.Windows.AI.Text.ILanguageModelContext";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("518b305c-7b69-5a33-8129-d47d6b8eec4e")
                    ILanguageModelContext : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ILanguageModelContext = _uuidof(ILanguageModelContext);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModelEmbeddingVectorResult
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModelEmbeddingVectorResult
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModelEmbeddingVectorResult[] = L"Microsoft.Windows.AI.Text.ILanguageModelEmbeddingVectorResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("4dbdb154-ee3c-56f6-a40b-413e95bd5acb")
                    ILanguageModelEmbeddingVectorResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_EmbeddingVectors(
                            __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            ABI::Microsoft::Windows::AI::Text::LanguageModelResponseStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                            HRESULT* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ILanguageModelEmbeddingVectorResult = _uuidof(ILanguageModelEmbeddingVectorResult);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModelOptions
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModelOptions
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModelOptions[] = L"Microsoft.Windows.AI.Text.ILanguageModelOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("7f380003-5a09-5f1f-afb0-aa483e3670cc")
                    ILanguageModelOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Temperature(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Temperature(
                            FLOAT value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TopP(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TopP(
                            FLOAT value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TopK(
                            UINT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TopK(
                            UINT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ContentFilterOptions(
                            ABI::Microsoft::Windows::AI::ContentSafety::IContentFilterOptions** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ContentFilterOptions(
                            ABI::Microsoft::Windows::AI::ContentSafety::IContentFilterOptions* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ILanguageModelOptions = _uuidof(ILanguageModelOptions);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModelResponseResult
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModelResponseResult
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModelResponseResult[] = L"Microsoft.Windows.AI.Text.ILanguageModelResponseResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("3a256fff-a426-5d3b-8e4b-3ac84162471e")
                    ILanguageModelResponseResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Text(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            ABI::Microsoft::Windows::AI::Text::LanguageModelResponseStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                            HRESULT* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ILanguageModelResponseResult = _uuidof(ILanguageModelResponseResult);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModelStatics
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModel
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModelStatics[] = L"Microsoft.Windows.AI.Text.ILanguageModelStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("8f18f9af-6095-553b-8d9d-6bcc98026546")
                    ILanguageModelStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetReadyState(
                            ABI::Microsoft::Windows::AI::AIFeatureReadyState* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsureReadyAsync(
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateAsync(
                            __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ILanguageModelStatics = _uuidof(ILanguageModelStatics);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextRewriter
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextRewriter
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextRewriter[] = L"Microsoft.Windows.AI.Text.ITextRewriter";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("eb1e7cf0-e110-506c-b0ea-7a288d8e7778")
                    ITextRewriter : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE RewriteAsync(
                            HSTRING text,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextRewriter = _uuidof(ITextRewriter);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextRewriter2
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextRewriter
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextRewriter2[] = L"Microsoft.Windows.AI.Text.ITextRewriter2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("7937d261-13ce-5b24-b17c-fe5cd0be23b6")
                    ITextRewriter2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE RewriteAsync(
                            HSTRING text,
                            ABI::Microsoft::Windows::AI::Text::TextRewriteTone tone,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextRewriter2 = _uuidof(ITextRewriter2);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextRewriterFactory
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextRewriter
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextRewriterFactory[] = L"Microsoft.Windows.AI.Text.ITextRewriterFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("f452e60d-ef50-5bc9-b483-217d5b4e7151")
                    ITextRewriterFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::Windows::AI::Text::ILanguageModel* languageModel,
                            ABI::Microsoft::Windows::AI::Text::ITextRewriter** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextRewriterFactory = _uuidof(ITextRewriterFactory);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextSummarizer
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextSummarizer
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextSummarizer[] = L"Microsoft.Windows.AI.Text.ITextSummarizer";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("eef548c5-d7bc-50be-a8ab-29e241b78bd1")
                    ITextSummarizer : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE SummarizeAsync(
                            HSTRING text,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SummarizeParagraphAsync(
                            HSTRING text,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextSummarizer = _uuidof(ITextSummarizer);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextSummarizer2
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextSummarizer
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextSummarizer2[] = L"Microsoft.Windows.AI.Text.ITextSummarizer2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("9e20797d-1ff6-5295-8cb6-d48fb8ba483b")
                    ITextSummarizer2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE SummarizeConversationAsync(
                            __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* messages,
                            ABI::Microsoft::Windows::AI::Text::IConversationSummaryOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextSummarizer2 = _uuidof(ITextSummarizer2);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextSummarizer3
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 3.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextSummarizer
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x30000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextSummarizer3[] = L"Microsoft.Windows.AI.Text.ITextSummarizer3";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("493d32b9-dbc9-5d4b-802f-90473850500e")
                    ITextSummarizer3 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE IsPromptLargerThanContext(
                            UINT32 messagesLength,
                            ABI::Microsoft::Windows::AI::Text::IConversationItem** messages,
                            ABI::Microsoft::Windows::AI::Text::IConversationSummaryOptions* options,
                            UINT64* cutoffPosition,
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextSummarizer3 = _uuidof(ITextSummarizer3);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x30000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextSummarizer4
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextSummarizer
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextSummarizer4[] = L"Microsoft.Windows.AI.Text.ITextSummarizer4";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("5b7a28c0-7777-52e5-9934-b95b514cf535")
                    ITextSummarizer4 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE IsPromptLargerThanContext(
                            HSTRING text,
                            UINT64* cutoffPosition,
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextSummarizer4 = _uuidof(ITextSummarizer4);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextSummarizerFactory
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextSummarizer
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextSummarizerFactory[] = L"Microsoft.Windows.AI.Text.ITextSummarizerFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("b6a75913-4a1e-59e7-856a-ae7ab2383864")
                    ITextSummarizerFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::Windows::AI::Text::ILanguageModel* languageModel,
                            ABI::Microsoft::Windows::AI::Text::ITextSummarizer** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextSummarizerFactory = _uuidof(ITextSummarizerFactory);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextToTableConverter
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextToTableConverter
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextToTableConverter[] = L"Microsoft.Windows.AI.Text.ITextToTableConverter";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("a008d9ad-25ce-5a6b-9ceb-d8e95d04e10b")
                    ITextToTableConverter : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE ConvertAsync(
                            HSTRING text,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextToTableConverter = _uuidof(ITextToTableConverter);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextToTableConverterFactory
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextToTableConverter
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextToTableConverterFactory[] = L"Microsoft.Windows.AI.Text.ITextToTableConverterFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("bb84cbb5-19c8-5857-b65d-705aa1486404")
                    ITextToTableConverterFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::Windows::AI::Text::ILanguageModel* languageModel,
                            ABI::Microsoft::Windows::AI::Text::ITextToTableConverter** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextToTableConverterFactory = _uuidof(ITextToTableConverterFactory);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextToTableResponseResult
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextToTableResponseResult
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextToTableResponseResult[] = L"Microsoft.Windows.AI.Text.ITextToTableResponseResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("391fbf11-59cd-575d-834a-9ef823116f98")
                    ITextToTableResponseResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetRows(
                            UINT32* resultLength,
                            ABI::Microsoft::Windows::AI::Text::ITextToTableRow*** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            ABI::Microsoft::Windows::AI::Text::LanguageModelResponseStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                            HRESULT* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextToTableResponseResult = _uuidof(ITextToTableResponseResult);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextToTableRow
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextToTableRow
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextToTableRow[] = L"Microsoft.Windows.AI.Text.ITextToTableRow";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Text {
                    MIDL_INTERFACE("036294fe-e53c-5e66-93d2-7c92338db881")
                    ITextToTableRow : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetColumns(
                            UINT32* resultLength,
                            HSTRING** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextToTableRow = _uuidof(ITextToTableRow);
                } /* Text */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.ConversationItem
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.Text.TextIntelligenceContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.IConversationItem ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_ConversationItem_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_ConversationItem_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_ConversationItem[] = L"Microsoft.Windows.AI.Text.ConversationItem";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.ConversationSummaryOptions
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.Text.TextIntelligenceContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.IConversationSummaryOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_ConversationSummaryOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_ConversationSummaryOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_ConversationSummaryOptions[] = L"Microsoft.Windows.AI.Text.ConversationSummaryOptions";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.LanguageModel
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Text.ILanguageModelStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Text.LanguageModelContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ILanguageModel ** Default Interface **
 *    Microsoft.Windows.AI.Text.ILanguageModel2
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModel_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModel_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_LanguageModel[] = L"Microsoft.Windows.AI.Text.LanguageModel";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.LanguageModelContext
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ILanguageModelContext ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelContext_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelContext_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_LanguageModelContext[] = L"Microsoft.Windows.AI.Text.LanguageModelContext";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.LanguageModelEmbeddingVectorResult
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 2.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ILanguageModelEmbeddingVectorResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelEmbeddingVectorResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelEmbeddingVectorResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_LanguageModelEmbeddingVectorResult[] = L"Microsoft.Windows.AI.Text.LanguageModelEmbeddingVectorResult";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.AI.Text.LanguageModelOptions
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.Text.LanguageModelContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ILanguageModelOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_LanguageModelOptions[] = L"Microsoft.Windows.AI.Text.LanguageModelOptions";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.LanguageModelResponseResult
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ILanguageModelResponseResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelResponseResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelResponseResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_LanguageModelResponseResult[] = L"Microsoft.Windows.AI.Text.LanguageModelResponseResult";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.TextRewriter
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.Text.ITextRewriterFactory interface starting with version 1.0 of the Microsoft.Windows.AI.Text.TextIntelligenceContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ITextRewriter ** Default Interface **
 *    Microsoft.Windows.AI.Text.ITextRewriter2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_TextRewriter_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_TextRewriter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_TextRewriter[] = L"Microsoft.Windows.AI.Text.TextRewriter";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.TextSummarizer
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 2.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.Text.ITextSummarizerFactory interface starting with version 2.0 of the Microsoft.Windows.AI.Text.TextIntelligenceContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ITextSummarizer ** Default Interface **
 *    Microsoft.Windows.AI.Text.ITextSummarizer2
 *    Microsoft.Windows.AI.Text.ITextSummarizer3
 *    Microsoft.Windows.AI.Text.ITextSummarizer4
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_TextSummarizer_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_TextSummarizer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_TextSummarizer[] = L"Microsoft.Windows.AI.Text.TextSummarizer";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.AI.Text.TextToTableConverter
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.Text.ITextToTableConverterFactory interface starting with version 1.0 of the Microsoft.Windows.AI.Text.TextIntelligenceContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ITextToTableConverter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableConverter_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableConverter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_TextToTableConverter[] = L"Microsoft.Windows.AI.Text.TextToTableConverter";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.TextToTableResponseResult
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ITextToTableResponseResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableResponseResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableResponseResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_TextToTableResponseResult[] = L"Microsoft.Windows.AI.Text.TextToTableResponseResult";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.TextToTableRow
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ITextToTableRow ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableRow_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableRow_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_TextToTableRow[] = L"Microsoft.Windows.AI.Text.TextToTableRow";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2 __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2 __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2 __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3 __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4 __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel;

#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModelVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModelVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModelVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModelVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModelVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModelVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CText__CLanguageModel_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

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

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING;

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING;

#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING;

typedef struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRINGVtbl;

interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING
{
    CONST_VTBL struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING;

typedef struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* handler);
    HRESULT (STDMETHODCALLTYPE* get_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult** result);

    END_INTERFACE
} __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRINGVtbl;

interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING
{
    CONST_VTBL struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_put_Progress(This, handler) \
    ((This)->lpVtbl->put_Progress(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_get_Progress(This, result) \
    ((This)->lpVtbl->get_Progress(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_INTERFACE_DEFINED__)
#define ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING;

typedef struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING* asyncInfo,
        HSTRING progressInfo);

    END_INTERFACE
} __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRINGVtbl;

interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING
{
    CONST_VTBL struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_Invoke(This, asyncInfo, progressInfo) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, progressInfo))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING;

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING;

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING;

typedef struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRINGVtbl;

interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING
{
    CONST_VTBL struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING;

typedef struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* handler);
    HRESULT (STDMETHODCALLTYPE* get_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult** result);

    END_INTERFACE
} __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRINGVtbl;

interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING
{
    CONST_VTBL struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_put_Progress(This, handler) \
    ((This)->lpVtbl->put_Progress(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_get_Progress(This, result) \
    ((This)->lpVtbl->get_Progress(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_INTERFACE_DEFINED__)
#define ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING;

typedef struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING* asyncInfo,
        HSTRING progressInfo);

    END_INTERFACE
} __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRINGVtbl;

interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING
{
    CONST_VTBL struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_Invoke(This, asyncInfo, progressInfo) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, progressInfo))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__

#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector;

typedef struct __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVectorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVectorVtbl;

interface __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVectorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector;

typedef struct __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVectorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        __FIIterator_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVectorVtbl;

interface __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVectorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem;

typedef struct __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItemVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItemVtbl;

interface __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItemVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem;

typedef struct __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItemVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        __FIIterator_1_Microsoft__CWindows__CAI__CText__CConversationItem** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItemVtbl;

interface __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItemVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CAI__CText__CConversationItem_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector;

typedef struct __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVectorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVectorVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVectorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem;

typedef struct __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItemVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItemVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItemVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState;

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CInputKind __x_ABI_CMicrosoft_CWindows_CAI_CText_CInputKind;

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CLanguageModelResponseStatus __x_ABI_CMicrosoft_CWindows_CAI_CText_CLanguageModelResponseStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CTextRewriteTone __x_ABI_CMicrosoft_CWindows_CAI_CText_CTextRewriteTone;

/*
 *
 * Struct Microsoft.Windows.AI.Text.InputKind
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CInputKind
{
    InputKind_GeneralConversation = 0,
    InputKind_Email = 1,
};
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.Text.LanguageModelResponseStatus
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CLanguageModelResponseStatus
{
    LanguageModelResponseStatus_Complete = 0,
    LanguageModelResponseStatus_InProgress = 1,
    LanguageModelResponseStatus_BlockedByPolicy = 2,
    LanguageModelResponseStatus_PromptLargerThanContext = 3,
    LanguageModelResponseStatus_PromptBlockedByContentModeration = 4,
    LanguageModelResponseStatus_ResponseBlockedByContentModeration = 5,
    LanguageModelResponseStatus_Error = 6,
};
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.Text.TextRewriteTone
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 6.0
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x60000
enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CTextRewriteTone
{
    TextRewriteTone_Default = 0,
    TextRewriteTone_General = 1,
    TextRewriteTone_Casual = 2,
    TextRewriteTone_Concise = 3,
    TextRewriteTone_Formal = 4,
};
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.AI.Text.IConversationItem
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.ConversationItem
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_IConversationItem[] = L"Microsoft.Windows.AI.Text.IConversationItem";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItemVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Participant)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Participant)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Message)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Message)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem* This,
        HSTRING value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItemVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItemVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_get_Participant(This, value) \
    ((This)->lpVtbl->get_Participant(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_put_Participant(This, value) \
    ((This)->lpVtbl->put_Participant(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_get_Message(This, value) \
    ((This)->lpVtbl->get_Message(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_put_Message(This, value) \
    ((This)->lpVtbl->put_Message(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.IConversationSummaryOptions
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.ConversationSummaryOptions
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_IConversationSummaryOptions[] = L"Microsoft.Windows.AI.Text.IConversationSummaryOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_InputKind)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CInputKind* value);
    HRESULT (STDMETHODCALLTYPE* put_InputKind)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CInputKind value);
    HRESULT (STDMETHODCALLTYPE* get_IncludeMessageCitations)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IncludeMessageCitations)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IncludeParticipantAttribution)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IncludeParticipantAttribution)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_MaxKeyPoints)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        UINT32* value);
    HRESULT (STDMETHODCALLTYPE* put_MaxKeyPoints)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        UINT32 value);
    HRESULT (STDMETHODCALLTYPE* get_Language)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Language)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* This,
        HSTRING value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_get_InputKind(This, value) \
    ((This)->lpVtbl->get_InputKind(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_put_InputKind(This, value) \
    ((This)->lpVtbl->put_InputKind(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_get_IncludeMessageCitations(This, value) \
    ((This)->lpVtbl->get_IncludeMessageCitations(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_put_IncludeMessageCitations(This, value) \
    ((This)->lpVtbl->put_IncludeMessageCitations(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_get_IncludeParticipantAttribution(This, value) \
    ((This)->lpVtbl->get_IncludeParticipantAttribution(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_put_IncludeParticipantAttribution(This, value) \
    ((This)->lpVtbl->put_IncludeParticipantAttribution(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_get_MaxKeyPoints(This, value) \
    ((This)->lpVtbl->get_MaxKeyPoints(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_put_MaxKeyPoints(This, value) \
    ((This)->lpVtbl->put_MaxKeyPoints(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_get_Language(This, value) \
    ((This)->lpVtbl->get_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_put_Language(This, value) \
    ((This)->lpVtbl->put_Language(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModel
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModel
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModel[] = L"Microsoft.Windows.AI.Text.ILanguageModel";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModel2
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModel
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModel2[] = L"Microsoft.Windows.AI.Text.ILanguageModel2";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GenerateResponseAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        HSTRING prompt,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);
    HRESULT (STDMETHODCALLTYPE* GenerateResponseAsync2)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        HSTRING prompt,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);
    HRESULT (STDMETHODCALLTYPE* GenerateResponseAsync3)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext* context,
        HSTRING prompt,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);
    HRESULT (STDMETHODCALLTYPE* GenerateResponseFromEmbeddingsAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* promptEmbedding,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);
    HRESULT (STDMETHODCALLTYPE* GenerateResponseFromEmbeddingsAsync2)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* promptEmbedding,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);
    HRESULT (STDMETHODCALLTYPE* GenerateResponseFromEmbeddingsAsync3)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext* context,
        __FIIterable_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector* promptEmbedding,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);
    HRESULT (STDMETHODCALLTYPE* GenerateEmbeddingVectors)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        HSTRING prompt,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult** result);
    HRESULT (STDMETHODCALLTYPE* GenerateEmbeddingVectors2)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        HSTRING prompt,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* contentFilterOptions,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult** result);
    HRESULT (STDMETHODCALLTYPE* GetUsablePromptLength)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        HSTRING prompt,
        UINT64* result);
    HRESULT (STDMETHODCALLTYPE* GetUsablePromptLength2)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext* context,
        HSTRING prompt,
        UINT64* result);
    HRESULT (STDMETHODCALLTYPE* GetVectorSpaceId)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        GUID* result);
    HRESULT (STDMETHODCALLTYPE* CreateContext)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext** result);
    HRESULT (STDMETHODCALLTYPE* CreateContext2)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        HSTRING systemPrompt,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext** result);
    HRESULT (STDMETHODCALLTYPE* CreateContext3)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2* This,
        HSTRING systemPrompt,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* contentFilterOptions,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GenerateResponseAsync(This, prompt, operation) \
    ((This)->lpVtbl->GenerateResponseAsync(This, prompt, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GenerateResponseAsync2(This, prompt, options, operation) \
    ((This)->lpVtbl->GenerateResponseAsync2(This, prompt, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GenerateResponseAsync3(This, context, prompt, options, operation) \
    ((This)->lpVtbl->GenerateResponseAsync3(This, context, prompt, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GenerateResponseFromEmbeddingsAsync(This, promptEmbedding, operation) \
    ((This)->lpVtbl->GenerateResponseFromEmbeddingsAsync(This, promptEmbedding, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GenerateResponseFromEmbeddingsAsync2(This, promptEmbedding, options, operation) \
    ((This)->lpVtbl->GenerateResponseFromEmbeddingsAsync2(This, promptEmbedding, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GenerateResponseFromEmbeddingsAsync3(This, context, promptEmbedding, options, operation) \
    ((This)->lpVtbl->GenerateResponseFromEmbeddingsAsync3(This, context, promptEmbedding, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GenerateEmbeddingVectors(This, prompt, result) \
    ((This)->lpVtbl->GenerateEmbeddingVectors(This, prompt, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GenerateEmbeddingVectors2(This, prompt, contentFilterOptions, result) \
    ((This)->lpVtbl->GenerateEmbeddingVectors2(This, prompt, contentFilterOptions, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GetUsablePromptLength(This, prompt, result) \
    ((This)->lpVtbl->GetUsablePromptLength(This, prompt, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GetUsablePromptLength2(This, context, prompt, result) \
    ((This)->lpVtbl->GetUsablePromptLength2(This, context, prompt, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_GetVectorSpaceId(This, result) \
    ((This)->lpVtbl->GetVectorSpaceId(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_CreateContext(This, result) \
    ((This)->lpVtbl->CreateContext(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_CreateContext2(This, systemPrompt, result) \
    ((This)->lpVtbl->CreateContext2(This, systemPrompt, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_CreateContext3(This, systemPrompt, contentFilterOptions, result) \
    ((This)->lpVtbl->CreateContext3(This, systemPrompt, contentFilterOptions, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModelContext
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModelContext
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModelContext[] = L"Microsoft.Windows.AI.Text.ILanguageModelContext";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContextVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContextVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContextVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelContext_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModelEmbeddingVectorResult
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModelEmbeddingVectorResult
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModelEmbeddingVectorResult[] = L"Microsoft.Windows.AI.Text.ILanguageModelEmbeddingVectorResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_EmbeddingVectors)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult* This,
        __FIVectorView_1_Microsoft__CWindows__CAI__CFoundation__CEmbeddingVector** value);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CLanguageModelResponseStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult* This,
        HRESULT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_get_EmbeddingVectors(This, value) \
    ((This)->lpVtbl->get_EmbeddingVectors(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelEmbeddingVectorResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModelOptions
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModelOptions
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModelOptions[] = L"Microsoft.Windows.AI.Text.ILanguageModelOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Temperature)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_Temperature)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_TopP)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_TopP)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_TopK)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        UINT32* value);
    HRESULT (STDMETHODCALLTYPE* put_TopK)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        UINT32 value);
    HRESULT (STDMETHODCALLTYPE* get_ContentFilterOptions)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions** value);
    HRESULT (STDMETHODCALLTYPE* put_ContentFilterOptions)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_get_Temperature(This, value) \
    ((This)->lpVtbl->get_Temperature(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_put_Temperature(This, value) \
    ((This)->lpVtbl->put_Temperature(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_get_TopP(This, value) \
    ((This)->lpVtbl->get_TopP(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_put_TopP(This, value) \
    ((This)->lpVtbl->put_TopP(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_get_TopK(This, value) \
    ((This)->lpVtbl->get_TopK(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_put_TopK(This, value) \
    ((This)->lpVtbl->put_TopK(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_get_ContentFilterOptions(This, value) \
    ((This)->lpVtbl->get_ContentFilterOptions(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_put_ContentFilterOptions(This, value) \
    ((This)->lpVtbl->put_ContentFilterOptions(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModelResponseResult
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModelResponseResult
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModelResponseResult[] = L"Microsoft.Windows.AI.Text.ILanguageModelResponseResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Text)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CLanguageModelResponseStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult* This,
        HRESULT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_get_Text(This, value) \
    ((This)->lpVtbl->get_Text(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelResponseResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ILanguageModelStatics
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.LanguageModel
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ILanguageModelStatics[] = L"Microsoft.Windows.AI.Text.ILanguageModelStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetReadyState)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState* result);
    HRESULT (STDMETHODCALLTYPE* EnsureReadyAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation);
    HRESULT (STDMETHODCALLTYPE* CreateAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CText__CLanguageModel** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_GetReadyState(This, result) \
    ((This)->lpVtbl->GetReadyState(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_EnsureReadyAsync(This, operation) \
    ((This)->lpVtbl->EnsureReadyAsync(This, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_CreateAsync(This, operation) \
    ((This)->lpVtbl->CreateAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModelStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextRewriter
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextRewriter
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextRewriter[] = L"Microsoft.Windows.AI.Text.ITextRewriter";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* RewriteAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter* This,
        HSTRING text,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_RewriteAsync(This, text, operation) \
    ((This)->lpVtbl->RewriteAsync(This, text, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextRewriter2
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextRewriter
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextRewriter2[] = L"Microsoft.Windows.AI.Text.ITextRewriter2";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* RewriteAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2* This,
        HSTRING text,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CTextRewriteTone tone,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_RewriteAsync(This, text, tone, operation) \
    ((This)->lpVtbl->RewriteAsync(This, text, tone, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextRewriterFactory
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextRewriter
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextRewriterFactory[] = L"Microsoft.Windows.AI.Text.ITextRewriterFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel* languageModel,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriter** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_CreateInstance(This, languageModel, value) \
    ((This)->lpVtbl->CreateInstance(This, languageModel, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextRewriterFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextSummarizer
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextSummarizer
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextSummarizer[] = L"Microsoft.Windows.AI.Text.ITextSummarizer";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* SummarizeAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer* This,
        HSTRING text,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);
    HRESULT (STDMETHODCALLTYPE* SummarizeParagraphAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer* This,
        HSTRING text,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_SummarizeAsync(This, text, operation) \
    ((This)->lpVtbl->SummarizeAsync(This, text, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_SummarizeParagraphAsync(This, text, operation) \
    ((This)->lpVtbl->SummarizeParagraphAsync(This, text, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextSummarizer2
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextSummarizer
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextSummarizer2[] = L"Microsoft.Windows.AI.Text.ITextSummarizer2";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* SummarizeConversationAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2* This,
        __FIVectorView_1_Microsoft__CWindows__CAI__CText__CConversationItem* messages,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CLanguageModelResponseResult_HSTRING** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_SummarizeConversationAsync(This, messages, options, operation) \
    ((This)->lpVtbl->SummarizeConversationAsync(This, messages, options, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextSummarizer3
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 3.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextSummarizer
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x30000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextSummarizer3[] = L"Microsoft.Windows.AI.Text.ITextSummarizer3";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsPromptLargerThanContext)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3* This,
        UINT32 messagesLength,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationItem** messages,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CIConversationSummaryOptions* options,
        UINT64* cutoffPosition,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_IsPromptLargerThanContext(This, messagesLength, messages, options, cutoffPosition, result) \
    ((This)->lpVtbl->IsPromptLargerThanContext(This, messagesLength, messages, options, cutoffPosition, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x30000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextSummarizer4
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextSummarizer
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextSummarizer4[] = L"Microsoft.Windows.AI.Text.ITextSummarizer4";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsPromptLargerThanContext)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4* This,
        HSTRING text,
        UINT64* cutoffPosition,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_IsPromptLargerThanContext(This, text, cutoffPosition, result) \
    ((This)->lpVtbl->IsPromptLargerThanContext(This, text, cutoffPosition, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer4_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextSummarizerFactory
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextSummarizer
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextSummarizerFactory[] = L"Microsoft.Windows.AI.Text.ITextSummarizerFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel* languageModel,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizer** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_CreateInstance(This, languageModel, value) \
    ((This)->lpVtbl->CreateInstance(This, languageModel, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextSummarizerFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextToTableConverter
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextToTableConverter
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextToTableConverter[] = L"Microsoft.Windows.AI.Text.ITextToTableConverter";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ConvertAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter* This,
        HSTRING text,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CText__CTextToTableResponseResult_HSTRING** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_ConvertAsync(This, text, operation) \
    ((This)->lpVtbl->ConvertAsync(This, text, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextToTableConverterFactory
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextToTableConverter
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextToTableConverterFactory[] = L"Microsoft.Windows.AI.Text.ITextToTableConverterFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CILanguageModel* languageModel,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverter** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_CreateInstance(This, languageModel, value) \
    ((This)->lpVtbl->CreateInstance(This, languageModel, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableConverterFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextToTableResponseResult
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextToTableResponseResult
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextToTableResponseResult[] = L"Microsoft.Windows.AI.Text.ITextToTableResponseResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetRows)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow*** result);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CText_CLanguageModelResponseStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult* This,
        HRESULT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_GetRows(This, resultLength, result) \
    ((This)->lpVtbl->GetRows(This, resultLength, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableResponseResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Text.ITextToTableRow
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Text.TextToTableRow
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Text_ITextToTableRow[] = L"Microsoft.Windows.AI.Text.ITextToTableRow";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRowVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetColumns)(__x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow* This,
        UINT32* resultLength,
        HSTRING** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRowVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRowVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_GetColumns(This, resultLength, result) \
    ((This)->lpVtbl->GetColumns(This, resultLength, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CText_CITextToTableRow_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.ConversationItem
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.Text.TextIntelligenceContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.IConversationItem ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_ConversationItem_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_ConversationItem_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_ConversationItem[] = L"Microsoft.Windows.AI.Text.ConversationItem";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.ConversationSummaryOptions
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.Text.TextIntelligenceContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.IConversationSummaryOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_ConversationSummaryOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_ConversationSummaryOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_ConversationSummaryOptions[] = L"Microsoft.Windows.AI.Text.ConversationSummaryOptions";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.LanguageModel
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AI.Text.ILanguageModelStatics interface starting with version 1.0 of the Microsoft.Windows.AI.Text.LanguageModelContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ILanguageModel ** Default Interface **
 *    Microsoft.Windows.AI.Text.ILanguageModel2
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModel_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModel_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_LanguageModel[] = L"Microsoft.Windows.AI.Text.LanguageModel";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.LanguageModelContext
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ILanguageModelContext ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelContext_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelContext_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_LanguageModelContext[] = L"Microsoft.Windows.AI.Text.LanguageModelContext";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.LanguageModelEmbeddingVectorResult
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 2.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ILanguageModelEmbeddingVectorResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelEmbeddingVectorResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelEmbeddingVectorResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_LanguageModelEmbeddingVectorResult[] = L"Microsoft.Windows.AI.Text.LanguageModelEmbeddingVectorResult";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.AI.Text.LanguageModelOptions
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.Text.LanguageModelContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ILanguageModelOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_LanguageModelOptions[] = L"Microsoft.Windows.AI.Text.LanguageModelOptions";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.LanguageModelResponseResult
 *
 * Introduced to Microsoft.Windows.AI.Text.LanguageModelContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ILanguageModelResponseResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelResponseResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_LanguageModelResponseResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_LanguageModelResponseResult[] = L"Microsoft.Windows.AI.Text.LanguageModelResponseResult";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_LANGUAGEMODELCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.TextRewriter
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.Text.ITextRewriterFactory interface starting with version 1.0 of the Microsoft.Windows.AI.Text.TextIntelligenceContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ITextRewriter ** Default Interface **
 *    Microsoft.Windows.AI.Text.ITextRewriter2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_TextRewriter_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_TextRewriter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_TextRewriter[] = L"Microsoft.Windows.AI.Text.TextRewriter";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.TextSummarizer
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 2.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.Text.ITextSummarizerFactory interface starting with version 2.0 of the Microsoft.Windows.AI.Text.TextIntelligenceContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ITextSummarizer ** Default Interface **
 *    Microsoft.Windows.AI.Text.ITextSummarizer2
 *    Microsoft.Windows.AI.Text.ITextSummarizer3
 *    Microsoft.Windows.AI.Text.ITextSummarizer4
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_TextSummarizer_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_TextSummarizer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_TextSummarizer[] = L"Microsoft.Windows.AI.Text.TextSummarizer";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.AI.Text.TextToTableConverter
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.Text.ITextToTableConverterFactory interface starting with version 1.0 of the Microsoft.Windows.AI.Text.TextIntelligenceContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ITextToTableConverter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableConverter_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableConverter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_TextToTableConverter[] = L"Microsoft.Windows.AI.Text.TextToTableConverter";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.TextToTableResponseResult
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ITextToTableResponseResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableResponseResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableResponseResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_TextToTableResponseResult[] = L"Microsoft.Windows.AI.Text.TextToTableResponseResult";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Text.TextToTableRow
 *
 * Introduced to Microsoft.Windows.AI.Text.TextIntelligenceContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Text.ITextToTableRow ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableRow_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Text_TextToTableRow_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Text_TextToTableRow[] = L"Microsoft.Windows.AI.Text.TextToTableRow";
#endif
#endif // MICROSOFT_WINDOWS_AI_TEXT_TEXTINTELLIGENCECONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eai2Etext_p_h__

#endif // __microsoft2Ewindows2Eai2Etext_h__
