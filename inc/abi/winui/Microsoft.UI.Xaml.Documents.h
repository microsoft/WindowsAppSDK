
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
#ifndef __microsoft2Eui2Examl2Edocuments_h__
#define __microsoft2Eui2Examl2Edocuments_h__
#ifndef __microsoft2Eui2Examl2Edocuments_p_h__
#define __microsoft2Eui2Examl2Edocuments_p_h__


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
#include "Microsoft.UI.Xaml.Input.h"
#include "Microsoft.UI.Xaml.Media.h"
#include "Windows.UI.Text.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IBlock;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock ABI::Microsoft::UI::Xaml::Documents::IBlock

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IBlockFactory;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory ABI::Microsoft::UI::Xaml::Documents::IBlockFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IBlockStatics;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics ABI::Microsoft::UI::Xaml::Documents::IBlockStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IBold;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold ABI::Microsoft::UI::Xaml::Documents::IBold

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IGlyphs;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs ABI::Microsoft::UI::Xaml::Documents::IGlyphs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IGlyphsStatics;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics ABI::Microsoft::UI::Xaml::Documents::IGlyphsStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IHyperlink;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink ABI::Microsoft::UI::Xaml::Documents::IHyperlink

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IHyperlinkClickEventArgs;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs ABI::Microsoft::UI::Xaml::Documents::IHyperlinkClickEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IHyperlinkStatics;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics ABI::Microsoft::UI::Xaml::Documents::IHyperlinkStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IInline;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline ABI::Microsoft::UI::Xaml::Documents::IInline

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IInlineFactory;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory ABI::Microsoft::UI::Xaml::Documents::IInlineFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IInlineUIContainer;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer ABI::Microsoft::UI::Xaml::Documents::IInlineUIContainer

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IItalic;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic ABI::Microsoft::UI::Xaml::Documents::IItalic

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ILineBreak;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak ABI::Microsoft::UI::Xaml::Documents::ILineBreak

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IParagraph;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph ABI::Microsoft::UI::Xaml::Documents::IParagraph

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IParagraphStatics;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics ABI::Microsoft::UI::Xaml::Documents::IParagraphStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IRun;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun ABI::Microsoft::UI::Xaml::Documents::IRun

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IRunStatics;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics ABI::Microsoft::UI::Xaml::Documents::IRunStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ISpan;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan ABI::Microsoft::UI::Xaml::Documents::ISpan

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ISpanFactory;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory ABI::Microsoft::UI::Xaml::Documents::ISpanFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITextElement;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement ABI::Microsoft::UI::Xaml::Documents::ITextElement

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITextElementFactory;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory ABI::Microsoft::UI::Xaml::Documents::ITextElementFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITextElementOverrides;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides ABI::Microsoft::UI::Xaml::Documents::ITextElementOverrides

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITextElementStatics;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics ABI::Microsoft::UI::Xaml::Documents::ITextElementStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITextHighlighter;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter ABI::Microsoft::UI::Xaml::Documents::ITextHighlighter

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITextHighlighterBase;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase ABI::Microsoft::UI::Xaml::Documents::ITextHighlighterBase

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITextHighlighterBaseFactory;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory ABI::Microsoft::UI::Xaml::Documents::ITextHighlighterBaseFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITextHighlighterFactory;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory ABI::Microsoft::UI::Xaml::Documents::ITextHighlighterFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITextHighlighterStatics;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics ABI::Microsoft::UI::Xaml::Documents::ITextHighlighterStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITextPointer;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer ABI::Microsoft::UI::Xaml::Documents::ITextPointer

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITypography;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography ABI::Microsoft::UI::Xaml::Documents::ITypography

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface ITypographyStatics;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics ABI::Microsoft::UI::Xaml::Documents::ITypographyStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    interface IUnderline;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline ABI::Microsoft::UI::Xaml::Documents::IUnderline

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    class Block;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE
#define DEF___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ef1efd95-828d-5c71-99d7-c23511a15088"))
IIterator<ABI::Microsoft::UI::Xaml::Documents::Block*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::Block*, ABI::Microsoft::UI::Xaml::Documents::IBlock*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Xaml.Documents.Block>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Xaml::Documents::Block*> __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_t;
#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE
#define DEF___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("882ba702-d0f7-54dd-994a-5560a252f1e5"))
IIterable<ABI::Microsoft::UI::Xaml::Documents::Block*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::Block*, ABI::Microsoft::UI::Xaml::Documents::IBlock*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Xaml.Documents.Block>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Xaml::Documents::Block*> __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_t;
#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    class Inline;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE
#define DEF___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("86e55d23-6538-5ca8-b944-d663e11a5120"))
IIterator<ABI::Microsoft::UI::Xaml::Documents::Inline*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::Inline*, ABI::Microsoft::UI::Xaml::Documents::IInline*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Xaml.Documents.Inline>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Xaml::Documents::Inline*> __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_t;
#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE
#define DEF___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("f86f5da2-1896-5eed-aa75-a07476952dbf"))
IIterable<ABI::Microsoft::UI::Xaml::Documents::Inline*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::Inline*, ABI::Microsoft::UI::Xaml::Documents::IInline*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Xaml.Documents.Inline>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Xaml::Documents::Inline*> __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_t;
#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    typedef struct TextRange TextRange;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE
#define DEF___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("c70c1944-933a-5ae4-bb65-93acfc3f3c40"))
IIterator<struct ABI::Microsoft::UI::Xaml::Documents::TextRange> : IIterator_impl<struct ABI::Microsoft::UI::Xaml::Documents::TextRange>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Xaml.Documents.TextRange>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<struct ABI::Microsoft::UI::Xaml::Documents::TextRange> __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_t;
#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE
#define DEF___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("078dc9d3-4f5e-5ab0-a784-722a4b1fcb01"))
IIterable<struct ABI::Microsoft::UI::Xaml::Documents::TextRange> : IIterable_impl<struct ABI::Microsoft::UI::Xaml::Documents::TextRange>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Xaml.Documents.TextRange>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<struct ABI::Microsoft::UI::Xaml::Documents::TextRange> __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_t;
#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE
#define DEF___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("de239cd0-1c4d-5911-875a-e8a5c022e05b"))
IVectorView<ABI::Microsoft::UI::Xaml::Documents::Block*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::Block*, ABI::Microsoft::UI::Xaml::Documents::IBlock*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.UI.Xaml.Documents.Block>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::UI::Xaml::Documents::Block*> __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_t;
#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE
#define DEF___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b0525fd0-f83c-54a4-bc08-f2574b42c536"))
IVectorView<ABI::Microsoft::UI::Xaml::Documents::Inline*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::Inline*, ABI::Microsoft::UI::Xaml::Documents::IInline*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.UI.Xaml.Documents.Inline>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::UI::Xaml::Documents::Inline*> __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_t;
#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE
#define DEF___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("9d4ea607-632b-50f1-9539-dde98c1eed29"))
IVectorView<struct ABI::Microsoft::UI::Xaml::Documents::TextRange> : IVectorView_impl<struct ABI::Microsoft::UI::Xaml::Documents::TextRange>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.UI.Xaml.Documents.TextRange>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<struct ABI::Microsoft::UI::Xaml::Documents::TextRange> __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_t;
#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE
#define DEF___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("d728dc59-5a96-5849-9009-7da7cbb392eb"))
IVector<ABI::Microsoft::UI::Xaml::Documents::Block*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::Block*, ABI::Microsoft::UI::Xaml::Documents::IBlock*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.UI.Xaml.Documents.Block>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Microsoft::UI::Xaml::Documents::Block*> __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_t;
#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE
#define DEF___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("0015a441-4c98-5d3f-8823-03e722615c48"))
IVector<ABI::Microsoft::UI::Xaml::Documents::Inline*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::Inline*, ABI::Microsoft::UI::Xaml::Documents::IInline*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.UI.Xaml.Documents.Inline>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Microsoft::UI::Xaml::Documents::Inline*> __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_t;
#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE
#define DEF___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("5338571c-77b4-560e-8dfd-a59dad270ebb"))
IVector<struct ABI::Microsoft::UI::Xaml::Documents::TextRange> : IVector_impl<struct ABI::Microsoft::UI::Xaml::Documents::TextRange>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.UI.Xaml.Documents.TextRange>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<struct ABI::Microsoft::UI::Xaml::Documents::TextRange> __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_t;
#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    class Hyperlink;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    class HyperlinkClickEventArgs;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("40bc5de0-8921-5b61-94f6-aa56a0b540ce"))
ITypedEventHandler<ABI::Microsoft::UI::Xaml::Documents::Hyperlink*, ABI::Microsoft::UI::Xaml::Documents::HyperlinkClickEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::Hyperlink*, ABI::Microsoft::UI::Xaml::Documents::IHyperlink*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::HyperlinkClickEventArgs*, ABI::Microsoft::UI::Xaml::Documents::IHyperlinkClickEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Xaml.Documents.Hyperlink, Microsoft.UI.Xaml.Documents.HyperlinkClickEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Xaml::Documents::Hyperlink*, ABI::Microsoft::UI::Xaml::Documents::HyperlinkClickEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    class TextElement;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class AccessKeyDisplayDismissedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IAccessKeyDisplayDismissedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs ABI::Microsoft::UI::Xaml::Input::IAccessKeyDisplayDismissedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("459ee508-eb51-5eab-9fd9-865afada06c7"))
ITypedEventHandler<ABI::Microsoft::UI::Xaml::Documents::TextElement*, ABI::Microsoft::UI::Xaml::Input::AccessKeyDisplayDismissedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::TextElement*, ABI::Microsoft::UI::Xaml::Documents::ITextElement*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::AccessKeyDisplayDismissedEventArgs*, ABI::Microsoft::UI::Xaml::Input::IAccessKeyDisplayDismissedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Xaml.Documents.TextElement, Microsoft.UI.Xaml.Input.AccessKeyDisplayDismissedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Xaml::Documents::TextElement*, ABI::Microsoft::UI::Xaml::Input::AccessKeyDisplayDismissedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class AccessKeyDisplayRequestedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IAccessKeyDisplayRequestedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs ABI::Microsoft::UI::Xaml::Input::IAccessKeyDisplayRequestedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("d2ff7f87-74c6-5a26-83f3-7cc6e5e8a54d"))
ITypedEventHandler<ABI::Microsoft::UI::Xaml::Documents::TextElement*, ABI::Microsoft::UI::Xaml::Input::AccessKeyDisplayRequestedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::TextElement*, ABI::Microsoft::UI::Xaml::Documents::ITextElement*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::AccessKeyDisplayRequestedEventArgs*, ABI::Microsoft::UI::Xaml::Input::IAccessKeyDisplayRequestedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Xaml.Documents.TextElement, Microsoft.UI.Xaml.Input.AccessKeyDisplayRequestedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Xaml::Documents::TextElement*, ABI::Microsoft::UI::Xaml::Input::AccessKeyDisplayRequestedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class AccessKeyInvokedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IAccessKeyInvokedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs ABI::Microsoft::UI::Xaml::Input::IAccessKeyInvokedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("60ef1dd7-8842-50f8-bc5c-e0c9182ef2d5"))
ITypedEventHandler<ABI::Microsoft::UI::Xaml::Documents::TextElement*, ABI::Microsoft::UI::Xaml::Input::AccessKeyInvokedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Documents::TextElement*, ABI::Microsoft::UI::Xaml::Documents::ITextElement*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::AccessKeyInvokedEventArgs*, ABI::Microsoft::UI::Xaml::Input::IAccessKeyInvokedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Xaml.Documents.TextElement, Microsoft.UI.Xaml.Input.AccessKeyInvokedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Xaml::Documents::TextElement*, ABI::Microsoft::UI::Xaml::Input::AccessKeyInvokedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

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

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum ElementSoundMode : int ElementSoundMode;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum FlowDirection : int FlowDirection;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum FocusState : int FocusState;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum FontCapitals : int FontCapitals;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum FontEastAsianLanguage : int FontEastAsianLanguage;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum FontEastAsianWidths : int FontEastAsianWidths;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum FontFraction : int FontFraction;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum FontNumeralAlignment : int FontNumeralAlignment;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum FontNumeralStyle : int FontNumeralStyle;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum FontVariants : int FontVariants;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                class FrameworkElement;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIFrameworkElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIFrameworkElement_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IFrameworkElement;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIFrameworkElement ABI::Microsoft::UI::Xaml::IFrameworkElement

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIFrameworkElement_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    typedef enum KeyTipPlacementMode : int KeyTipPlacementMode;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    typedef enum XYFocusNavigationStrategy : int XYFocusNavigationStrategy;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum LineStackingStrategy : int LineStackingStrategy;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    class Brush;
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    interface IBrush;
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush ABI::Microsoft::UI::Xaml::Media::IBrush

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    class FontFamily;
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    interface IFontFamily;
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily ABI::Microsoft::UI::Xaml::Media::IFontFamily

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    typedef enum StyleSimulations : int StyleSimulations;
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IRoutedEventHandler;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler ABI::Microsoft::UI::Xaml::IRoutedEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef enum TextAlignment : int TextAlignment;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                typedef struct Thickness Thickness;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

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
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                class XamlRoot;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IXamlRoot;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot ABI::Microsoft::UI::Xaml::IXamlRoot

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__

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
            namespace Text {
                typedef enum FontStretch : int FontStretch;
            } /* Text */
        } /* UI */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Text {
                typedef enum FontStyle : int FontStyle;
            } /* Text */
        } /* UI */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Text {
                typedef struct FontWeight FontWeight;
            } /* Text */
        } /* UI */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Text {
                typedef enum TextDecorations : unsigned int TextDecorations;
            } /* Text */
        } /* UI */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    typedef enum LogicalDirection : int LogicalDirection;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    typedef enum UnderlineStyle : int UnderlineStyle;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    class InlineCollection;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    class Span;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    class TextHighlighter;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    class TextPointer;
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Xaml.Documents.LogicalDirection
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    enum LogicalDirection : int
                    {
                        LogicalDirection_Backward = 0,
                        LogicalDirection_Forward = 1,
                    };
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Documents.UnderlineStyle
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    enum UnderlineStyle : int
                    {
                        UnderlineStyle_None = 0,
                        UnderlineStyle_Single = 1,
                    };
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Documents.TextRange
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    struct TextRange
                    {
                        INT32 StartIndex;
                        INT32 Length;
                    };
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IBlock
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Block
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IBlock[] = L"Microsoft.UI.Xaml.Documents.IBlock";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("8149d507-672f-5fd5-a10a-351389ba9659")
                    IBlock : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_TextAlignment(
                            ABI::Microsoft::UI::Xaml::TextAlignment* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TextAlignment(
                            ABI::Microsoft::UI::Xaml::TextAlignment value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_HorizontalTextAlignment(
                            ABI::Microsoft::UI::Xaml::TextAlignment* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_HorizontalTextAlignment(
                            ABI::Microsoft::UI::Xaml::TextAlignment value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LineHeight(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_LineHeight(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LineStackingStrategy(
                            ABI::Microsoft::UI::Xaml::LineStackingStrategy* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_LineStackingStrategy(
                            ABI::Microsoft::UI::Xaml::LineStackingStrategy value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Margin(
                            ABI::Microsoft::UI::Xaml::Thickness* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Margin(
                            ABI::Microsoft::UI::Xaml::Thickness value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IBlock = _uuidof(IBlock);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IBlockFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Block
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IBlockFactory[] = L"Microsoft.UI.Xaml.Documents.IBlockFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("21bd671c-33e2-56ef-be37-a128e898452c")
                    IBlockFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Documents::IBlock** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IBlockFactory = _uuidof(IBlockFactory);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IBlockStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Block
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IBlockStatics[] = L"Microsoft.UI.Xaml.Documents.IBlockStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("830feedf-9aa6-56cd-983e-055500171b45")
                    IBlockStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_TextAlignmentProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_HorizontalTextAlignmentProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LineHeightProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LineStackingStrategyProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MarginProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IBlockStatics = _uuidof(IBlockStatics);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IBold
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Bold
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IBold[] = L"Microsoft.UI.Xaml.Documents.IBold";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("241a5f5a-c164-597f-b0db-fac7431297f2")
                    IBold : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IBold = _uuidof(IBold);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IGlyphs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Glyphs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IGlyphs[] = L"Microsoft.UI.Xaml.Documents.IGlyphs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("0fbf8cfe-18e7-5e45-9fa3-d2d0927958f4")
                    IGlyphs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_UnicodeString(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_UnicodeString(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Indices(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Indices(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FontUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StyleSimulations(
                            ABI::Microsoft::UI::Xaml::Media::StyleSimulations* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_StyleSimulations(
                            ABI::Microsoft::UI::Xaml::Media::StyleSimulations value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontRenderingEmSize(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FontRenderingEmSize(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OriginX(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_OriginX(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OriginY(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_OriginY(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Fill(
                            ABI::Microsoft::UI::Xaml::Media::IBrush** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Fill(
                            ABI::Microsoft::UI::Xaml::Media::IBrush* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsColorFontEnabled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsColorFontEnabled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ColorFontPaletteIndex(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ColorFontPaletteIndex(
                            INT32 value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IGlyphs = _uuidof(IGlyphs);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IGlyphsStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Glyphs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IGlyphsStatics[] = L"Microsoft.UI.Xaml.Documents.IGlyphsStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("8d9e241a-3e0e-5100-8ede-e008034ff8ae")
                    IGlyphsStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_UnicodeStringProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IndicesProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontUriProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StyleSimulationsProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontRenderingEmSizeProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OriginXProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OriginYProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FillProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsColorFontEnabledProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ColorFontPaletteIndexProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IGlyphsStatics = _uuidof(IGlyphsStatics);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IHyperlink
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Hyperlink
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IHyperlink[] = L"Microsoft.UI.Xaml.Documents.IHyperlink";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("ac09bd16-cdfa-54c2-8d03-a474181545b1")
                    IHyperlink : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_NavigateUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_NavigateUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_UnderlineStyle(
                            ABI::Microsoft::UI::Xaml::Documents::UnderlineStyle* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_UnderlineStyle(
                            ABI::Microsoft::UI::Xaml::Documents::UnderlineStyle value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusLeft(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_XYFocusLeft(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusRight(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_XYFocusRight(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusUp(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_XYFocusUp(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusDown(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_XYFocusDown(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ElementSoundMode(
                            ABI::Microsoft::UI::Xaml::ElementSoundMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ElementSoundMode(
                            ABI::Microsoft::UI::Xaml::ElementSoundMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FocusState(
                            ABI::Microsoft::UI::Xaml::FocusState* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusUpNavigationStrategy(
                            ABI::Microsoft::UI::Xaml::Input::XYFocusNavigationStrategy* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_XYFocusUpNavigationStrategy(
                            ABI::Microsoft::UI::Xaml::Input::XYFocusNavigationStrategy value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusDownNavigationStrategy(
                            ABI::Microsoft::UI::Xaml::Input::XYFocusNavigationStrategy* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_XYFocusDownNavigationStrategy(
                            ABI::Microsoft::UI::Xaml::Input::XYFocusNavigationStrategy value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusLeftNavigationStrategy(
                            ABI::Microsoft::UI::Xaml::Input::XYFocusNavigationStrategy* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_XYFocusLeftNavigationStrategy(
                            ABI::Microsoft::UI::Xaml::Input::XYFocusNavigationStrategy value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusRightNavigationStrategy(
                            ABI::Microsoft::UI::Xaml::Input::XYFocusNavigationStrategy* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_XYFocusRightNavigationStrategy(
                            ABI::Microsoft::UI::Xaml::Input::XYFocusNavigationStrategy value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsTabStop(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsTabStop(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TabIndex(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TabIndex(
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_Click(
                            __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_Click(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_GotFocus(
                            ABI::Microsoft::UI::Xaml::IRoutedEventHandler* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_GotFocus(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_LostFocus(
                            ABI::Microsoft::UI::Xaml::IRoutedEventHandler* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_LostFocus(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Focus(
                            ABI::Microsoft::UI::Xaml::FocusState value,
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IHyperlink = _uuidof(IHyperlink);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IHyperlinkClickEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.HyperlinkClickEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IHyperlinkClickEventArgs[] = L"Microsoft.UI.Xaml.Documents.IHyperlinkClickEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("f8f89552-873d-5ef5-82bf-c79a9509b07c")
                    IHyperlinkClickEventArgs : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IHyperlinkClickEventArgs = _uuidof(IHyperlinkClickEventArgs);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IHyperlinkStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Hyperlink
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IHyperlinkStatics[] = L"Microsoft.UI.Xaml.Documents.IHyperlinkStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("e13598f4-7bc7-5ab9-885b-70f32f8c9531")
                    IHyperlinkStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_NavigateUriProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_UnderlineStyleProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusLeftProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusRightProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusUpProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusDownProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ElementSoundModeProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FocusStateProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusUpNavigationStrategyProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusDownNavigationStrategyProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusLeftNavigationStrategyProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusRightNavigationStrategyProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsTabStopProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TabIndexProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IHyperlinkStatics = _uuidof(IHyperlinkStatics);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IInline
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Inline
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IInline[] = L"Microsoft.UI.Xaml.Documents.IInline";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("813d427a-8980-5a79-a8fa-f27919cfb24f")
                    IInline : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IInline = _uuidof(IInline);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IInlineFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Inline
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IInlineFactory[] = L"Microsoft.UI.Xaml.Documents.IInlineFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("fd253a36-fa2b-5b30-89a8-9f577871ec07")
                    IInlineFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Documents::IInline** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInlineFactory = _uuidof(IInlineFactory);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IInlineUIContainer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.InlineUIContainer
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IInlineUIContainer[] = L"Microsoft.UI.Xaml.Documents.IInlineUIContainer";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("d529bef6-c05a-5bad-85e8-640127cf86f5")
                    IInlineUIContainer : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Child(
                            ABI::Microsoft::UI::Xaml::IUIElement** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Child(
                            ABI::Microsoft::UI::Xaml::IUIElement* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInlineUIContainer = _uuidof(IInlineUIContainer);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IItalic
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Italic
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IItalic[] = L"Microsoft.UI.Xaml.Documents.IItalic";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("ca3cbebd-7a8d-5d7a-8fdf-538e8a680f6c")
                    IItalic : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IItalic = _uuidof(IItalic);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ILineBreak
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.LineBreak
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ILineBreak[] = L"Microsoft.UI.Xaml.Documents.ILineBreak";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("09307599-7cc2-5f54-b106-728620c16f76")
                    ILineBreak : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ILineBreak = _uuidof(ILineBreak);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IParagraph
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Paragraph
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IParagraph[] = L"Microsoft.UI.Xaml.Documents.IParagraph";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("9ed64c77-329d-502f-a257-f58398edab51")
                    IParagraph : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Inlines(
                            __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TextIndent(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TextIndent(
                            DOUBLE value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IParagraph = _uuidof(IParagraph);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IParagraphStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Paragraph
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IParagraphStatics[] = L"Microsoft.UI.Xaml.Documents.IParagraphStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("4eb89ab1-66c8-5fc0-aa5f-48c8092ceb5f")
                    IParagraphStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_TextIndentProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IParagraphStatics = _uuidof(IParagraphStatics);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IRun
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Run
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IRun[] = L"Microsoft.UI.Xaml.Documents.IRun";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("1f905239-37cb-590b-9132-3ffb7741906e")
                    IRun : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Text(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Text(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FlowDirection(
                            ABI::Microsoft::UI::Xaml::FlowDirection* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FlowDirection(
                            ABI::Microsoft::UI::Xaml::FlowDirection value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRun = _uuidof(IRun);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IRunStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Run
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IRunStatics[] = L"Microsoft.UI.Xaml.Documents.IRunStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("051b3c5b-7600-51a5-80c5-93eb50fd684f")
                    IRunStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_FlowDirectionProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRunStatics = _uuidof(IRunStatics);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ISpan
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Span
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ISpan[] = L"Microsoft.UI.Xaml.Documents.ISpan";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("91b93d4d-4e28-57b9-bffb-3566c2a3c2a1")
                    ISpan : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Inlines(
                            __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Inlines(
                            __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ISpan = _uuidof(ISpan);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ISpanFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Span
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ISpanFactory[] = L"Microsoft.UI.Xaml.Documents.ISpanFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("a6e87c16-c175-55c8-bbd3-ce40f9d0a680")
                    ISpanFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Documents::ISpan** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ISpanFactory = _uuidof(ISpanFactory);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextElement
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextElement
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextElement[] = L"Microsoft.UI.Xaml.Documents.ITextElement";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("a122ba22-833f-5220-a47e-6cd507531abe")
                    ITextElement : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Name(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontSize(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FontSize(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontFamily(
                            ABI::Microsoft::UI::Xaml::Media::IFontFamily** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FontFamily(
                            ABI::Microsoft::UI::Xaml::Media::IFontFamily* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontWeight(
                            ABI::Windows::UI::Text::FontWeight* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FontWeight(
                            ABI::Windows::UI::Text::FontWeight value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontStyle(
                            ABI::Windows::UI::Text::FontStyle* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FontStyle(
                            ABI::Windows::UI::Text::FontStyle value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontStretch(
                            ABI::Windows::UI::Text::FontStretch* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FontStretch(
                            ABI::Windows::UI::Text::FontStretch value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CharacterSpacing(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CharacterSpacing(
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Foreground(
                            ABI::Microsoft::UI::Xaml::Media::IBrush** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Foreground(
                            ABI::Microsoft::UI::Xaml::Media::IBrush* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Language(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Language(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsTextScaleFactorEnabled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsTextScaleFactorEnabled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TextDecorations(
                            ABI::Windows::UI::Text::TextDecorations* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TextDecorations(
                            ABI::Windows::UI::Text::TextDecorations value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ContentStart(
                            ABI::Microsoft::UI::Xaml::Documents::ITextPointer** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ContentEnd(
                            ABI::Microsoft::UI::Xaml::Documents::ITextPointer** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ElementStart(
                            ABI::Microsoft::UI::Xaml::Documents::ITextPointer** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ElementEnd(
                            ABI::Microsoft::UI::Xaml::Documents::ITextPointer** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AllowFocusOnInteraction(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AllowFocusOnInteraction(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AccessKey(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AccessKey(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExitDisplayModeOnAccessKeyInvoked(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ExitDisplayModeOnAccessKeyInvoked(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsAccessKeyScope(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsAccessKeyScope(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AccessKeyScopeOwner(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AccessKeyScopeOwner(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyTipPlacementMode(
                            ABI::Microsoft::UI::Xaml::Input::KeyTipPlacementMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_KeyTipPlacementMode(
                            ABI::Microsoft::UI::Xaml::Input::KeyTipPlacementMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyTipHorizontalOffset(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_KeyTipHorizontalOffset(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyTipVerticalOffset(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_KeyTipVerticalOffset(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XamlRoot(
                            ABI::Microsoft::UI::Xaml::IXamlRoot** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_XamlRoot(
                            ABI::Microsoft::UI::Xaml::IXamlRoot* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_AccessKeyDisplayRequested(
                            __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_AccessKeyDisplayRequested(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_AccessKeyDisplayDismissed(
                            __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_AccessKeyDisplayDismissed(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_AccessKeyInvoked(
                            __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_AccessKeyInvoked(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE FindName(
                            HSTRING name,
                            IInspectable** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextElement = _uuidof(ITextElement);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextElementFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextElement
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextElementFactory[] = L"Microsoft.UI.Xaml.Documents.ITextElementFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("df51fb95-a5e6-5b16-8e88-9f7cbfa234b1")
                    ITextElementFactory : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ITextElementFactory = _uuidof(ITextElementFactory);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextElementOverrides
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextElement
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextElementOverrides[] = L"Microsoft.UI.Xaml.Documents.ITextElementOverrides";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("41b01380-e49f-5fda-8c72-acc1ac1e91df")
                    ITextElementOverrides : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE OnDisconnectVisualChildren(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextElementOverrides = _uuidof(ITextElementOverrides);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextElementStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextElement
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextElementStatics[] = L"Microsoft.UI.Xaml.Documents.ITextElementStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("c9b55919-e1fe-5acd-bac7-c9d7f413b35c")
                    ITextElementStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_FontSizeProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontFamilyProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontWeightProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontStyleProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FontStretchProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CharacterSpacingProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ForegroundProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LanguageProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsTextScaleFactorEnabledProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TextDecorationsProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AllowFocusOnInteractionProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AccessKeyProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExitDisplayModeOnAccessKeyInvokedProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsAccessKeyScopeProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AccessKeyScopeOwnerProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyTipPlacementModeProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyTipHorizontalOffsetProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyTipVerticalOffsetProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextElementStatics = _uuidof(ITextElementStatics);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextHighlighter
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextHighlighter
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextHighlighter[] = L"Microsoft.UI.Xaml.Documents.ITextHighlighter";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("b756e861-1d2b-5f6f-81fd-c51a5bc068ff")
                    ITextHighlighter : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Ranges(
                            __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Foreground(
                            ABI::Microsoft::UI::Xaml::Media::IBrush** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Foreground(
                            ABI::Microsoft::UI::Xaml::Media::IBrush* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Background(
                            ABI::Microsoft::UI::Xaml::Media::IBrush** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Background(
                            ABI::Microsoft::UI::Xaml::Media::IBrush* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextHighlighter = _uuidof(ITextHighlighter);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextHighlighterBase
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextHighlighterBase
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextHighlighterBase[] = L"Microsoft.UI.Xaml.Documents.ITextHighlighterBase";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("5c21aaf0-3a17-5468-8aac-be14db0ed8c1")
                    ITextHighlighterBase : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ITextHighlighterBase = _uuidof(ITextHighlighterBase);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextHighlighterBaseFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextHighlighterBase
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextHighlighterBaseFactory[] = L"Microsoft.UI.Xaml.Documents.ITextHighlighterBaseFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("e091e461-53ab-599e-aaea-800adc72da4f")
                    ITextHighlighterBaseFactory : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ITextHighlighterBaseFactory = _uuidof(ITextHighlighterBaseFactory);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextHighlighterFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextHighlighter
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextHighlighterFactory[] = L"Microsoft.UI.Xaml.Documents.ITextHighlighterFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("69c7311f-c019-5b93-b511-81418543bab7")
                    ITextHighlighterFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Documents::ITextHighlighter** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextHighlighterFactory = _uuidof(ITextHighlighterFactory);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextHighlighterStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextHighlighter
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextHighlighterStatics[] = L"Microsoft.UI.Xaml.Documents.ITextHighlighterStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("4975047a-87ad-51a2-977c-e771de4f4035")
                    ITextHighlighterStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ForegroundProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_BackgroundProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextHighlighterStatics = _uuidof(ITextHighlighterStatics);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextPointer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextPointer
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextPointer[] = L"Microsoft.UI.Xaml.Documents.ITextPointer";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("842eb385-ee41-5930-979b-438fa7525a51")
                    ITextPointer : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Parent(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_VisualParent(
                            ABI::Microsoft::UI::Xaml::IFrameworkElement** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LogicalDirection(
                            ABI::Microsoft::UI::Xaml::Documents::LogicalDirection* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Offset(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetCharacterRect(
                            ABI::Microsoft::UI::Xaml::Documents::LogicalDirection direction,
                            ABI::Windows::Foundation::Rect* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetPositionAtOffset(
                            INT32 offset,
                            ABI::Microsoft::UI::Xaml::Documents::LogicalDirection direction,
                            ABI::Microsoft::UI::Xaml::Documents::ITextPointer** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextPointer = _uuidof(ITextPointer);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITypography
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Typography
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITypography[] = L"Microsoft.UI.Xaml.Documents.ITypography";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("fa27e2e3-be5e-5d21-9a5e-90cf102af828")
                    ITypography : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ITypography = _uuidof(ITypography);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITypographyStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Typography
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITypographyStatics[] = L"Microsoft.UI.Xaml.Documents.ITypographyStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("55fe4535-2125-533a-ada8-27be2b9e1193")
                    ITypographyStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AnnotationAlternatesProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetAnnotationAlternates(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetAnnotationAlternates(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_EastAsianExpertFormsProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetEastAsianExpertForms(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetEastAsianExpertForms(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_EastAsianLanguageProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetEastAsianLanguage(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontEastAsianLanguage* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetEastAsianLanguage(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontEastAsianLanguage value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_EastAsianWidthsProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetEastAsianWidths(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontEastAsianWidths* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetEastAsianWidths(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontEastAsianWidths value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StandardLigaturesProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStandardLigatures(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStandardLigatures(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ContextualLigaturesProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetContextualLigatures(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetContextualLigatures(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DiscretionaryLigaturesProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetDiscretionaryLigatures(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetDiscretionaryLigatures(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_HistoricalLigaturesProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetHistoricalLigatures(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetHistoricalLigatures(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StandardSwashesProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStandardSwashes(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStandardSwashes(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ContextualSwashesProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetContextualSwashes(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetContextualSwashes(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ContextualAlternatesProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetContextualAlternates(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetContextualAlternates(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticAlternatesProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticAlternates(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticAlternates(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet1Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet1(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet1(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet2Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet2(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet2(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet3Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet3(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet3(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet4Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet4(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet4(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet5Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet5(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet5(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet6Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet6(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet6(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet7Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet7(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet7(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet8Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet8(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet8(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet9Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet9(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet9(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet10Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet10(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet10(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet11Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet11(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet11(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet12Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet12(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet12(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet13Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet13(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet13(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet14Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet14(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet14(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet15Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet15(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet15(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet16Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet16(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet16(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet17Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet17(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet17(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet18Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet18(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet18(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet19Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet19(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet19(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StylisticSet20Property(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStylisticSet20(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStylisticSet20(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CapitalsProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetCapitals(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontCapitals* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetCapitals(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontCapitals value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CapitalSpacingProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetCapitalSpacing(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetCapitalSpacing(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KerningProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetKerning(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetKerning(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CaseSensitiveFormsProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetCaseSensitiveForms(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetCaseSensitiveForms(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_HistoricalFormsProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetHistoricalForms(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetHistoricalForms(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FractionProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetFraction(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontFraction* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetFraction(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontFraction value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NumeralStyleProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetNumeralStyle(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontNumeralStyle* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetNumeralStyle(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontNumeralStyle value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NumeralAlignmentProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetNumeralAlignment(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontNumeralAlignment* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetNumeralAlignment(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontNumeralAlignment value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SlashedZeroProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetSlashedZero(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetSlashedZero(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MathematicalGreekProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetMathematicalGreek(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetMathematicalGreek(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_VariantsProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetVariants(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontVariants* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetVariants(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FontVariants value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITypographyStatics = _uuidof(ITypographyStatics);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IUnderline
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Underline
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IUnderline[] = L"Microsoft.UI.Xaml.Documents.IUnderline";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Documents {
                    MIDL_INTERFACE("68aaec6e-ea71-5ed2-b83e-91684b25efb9")
                    IUnderline : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IUnderline = _uuidof(IUnderline);
                } /* Documents */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Block
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.IBlockStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IBlock ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Block_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Block_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Block[] = L"Microsoft.UI.Xaml.Documents.Block";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.BlockCollection
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Windows.Foundation.Collections.IVector`1<Microsoft.UI.Xaml.Documents.Block> ** Default Interface **
 *    Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Xaml.Documents.Block>
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_BlockCollection_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_BlockCollection_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_BlockCollection[] = L"Microsoft.UI.Xaml.Documents.BlockCollection";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Bold
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IBold ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Bold_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Bold_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Bold[] = L"Microsoft.UI.Xaml.Documents.Bold";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Glyphs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.IGlyphsStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IGlyphs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Glyphs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Glyphs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Glyphs[] = L"Microsoft.UI.Xaml.Documents.Glyphs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Hyperlink
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.IHyperlinkStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IHyperlink ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Hyperlink_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Hyperlink_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Hyperlink[] = L"Microsoft.UI.Xaml.Documents.Hyperlink";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.HyperlinkClickEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IHyperlinkClickEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_HyperlinkClickEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_HyperlinkClickEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_HyperlinkClickEventArgs[] = L"Microsoft.UI.Xaml.Documents.HyperlinkClickEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Inline
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IInline ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Inline_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Inline_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Inline[] = L"Microsoft.UI.Xaml.Documents.Inline";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.InlineCollection
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Windows.Foundation.Collections.IVector`1<Microsoft.UI.Xaml.Documents.Inline> ** Default Interface **
 *    Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Xaml.Documents.Inline>
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_InlineCollection_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_InlineCollection_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_InlineCollection[] = L"Microsoft.UI.Xaml.Documents.InlineCollection";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.InlineUIContainer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IInlineUIContainer ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_InlineUIContainer_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_InlineUIContainer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_InlineUIContainer[] = L"Microsoft.UI.Xaml.Documents.InlineUIContainer";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Italic
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IItalic ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Italic_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Italic_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Italic[] = L"Microsoft.UI.Xaml.Documents.Italic";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.LineBreak
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ILineBreak ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_LineBreak_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_LineBreak_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_LineBreak[] = L"Microsoft.UI.Xaml.Documents.LineBreak";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Paragraph
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.IParagraphStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IParagraph ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Paragraph_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Paragraph_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Paragraph[] = L"Microsoft.UI.Xaml.Documents.Paragraph";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Run
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.IRunStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IRun ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Run_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Run_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Run[] = L"Microsoft.UI.Xaml.Documents.Run";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Span
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ISpan ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Span_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Span_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Span[] = L"Microsoft.UI.Xaml.Documents.Span";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.TextElement
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.ITextElementStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ITextElement ** Default Interface **
 *    Microsoft.UI.Xaml.Documents.ITextElementOverrides
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextElement_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextElement_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_TextElement[] = L"Microsoft.UI.Xaml.Documents.TextElement";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.TextHighlighter
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.ITextHighlighterStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ITextHighlighter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextHighlighter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextHighlighter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_TextHighlighter[] = L"Microsoft.UI.Xaml.Documents.TextHighlighter";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.TextHighlighterBase
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ITextHighlighterBase ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextHighlighterBase_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextHighlighterBase_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_TextHighlighterBase[] = L"Microsoft.UI.Xaml.Documents.TextHighlighterBase";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.TextPointer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ITextPointer ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextPointer_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextPointer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_TextPointer[] = L"Microsoft.UI.Xaml.Documents.TextPointer";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Typography
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.ITypographyStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ITypography ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Typography_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Typography_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Typography[] = L"Microsoft.UI.Xaml.Documents.Typography";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Underline
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IUnderline ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Underline_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Underline_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Underline[] = L"Microsoft.UI.Xaml.Documents.Underline";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock;

typedef struct __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl;

interface __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock;

typedef struct __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CBlock** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl;

interface __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline;

typedef struct __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl;

interface __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline;

typedef struct __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CInline** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl;

interface __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange;

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange;

typedef struct __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange* result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32 itemsLength,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange* items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl;

interface __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange;

typedef struct __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        __FIIterator_1_Microsoft__CUI__CXaml__CDocuments__CTextRange** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl;

interface __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock;

typedef struct __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl;

interface __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline;

typedef struct __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl;

interface __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange;

typedef struct __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32 index,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange* items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl;

interface __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock;

typedef struct __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CBlock** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock** items);

    END_INTERFACE
} __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl;

interface __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock
{
    CONST_VTBL struct __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlockVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline;

typedef struct __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CInline** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline** items);

    END_INTERFACE
} __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl;

interface __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline
{
    CONST_VTBL struct __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInlineVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange;

typedef struct __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32 index,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        __FIVectorView_1_Microsoft__CUI__CXaml__CDocuments__CTextRange** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32 index,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32 index,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange* items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange* This,
        UINT32 itemsLength,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange* items);

    END_INTERFACE
} __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl;

interface __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange
{
    CONST_VTBL struct __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRangeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CElementSoundMode __x_ABI_CMicrosoft_CUI_CXaml_CElementSoundMode;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CFlowDirection __x_ABI_CMicrosoft_CUI_CXaml_CFlowDirection;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CFocusState __x_ABI_CMicrosoft_CUI_CXaml_CFocusState;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CFontCapitals __x_ABI_CMicrosoft_CUI_CXaml_CFontCapitals;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CFontEastAsianLanguage __x_ABI_CMicrosoft_CUI_CXaml_CFontEastAsianLanguage;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CFontEastAsianWidths __x_ABI_CMicrosoft_CUI_CXaml_CFontEastAsianWidths;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CFontFraction __x_ABI_CMicrosoft_CUI_CXaml_CFontFraction;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CFontNumeralAlignment __x_ABI_CMicrosoft_CUI_CXaml_CFontNumeralAlignment;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CFontNumeralStyle __x_ABI_CMicrosoft_CUI_CXaml_CFontNumeralStyle;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CFontVariants __x_ABI_CMicrosoft_CUI_CXaml_CFontVariants;

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIFrameworkElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIFrameworkElement_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIFrameworkElement __x_ABI_CMicrosoft_CUI_CXaml_CIFrameworkElement;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIFrameworkElement_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CKeyTipPlacementMode __x_ABI_CMicrosoft_CUI_CXaml_CInput_CKeyTipPlacementMode;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CLineStackingStrategy __x_ABI_CMicrosoft_CUI_CXaml_CLineStackingStrategy;

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CStyleSimulations __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CStyleSimulations;

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CTextAlignment __x_ABI_CMicrosoft_CUI_CXaml_CTextAlignment;

typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CThickness __x_ABI_CMicrosoft_CUI_CXaml_CThickness;

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot __x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CRect __x_ABI_CWindows_CFoundation_CRect;

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIUriRuntimeClass __x_ABI_CWindows_CFoundation_CIUriRuntimeClass;

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

typedef enum __x_ABI_CWindows_CUI_CText_CFontStretch __x_ABI_CWindows_CUI_CText_CFontStretch;

typedef enum __x_ABI_CWindows_CUI_CText_CFontStyle __x_ABI_CWindows_CUI_CText_CFontStyle;

typedef struct __x_ABI_CWindows_CUI_CText_CFontWeight __x_ABI_CWindows_CUI_CText_CFontWeight;

typedef enum __x_ABI_CWindows_CUI_CText_CTextDecorations __x_ABI_CWindows_CUI_CText_CTextDecorations;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CLogicalDirection __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CLogicalDirection;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CUnderlineStyle __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CUnderlineStyle;

/*
 *
 * Struct Microsoft.UI.Xaml.Documents.LogicalDirection
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CLogicalDirection
{
    LogicalDirection_Backward = 0,
    LogicalDirection_Forward = 1,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Documents.UnderlineStyle
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CUnderlineStyle
{
    UnderlineStyle_None = 0,
    UnderlineStyle_Single = 1,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Documents.TextRange
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CTextRange
{
    INT32 StartIndex;
    INT32 Length;
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IBlock
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Block
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IBlock[] = L"Microsoft.UI.Xaml.Documents.IBlock";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_TextAlignment)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CTextAlignment* value);
    HRESULT (STDMETHODCALLTYPE* put_TextAlignment)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CTextAlignment value);
    HRESULT (STDMETHODCALLTYPE* get_HorizontalTextAlignment)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CTextAlignment* value);
    HRESULT (STDMETHODCALLTYPE* put_HorizontalTextAlignment)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CTextAlignment value);
    HRESULT (STDMETHODCALLTYPE* get_LineHeight)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_LineHeight)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_LineStackingStrategy)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CLineStackingStrategy* value);
    HRESULT (STDMETHODCALLTYPE* put_LineStackingStrategy)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CLineStackingStrategy value);
    HRESULT (STDMETHODCALLTYPE* get_Margin)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CThickness* value);
    HRESULT (STDMETHODCALLTYPE* put_Margin)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CThickness value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_get_TextAlignment(This, value) \
    ((This)->lpVtbl->get_TextAlignment(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_put_TextAlignment(This, value) \
    ((This)->lpVtbl->put_TextAlignment(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_get_HorizontalTextAlignment(This, value) \
    ((This)->lpVtbl->get_HorizontalTextAlignment(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_put_HorizontalTextAlignment(This, value) \
    ((This)->lpVtbl->put_HorizontalTextAlignment(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_get_LineHeight(This, value) \
    ((This)->lpVtbl->get_LineHeight(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_put_LineHeight(This, value) \
    ((This)->lpVtbl->put_LineHeight(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_get_LineStackingStrategy(This, value) \
    ((This)->lpVtbl->get_LineStackingStrategy(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_put_LineStackingStrategy(This, value) \
    ((This)->lpVtbl->put_LineStackingStrategy(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_get_Margin(This, value) \
    ((This)->lpVtbl->get_Margin(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_put_Margin(This, value) \
    ((This)->lpVtbl->put_Margin(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IBlockFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Block
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IBlockFactory[] = L"Microsoft.UI.Xaml.Documents.IBlockFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlock** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IBlockStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Block
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IBlockStatics[] = L"Microsoft.UI.Xaml.Documents.IBlockStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_TextAlignmentProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_HorizontalTextAlignmentProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_LineHeightProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_LineStackingStrategyProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_MarginProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_get_TextAlignmentProperty(This, value) \
    ((This)->lpVtbl->get_TextAlignmentProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_get_HorizontalTextAlignmentProperty(This, value) \
    ((This)->lpVtbl->get_HorizontalTextAlignmentProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_get_LineHeightProperty(This, value) \
    ((This)->lpVtbl->get_LineHeightProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_get_LineStackingStrategyProperty(This, value) \
    ((This)->lpVtbl->get_LineStackingStrategyProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_get_MarginProperty(This, value) \
    ((This)->lpVtbl->get_MarginProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBlockStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IBold
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Bold
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IBold[] = L"Microsoft.UI.Xaml.Documents.IBold";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBoldVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBoldVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBoldVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIBold_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IGlyphs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Glyphs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IGlyphs[] = L"Microsoft.UI.Xaml.Documents.IGlyphs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_UnicodeString)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_UnicodeString)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Indices)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Indices)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_FontUri)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_FontUri)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_StyleSimulations)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CStyleSimulations* value);
    HRESULT (STDMETHODCALLTYPE* put_StyleSimulations)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CStyleSimulations value);
    HRESULT (STDMETHODCALLTYPE* get_FontRenderingEmSize)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_FontRenderingEmSize)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_OriginX)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_OriginX)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_OriginY)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_OriginY)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_Fill)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush** value);
    HRESULT (STDMETHODCALLTYPE* put_Fill)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush* value);
    HRESULT (STDMETHODCALLTYPE* get_IsColorFontEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsColorFontEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ColorFontPaletteIndex)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_ColorFontPaletteIndex)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs* This,
        INT32 value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_get_UnicodeString(This, value) \
    ((This)->lpVtbl->get_UnicodeString(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_put_UnicodeString(This, value) \
    ((This)->lpVtbl->put_UnicodeString(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_get_Indices(This, value) \
    ((This)->lpVtbl->get_Indices(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_put_Indices(This, value) \
    ((This)->lpVtbl->put_Indices(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_get_FontUri(This, value) \
    ((This)->lpVtbl->get_FontUri(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_put_FontUri(This, value) \
    ((This)->lpVtbl->put_FontUri(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_get_StyleSimulations(This, value) \
    ((This)->lpVtbl->get_StyleSimulations(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_put_StyleSimulations(This, value) \
    ((This)->lpVtbl->put_StyleSimulations(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_get_FontRenderingEmSize(This, value) \
    ((This)->lpVtbl->get_FontRenderingEmSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_put_FontRenderingEmSize(This, value) \
    ((This)->lpVtbl->put_FontRenderingEmSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_get_OriginX(This, value) \
    ((This)->lpVtbl->get_OriginX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_put_OriginX(This, value) \
    ((This)->lpVtbl->put_OriginX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_get_OriginY(This, value) \
    ((This)->lpVtbl->get_OriginY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_put_OriginY(This, value) \
    ((This)->lpVtbl->put_OriginY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_get_Fill(This, value) \
    ((This)->lpVtbl->get_Fill(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_put_Fill(This, value) \
    ((This)->lpVtbl->put_Fill(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_get_IsColorFontEnabled(This, value) \
    ((This)->lpVtbl->get_IsColorFontEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_put_IsColorFontEnabled(This, value) \
    ((This)->lpVtbl->put_IsColorFontEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_get_ColorFontPaletteIndex(This, value) \
    ((This)->lpVtbl->get_ColorFontPaletteIndex(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_put_ColorFontPaletteIndex(This, value) \
    ((This)->lpVtbl->put_ColorFontPaletteIndex(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IGlyphsStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Glyphs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IGlyphsStatics[] = L"Microsoft.UI.Xaml.Documents.IGlyphsStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_UnicodeStringProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_IndicesProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_FontUriProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_StyleSimulationsProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_FontRenderingEmSizeProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_OriginXProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_OriginYProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_FillProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_IsColorFontEnabledProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_ColorFontPaletteIndexProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_get_UnicodeStringProperty(This, value) \
    ((This)->lpVtbl->get_UnicodeStringProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_get_IndicesProperty(This, value) \
    ((This)->lpVtbl->get_IndicesProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_get_FontUriProperty(This, value) \
    ((This)->lpVtbl->get_FontUriProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_get_StyleSimulationsProperty(This, value) \
    ((This)->lpVtbl->get_StyleSimulationsProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_get_FontRenderingEmSizeProperty(This, value) \
    ((This)->lpVtbl->get_FontRenderingEmSizeProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_get_OriginXProperty(This, value) \
    ((This)->lpVtbl->get_OriginXProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_get_OriginYProperty(This, value) \
    ((This)->lpVtbl->get_OriginYProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_get_FillProperty(This, value) \
    ((This)->lpVtbl->get_FillProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_get_IsColorFontEnabledProperty(This, value) \
    ((This)->lpVtbl->get_IsColorFontEnabledProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_get_ColorFontPaletteIndexProperty(This, value) \
    ((This)->lpVtbl->get_ColorFontPaletteIndexProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIGlyphsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IHyperlink
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Hyperlink
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IHyperlink[] = L"Microsoft.UI.Xaml.Documents.IHyperlink";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_NavigateUri)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_NavigateUri)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_UnderlineStyle)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CUnderlineStyle* value);
    HRESULT (STDMETHODCALLTYPE* put_UnderlineStyle)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CUnderlineStyle value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusLeft)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* put_XYFocusLeft)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusRight)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* put_XYFocusRight)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusUp)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* put_XYFocusUp)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusDown)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* put_XYFocusDown)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* value);
    HRESULT (STDMETHODCALLTYPE* get_ElementSoundMode)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CElementSoundMode* value);
    HRESULT (STDMETHODCALLTYPE* put_ElementSoundMode)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CElementSoundMode value);
    HRESULT (STDMETHODCALLTYPE* get_FocusState)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFocusState* value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusUpNavigationStrategy)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy* value);
    HRESULT (STDMETHODCALLTYPE* put_XYFocusUpNavigationStrategy)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusDownNavigationStrategy)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy* value);
    HRESULT (STDMETHODCALLTYPE* put_XYFocusDownNavigationStrategy)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusLeftNavigationStrategy)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy* value);
    HRESULT (STDMETHODCALLTYPE* put_XYFocusLeftNavigationStrategy)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusRightNavigationStrategy)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy* value);
    HRESULT (STDMETHODCALLTYPE* put_XYFocusRightNavigationStrategy)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy value);
    HRESULT (STDMETHODCALLTYPE* get_IsTabStop)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsTabStop)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_TabIndex)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_TabIndex)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* add_Click)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CHyperlink_Microsoft__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Click)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_GotFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_GotFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_LostFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIRoutedEventHandler* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_LostFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* Focus)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFocusState value,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_NavigateUri(This, value) \
    ((This)->lpVtbl->get_NavigateUri(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_NavigateUri(This, value) \
    ((This)->lpVtbl->put_NavigateUri(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_UnderlineStyle(This, value) \
    ((This)->lpVtbl->get_UnderlineStyle(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_UnderlineStyle(This, value) \
    ((This)->lpVtbl->put_UnderlineStyle(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_XYFocusLeft(This, value) \
    ((This)->lpVtbl->get_XYFocusLeft(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_XYFocusLeft(This, value) \
    ((This)->lpVtbl->put_XYFocusLeft(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_XYFocusRight(This, value) \
    ((This)->lpVtbl->get_XYFocusRight(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_XYFocusRight(This, value) \
    ((This)->lpVtbl->put_XYFocusRight(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_XYFocusUp(This, value) \
    ((This)->lpVtbl->get_XYFocusUp(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_XYFocusUp(This, value) \
    ((This)->lpVtbl->put_XYFocusUp(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_XYFocusDown(This, value) \
    ((This)->lpVtbl->get_XYFocusDown(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_XYFocusDown(This, value) \
    ((This)->lpVtbl->put_XYFocusDown(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_ElementSoundMode(This, value) \
    ((This)->lpVtbl->get_ElementSoundMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_ElementSoundMode(This, value) \
    ((This)->lpVtbl->put_ElementSoundMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_FocusState(This, value) \
    ((This)->lpVtbl->get_FocusState(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_XYFocusUpNavigationStrategy(This, value) \
    ((This)->lpVtbl->get_XYFocusUpNavigationStrategy(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_XYFocusUpNavigationStrategy(This, value) \
    ((This)->lpVtbl->put_XYFocusUpNavigationStrategy(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_XYFocusDownNavigationStrategy(This, value) \
    ((This)->lpVtbl->get_XYFocusDownNavigationStrategy(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_XYFocusDownNavigationStrategy(This, value) \
    ((This)->lpVtbl->put_XYFocusDownNavigationStrategy(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_XYFocusLeftNavigationStrategy(This, value) \
    ((This)->lpVtbl->get_XYFocusLeftNavigationStrategy(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_XYFocusLeftNavigationStrategy(This, value) \
    ((This)->lpVtbl->put_XYFocusLeftNavigationStrategy(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_XYFocusRightNavigationStrategy(This, value) \
    ((This)->lpVtbl->get_XYFocusRightNavigationStrategy(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_XYFocusRightNavigationStrategy(This, value) \
    ((This)->lpVtbl->put_XYFocusRightNavigationStrategy(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_IsTabStop(This, value) \
    ((This)->lpVtbl->get_IsTabStop(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_IsTabStop(This, value) \
    ((This)->lpVtbl->put_IsTabStop(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_get_TabIndex(This, value) \
    ((This)->lpVtbl->get_TabIndex(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_put_TabIndex(This, value) \
    ((This)->lpVtbl->put_TabIndex(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_add_Click(This, handler, token) \
    ((This)->lpVtbl->add_Click(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_remove_Click(This, token) \
    ((This)->lpVtbl->remove_Click(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_add_GotFocus(This, handler, token) \
    ((This)->lpVtbl->add_GotFocus(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_remove_GotFocus(This, token) \
    ((This)->lpVtbl->remove_GotFocus(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_add_LostFocus(This, handler, token) \
    ((This)->lpVtbl->add_LostFocus(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_remove_LostFocus(This, token) \
    ((This)->lpVtbl->remove_LostFocus(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_Focus(This, value, result) \
    ((This)->lpVtbl->Focus(This, value, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlink_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IHyperlinkClickEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.HyperlinkClickEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IHyperlinkClickEventArgs[] = L"Microsoft.UI.Xaml.Documents.IHyperlinkClickEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IHyperlinkStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Hyperlink
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IHyperlinkStatics[] = L"Microsoft.UI.Xaml.Documents.IHyperlinkStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_NavigateUriProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_UnderlineStyleProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusLeftProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusRightProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusUpProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusDownProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_ElementSoundModeProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_FocusStateProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusUpNavigationStrategyProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusDownNavigationStrategyProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusLeftNavigationStrategyProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusRightNavigationStrategyProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_IsTabStopProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_TabIndexProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_NavigateUriProperty(This, value) \
    ((This)->lpVtbl->get_NavigateUriProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_UnderlineStyleProperty(This, value) \
    ((This)->lpVtbl->get_UnderlineStyleProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_XYFocusLeftProperty(This, value) \
    ((This)->lpVtbl->get_XYFocusLeftProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_XYFocusRightProperty(This, value) \
    ((This)->lpVtbl->get_XYFocusRightProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_XYFocusUpProperty(This, value) \
    ((This)->lpVtbl->get_XYFocusUpProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_XYFocusDownProperty(This, value) \
    ((This)->lpVtbl->get_XYFocusDownProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_ElementSoundModeProperty(This, value) \
    ((This)->lpVtbl->get_ElementSoundModeProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_FocusStateProperty(This, value) \
    ((This)->lpVtbl->get_FocusStateProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_XYFocusUpNavigationStrategyProperty(This, value) \
    ((This)->lpVtbl->get_XYFocusUpNavigationStrategyProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_XYFocusDownNavigationStrategyProperty(This, value) \
    ((This)->lpVtbl->get_XYFocusDownNavigationStrategyProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_XYFocusLeftNavigationStrategyProperty(This, value) \
    ((This)->lpVtbl->get_XYFocusLeftNavigationStrategyProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_XYFocusRightNavigationStrategyProperty(This, value) \
    ((This)->lpVtbl->get_XYFocusRightNavigationStrategyProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_IsTabStopProperty(This, value) \
    ((This)->lpVtbl->get_IsTabStopProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_get_TabIndexProperty(This, value) \
    ((This)->lpVtbl->get_TabIndexProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIHyperlinkStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IInline
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Inline
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IInline[] = L"Microsoft.UI.Xaml.Documents.IInline";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IInlineFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Inline
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IInlineFactory[] = L"Microsoft.UI.Xaml.Documents.IInlineFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInline** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IInlineUIContainer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.InlineUIContainer
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IInlineUIContainer[] = L"Microsoft.UI.Xaml.Documents.IInlineUIContainer";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Child)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement** value);
    HRESULT (STDMETHODCALLTYPE* put_Child)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_get_Child(This, value) \
    ((This)->lpVtbl->get_Child(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_put_Child(This, value) \
    ((This)->lpVtbl->put_Child(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIInlineUIContainer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IItalic
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Italic
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IItalic[] = L"Microsoft.UI.Xaml.Documents.IItalic";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalicVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalicVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalicVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIItalic_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ILineBreak
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.LineBreak
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ILineBreak[] = L"Microsoft.UI.Xaml.Documents.ILineBreak";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreakVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreakVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreakVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CILineBreak_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IParagraph
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Paragraph
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IParagraph[] = L"Microsoft.UI.Xaml.Documents.IParagraph";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Inlines)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph* This,
        __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline** value);
    HRESULT (STDMETHODCALLTYPE* get_TextIndent)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_TextIndent)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph* This,
        DOUBLE value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_get_Inlines(This, value) \
    ((This)->lpVtbl->get_Inlines(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_get_TextIndent(This, value) \
    ((This)->lpVtbl->get_TextIndent(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_put_TextIndent(This, value) \
    ((This)->lpVtbl->put_TextIndent(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraph_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IParagraphStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Paragraph
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IParagraphStatics[] = L"Microsoft.UI.Xaml.Documents.IParagraphStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_TextIndentProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_get_TextIndentProperty(This, value) \
    ((This)->lpVtbl->get_TextIndentProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIParagraphStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IRun
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Run
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IRun[] = L"Microsoft.UI.Xaml.Documents.IRun";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Text)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Text)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_FlowDirection)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFlowDirection* value);
    HRESULT (STDMETHODCALLTYPE* put_FlowDirection)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFlowDirection value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_get_Text(This, value) \
    ((This)->lpVtbl->get_Text(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_put_Text(This, value) \
    ((This)->lpVtbl->put_Text(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_get_FlowDirection(This, value) \
    ((This)->lpVtbl->get_FlowDirection(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_put_FlowDirection(This, value) \
    ((This)->lpVtbl->put_FlowDirection(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRun_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IRunStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Run
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IRunStatics[] = L"Microsoft.UI.Xaml.Documents.IRunStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FlowDirectionProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_get_FlowDirectionProperty(This, value) \
    ((This)->lpVtbl->get_FlowDirectionProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIRunStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ISpan
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Span
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ISpan[] = L"Microsoft.UI.Xaml.Documents.ISpan";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Inlines)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan* This,
        __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline** value);
    HRESULT (STDMETHODCALLTYPE* put_Inlines)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan* This,
        __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CInline* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_get_Inlines(This, value) \
    ((This)->lpVtbl->get_Inlines(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_put_Inlines(This, value) \
    ((This)->lpVtbl->put_Inlines(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ISpanFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Span
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ISpanFactory[] = L"Microsoft.UI.Xaml.Documents.ISpanFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpan** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CISpanFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextElement
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextElement
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextElement[] = L"Microsoft.UI.Xaml.Documents.ITextElement";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Name)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_FontSize)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_FontSize)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_FontFamily)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily** value);
    HRESULT (STDMETHODCALLTYPE* put_FontFamily)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIFontFamily* value);
    HRESULT (STDMETHODCALLTYPE* get_FontWeight)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* put_FontWeight)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight value);
    HRESULT (STDMETHODCALLTYPE* get_FontStyle)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        enum __x_ABI_CWindows_CUI_CText_CFontStyle* value);
    HRESULT (STDMETHODCALLTYPE* put_FontStyle)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        enum __x_ABI_CWindows_CUI_CText_CFontStyle value);
    HRESULT (STDMETHODCALLTYPE* get_FontStretch)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        enum __x_ABI_CWindows_CUI_CText_CFontStretch* value);
    HRESULT (STDMETHODCALLTYPE* put_FontStretch)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        enum __x_ABI_CWindows_CUI_CText_CFontStretch value);
    HRESULT (STDMETHODCALLTYPE* get_CharacterSpacing)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_CharacterSpacing)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* get_Foreground)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush** value);
    HRESULT (STDMETHODCALLTYPE* put_Foreground)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush* value);
    HRESULT (STDMETHODCALLTYPE* get_Language)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Language)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_IsTextScaleFactorEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsTextScaleFactorEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_TextDecorations)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        enum __x_ABI_CWindows_CUI_CText_CTextDecorations* value);
    HRESULT (STDMETHODCALLTYPE* put_TextDecorations)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        enum __x_ABI_CWindows_CUI_CText_CTextDecorations value);
    HRESULT (STDMETHODCALLTYPE* get_ContentStart)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer** value);
    HRESULT (STDMETHODCALLTYPE* get_ContentEnd)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer** value);
    HRESULT (STDMETHODCALLTYPE* get_ElementStart)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer** value);
    HRESULT (STDMETHODCALLTYPE* get_ElementEnd)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer** value);
    HRESULT (STDMETHODCALLTYPE* get_AllowFocusOnInteraction)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_AllowFocusOnInteraction)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_AccessKey)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_AccessKey)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_ExitDisplayModeOnAccessKeyInvoked)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ExitDisplayModeOnAccessKeyInvoked)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsAccessKeyScope)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsAccessKeyScope)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_AccessKeyScopeOwner)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* put_AccessKeyScopeOwner)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* value);
    HRESULT (STDMETHODCALLTYPE* get_KeyTipPlacementMode)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CKeyTipPlacementMode* value);
    HRESULT (STDMETHODCALLTYPE* put_KeyTipPlacementMode)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CKeyTipPlacementMode value);
    HRESULT (STDMETHODCALLTYPE* get_KeyTipHorizontalOffset)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_KeyTipHorizontalOffset)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_KeyTipVerticalOffset)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_KeyTipVerticalOffset)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_XamlRoot)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot** value);
    HRESULT (STDMETHODCALLTYPE* put_XamlRoot)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot* value);
    HRESULT (STDMETHODCALLTYPE* add_AccessKeyDisplayRequested)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayRequestedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_AccessKeyDisplayRequested)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_AccessKeyDisplayDismissed)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyDisplayDismissedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_AccessKeyDisplayDismissed)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_AccessKeyInvoked)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        __FITypedEventHandler_2_Microsoft__CUI__CXaml__CDocuments__CTextElement_Microsoft__CUI__CXaml__CInput__CAccessKeyInvokedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_AccessKeyInvoked)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* FindName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement* This,
        HSTRING name,
        IInspectable** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_Name(This, value) \
    ((This)->lpVtbl->get_Name(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_FontSize(This, value) \
    ((This)->lpVtbl->get_FontSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_FontSize(This, value) \
    ((This)->lpVtbl->put_FontSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_FontFamily(This, value) \
    ((This)->lpVtbl->get_FontFamily(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_FontFamily(This, value) \
    ((This)->lpVtbl->put_FontFamily(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_FontWeight(This, value) \
    ((This)->lpVtbl->get_FontWeight(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_FontWeight(This, value) \
    ((This)->lpVtbl->put_FontWeight(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_FontStyle(This, value) \
    ((This)->lpVtbl->get_FontStyle(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_FontStyle(This, value) \
    ((This)->lpVtbl->put_FontStyle(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_FontStretch(This, value) \
    ((This)->lpVtbl->get_FontStretch(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_FontStretch(This, value) \
    ((This)->lpVtbl->put_FontStretch(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_CharacterSpacing(This, value) \
    ((This)->lpVtbl->get_CharacterSpacing(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_CharacterSpacing(This, value) \
    ((This)->lpVtbl->put_CharacterSpacing(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_Foreground(This, value) \
    ((This)->lpVtbl->get_Foreground(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_Foreground(This, value) \
    ((This)->lpVtbl->put_Foreground(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_Language(This, value) \
    ((This)->lpVtbl->get_Language(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_Language(This, value) \
    ((This)->lpVtbl->put_Language(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_IsTextScaleFactorEnabled(This, value) \
    ((This)->lpVtbl->get_IsTextScaleFactorEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_IsTextScaleFactorEnabled(This, value) \
    ((This)->lpVtbl->put_IsTextScaleFactorEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_TextDecorations(This, value) \
    ((This)->lpVtbl->get_TextDecorations(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_TextDecorations(This, value) \
    ((This)->lpVtbl->put_TextDecorations(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_ContentStart(This, value) \
    ((This)->lpVtbl->get_ContentStart(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_ContentEnd(This, value) \
    ((This)->lpVtbl->get_ContentEnd(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_ElementStart(This, value) \
    ((This)->lpVtbl->get_ElementStart(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_ElementEnd(This, value) \
    ((This)->lpVtbl->get_ElementEnd(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_AllowFocusOnInteraction(This, value) \
    ((This)->lpVtbl->get_AllowFocusOnInteraction(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_AllowFocusOnInteraction(This, value) \
    ((This)->lpVtbl->put_AllowFocusOnInteraction(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_AccessKey(This, value) \
    ((This)->lpVtbl->get_AccessKey(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_AccessKey(This, value) \
    ((This)->lpVtbl->put_AccessKey(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_ExitDisplayModeOnAccessKeyInvoked(This, value) \
    ((This)->lpVtbl->get_ExitDisplayModeOnAccessKeyInvoked(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_ExitDisplayModeOnAccessKeyInvoked(This, value) \
    ((This)->lpVtbl->put_ExitDisplayModeOnAccessKeyInvoked(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_IsAccessKeyScope(This, value) \
    ((This)->lpVtbl->get_IsAccessKeyScope(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_IsAccessKeyScope(This, value) \
    ((This)->lpVtbl->put_IsAccessKeyScope(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_AccessKeyScopeOwner(This, value) \
    ((This)->lpVtbl->get_AccessKeyScopeOwner(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_AccessKeyScopeOwner(This, value) \
    ((This)->lpVtbl->put_AccessKeyScopeOwner(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_KeyTipPlacementMode(This, value) \
    ((This)->lpVtbl->get_KeyTipPlacementMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_KeyTipPlacementMode(This, value) \
    ((This)->lpVtbl->put_KeyTipPlacementMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_KeyTipHorizontalOffset(This, value) \
    ((This)->lpVtbl->get_KeyTipHorizontalOffset(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_KeyTipHorizontalOffset(This, value) \
    ((This)->lpVtbl->put_KeyTipHorizontalOffset(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_KeyTipVerticalOffset(This, value) \
    ((This)->lpVtbl->get_KeyTipVerticalOffset(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_KeyTipVerticalOffset(This, value) \
    ((This)->lpVtbl->put_KeyTipVerticalOffset(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_get_XamlRoot(This, value) \
    ((This)->lpVtbl->get_XamlRoot(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_put_XamlRoot(This, value) \
    ((This)->lpVtbl->put_XamlRoot(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_add_AccessKeyDisplayRequested(This, handler, token) \
    ((This)->lpVtbl->add_AccessKeyDisplayRequested(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_remove_AccessKeyDisplayRequested(This, token) \
    ((This)->lpVtbl->remove_AccessKeyDisplayRequested(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_add_AccessKeyDisplayDismissed(This, handler, token) \
    ((This)->lpVtbl->add_AccessKeyDisplayDismissed(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_remove_AccessKeyDisplayDismissed(This, token) \
    ((This)->lpVtbl->remove_AccessKeyDisplayDismissed(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_add_AccessKeyInvoked(This, handler, token) \
    ((This)->lpVtbl->add_AccessKeyInvoked(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_remove_AccessKeyInvoked(This, token) \
    ((This)->lpVtbl->remove_AccessKeyInvoked(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_FindName(This, name, result) \
    ((This)->lpVtbl->FindName(This, name, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElement_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextElementFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextElement
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextElementFactory[] = L"Microsoft.UI.Xaml.Documents.ITextElementFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextElementOverrides
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextElement
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextElementOverrides[] = L"Microsoft.UI.Xaml.Documents.ITextElementOverrides";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverridesVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnDisconnectVisualChildren)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverridesVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverridesVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_OnDisconnectVisualChildren(This) \
    ((This)->lpVtbl->OnDisconnectVisualChildren(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementOverrides_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextElementStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextElement
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextElementStatics[] = L"Microsoft.UI.Xaml.Documents.ITextElementStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FontSizeProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_FontFamilyProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_FontWeightProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_FontStyleProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_FontStretchProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_CharacterSpacingProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_ForegroundProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_LanguageProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_IsTextScaleFactorEnabledProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_TextDecorationsProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_AllowFocusOnInteractionProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_AccessKeyProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_ExitDisplayModeOnAccessKeyInvokedProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_IsAccessKeyScopeProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_AccessKeyScopeOwnerProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_KeyTipPlacementModeProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_KeyTipHorizontalOffsetProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_KeyTipVerticalOffsetProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_FontSizeProperty(This, value) \
    ((This)->lpVtbl->get_FontSizeProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_FontFamilyProperty(This, value) \
    ((This)->lpVtbl->get_FontFamilyProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_FontWeightProperty(This, value) \
    ((This)->lpVtbl->get_FontWeightProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_FontStyleProperty(This, value) \
    ((This)->lpVtbl->get_FontStyleProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_FontStretchProperty(This, value) \
    ((This)->lpVtbl->get_FontStretchProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_CharacterSpacingProperty(This, value) \
    ((This)->lpVtbl->get_CharacterSpacingProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_ForegroundProperty(This, value) \
    ((This)->lpVtbl->get_ForegroundProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_LanguageProperty(This, value) \
    ((This)->lpVtbl->get_LanguageProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_IsTextScaleFactorEnabledProperty(This, value) \
    ((This)->lpVtbl->get_IsTextScaleFactorEnabledProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_TextDecorationsProperty(This, value) \
    ((This)->lpVtbl->get_TextDecorationsProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_AllowFocusOnInteractionProperty(This, value) \
    ((This)->lpVtbl->get_AllowFocusOnInteractionProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_AccessKeyProperty(This, value) \
    ((This)->lpVtbl->get_AccessKeyProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_ExitDisplayModeOnAccessKeyInvokedProperty(This, value) \
    ((This)->lpVtbl->get_ExitDisplayModeOnAccessKeyInvokedProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_IsAccessKeyScopeProperty(This, value) \
    ((This)->lpVtbl->get_IsAccessKeyScopeProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_AccessKeyScopeOwnerProperty(This, value) \
    ((This)->lpVtbl->get_AccessKeyScopeOwnerProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_KeyTipPlacementModeProperty(This, value) \
    ((This)->lpVtbl->get_KeyTipPlacementModeProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_KeyTipHorizontalOffsetProperty(This, value) \
    ((This)->lpVtbl->get_KeyTipHorizontalOffsetProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_get_KeyTipVerticalOffsetProperty(This, value) \
    ((This)->lpVtbl->get_KeyTipVerticalOffsetProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextElementStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextHighlighter
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextHighlighter
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextHighlighter[] = L"Microsoft.UI.Xaml.Documents.ITextHighlighter";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Ranges)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This,
        __FIVector_1_Microsoft__CUI__CXaml__CDocuments__CTextRange** value);
    HRESULT (STDMETHODCALLTYPE* get_Foreground)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush** value);
    HRESULT (STDMETHODCALLTYPE* put_Foreground)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush* value);
    HRESULT (STDMETHODCALLTYPE* get_Background)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush** value);
    HRESULT (STDMETHODCALLTYPE* put_Background)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CIBrush* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_get_Ranges(This, value) \
    ((This)->lpVtbl->get_Ranges(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_get_Foreground(This, value) \
    ((This)->lpVtbl->get_Foreground(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_put_Foreground(This, value) \
    ((This)->lpVtbl->put_Foreground(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_get_Background(This, value) \
    ((This)->lpVtbl->get_Background(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_put_Background(This, value) \
    ((This)->lpVtbl->put_Background(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextHighlighterBase
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextHighlighterBase
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextHighlighterBase[] = L"Microsoft.UI.Xaml.Documents.ITextHighlighterBase";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBase_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextHighlighterBaseFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextHighlighterBase
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextHighlighterBaseFactory[] = L"Microsoft.UI.Xaml.Documents.ITextHighlighterBaseFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterBaseFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextHighlighterFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextHighlighter
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextHighlighterFactory[] = L"Microsoft.UI.Xaml.Documents.ITextHighlighterFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighter** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextHighlighterStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextHighlighter
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextHighlighterStatics[] = L"Microsoft.UI.Xaml.Documents.ITextHighlighterStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ForegroundProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_BackgroundProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_get_ForegroundProperty(This, value) \
    ((This)->lpVtbl->get_ForegroundProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_get_BackgroundProperty(This, value) \
    ((This)->lpVtbl->get_BackgroundProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextHighlighterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITextPointer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.TextPointer
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITextPointer[] = L"Microsoft.UI.Xaml.Documents.ITextPointer";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Parent)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* get_VisualParent)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIFrameworkElement** value);
    HRESULT (STDMETHODCALLTYPE* get_LogicalDirection)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CLogicalDirection* value);
    HRESULT (STDMETHODCALLTYPE* get_Offset)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* GetCharacterRect)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CLogicalDirection direction,
        struct __x_ABI_CWindows_CFoundation_CRect* result);
    HRESULT (STDMETHODCALLTYPE* GetPositionAtOffset)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer* This,
        INT32 offset,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CLogicalDirection direction,
        __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_get_Parent(This, value) \
    ((This)->lpVtbl->get_Parent(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_get_VisualParent(This, value) \
    ((This)->lpVtbl->get_VisualParent(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_get_LogicalDirection(This, value) \
    ((This)->lpVtbl->get_LogicalDirection(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_get_Offset(This, value) \
    ((This)->lpVtbl->get_Offset(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_GetCharacterRect(This, direction, result) \
    ((This)->lpVtbl->GetCharacterRect(This, direction, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_GetPositionAtOffset(This, offset, direction, result) \
    ((This)->lpVtbl->GetPositionAtOffset(This, offset, direction, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITextPointer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITypography
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Typography
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITypography[] = L"Microsoft.UI.Xaml.Documents.ITypography";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypography_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.ITypographyStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Typography
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_ITypographyStatics[] = L"Microsoft.UI.Xaml.Documents.ITypographyStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AnnotationAlternatesProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetAnnotationAlternates)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* SetAnnotationAlternates)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* get_EastAsianExpertFormsProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetEastAsianExpertForms)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetEastAsianExpertForms)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_EastAsianLanguageProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetEastAsianLanguage)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontEastAsianLanguage* result);
    HRESULT (STDMETHODCALLTYPE* SetEastAsianLanguage)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontEastAsianLanguage value);
    HRESULT (STDMETHODCALLTYPE* get_EastAsianWidthsProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetEastAsianWidths)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontEastAsianWidths* result);
    HRESULT (STDMETHODCALLTYPE* SetEastAsianWidths)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontEastAsianWidths value);
    HRESULT (STDMETHODCALLTYPE* get_StandardLigaturesProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStandardLigatures)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStandardLigatures)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ContextualLigaturesProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetContextualLigatures)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetContextualLigatures)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_DiscretionaryLigaturesProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetDiscretionaryLigatures)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetDiscretionaryLigatures)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_HistoricalLigaturesProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetHistoricalLigatures)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetHistoricalLigatures)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StandardSwashesProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStandardSwashes)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* SetStandardSwashes)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* get_ContextualSwashesProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetContextualSwashes)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* SetContextualSwashes)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* get_ContextualAlternatesProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetContextualAlternates)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetContextualAlternates)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticAlternatesProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticAlternates)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticAlternates)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet1Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet1)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet1)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet2Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet2)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet2)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet3Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet3)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet3)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet4Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet4)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet4)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet5Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet5)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet5)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet6Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet6)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet6)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet7Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet7)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet7)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet8Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet8)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet8)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet9Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet9)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet9)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet10Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet10)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet10)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet11Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet11)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet11)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet12Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet12)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet12)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet13Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet13)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet13)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet14Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet14)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet14)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet15Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet15)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet15)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet16Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet16)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet16)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet17Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet17)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet17)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet18Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet18)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet18)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet19Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet19)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet19)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StylisticSet20Property)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetStylisticSet20)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetStylisticSet20)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_CapitalsProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetCapitals)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontCapitals* result);
    HRESULT (STDMETHODCALLTYPE* SetCapitals)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontCapitals value);
    HRESULT (STDMETHODCALLTYPE* get_CapitalSpacingProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetCapitalSpacing)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetCapitalSpacing)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_KerningProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetKerning)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetKerning)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_CaseSensitiveFormsProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetCaseSensitiveForms)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetCaseSensitiveForms)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_HistoricalFormsProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetHistoricalForms)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetHistoricalForms)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_FractionProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetFraction)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontFraction* result);
    HRESULT (STDMETHODCALLTYPE* SetFraction)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontFraction value);
    HRESULT (STDMETHODCALLTYPE* get_NumeralStyleProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetNumeralStyle)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontNumeralStyle* result);
    HRESULT (STDMETHODCALLTYPE* SetNumeralStyle)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontNumeralStyle value);
    HRESULT (STDMETHODCALLTYPE* get_NumeralAlignmentProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetNumeralAlignment)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontNumeralAlignment* result);
    HRESULT (STDMETHODCALLTYPE* SetNumeralAlignment)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontNumeralAlignment value);
    HRESULT (STDMETHODCALLTYPE* get_SlashedZeroProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetSlashedZero)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetSlashedZero)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_MathematicalGreekProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetMathematicalGreek)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetMathematicalGreek)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_VariantsProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetVariants)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontVariants* result);
    HRESULT (STDMETHODCALLTYPE* SetVariants)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFontVariants value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_AnnotationAlternatesProperty(This, value) \
    ((This)->lpVtbl->get_AnnotationAlternatesProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetAnnotationAlternates(This, element, result) \
    ((This)->lpVtbl->GetAnnotationAlternates(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetAnnotationAlternates(This, element, value) \
    ((This)->lpVtbl->SetAnnotationAlternates(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_EastAsianExpertFormsProperty(This, value) \
    ((This)->lpVtbl->get_EastAsianExpertFormsProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetEastAsianExpertForms(This, element, result) \
    ((This)->lpVtbl->GetEastAsianExpertForms(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetEastAsianExpertForms(This, element, value) \
    ((This)->lpVtbl->SetEastAsianExpertForms(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_EastAsianLanguageProperty(This, value) \
    ((This)->lpVtbl->get_EastAsianLanguageProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetEastAsianLanguage(This, element, result) \
    ((This)->lpVtbl->GetEastAsianLanguage(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetEastAsianLanguage(This, element, value) \
    ((This)->lpVtbl->SetEastAsianLanguage(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_EastAsianWidthsProperty(This, value) \
    ((This)->lpVtbl->get_EastAsianWidthsProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetEastAsianWidths(This, element, result) \
    ((This)->lpVtbl->GetEastAsianWidths(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetEastAsianWidths(This, element, value) \
    ((This)->lpVtbl->SetEastAsianWidths(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StandardLigaturesProperty(This, value) \
    ((This)->lpVtbl->get_StandardLigaturesProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStandardLigatures(This, element, result) \
    ((This)->lpVtbl->GetStandardLigatures(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStandardLigatures(This, element, value) \
    ((This)->lpVtbl->SetStandardLigatures(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_ContextualLigaturesProperty(This, value) \
    ((This)->lpVtbl->get_ContextualLigaturesProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetContextualLigatures(This, element, result) \
    ((This)->lpVtbl->GetContextualLigatures(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetContextualLigatures(This, element, value) \
    ((This)->lpVtbl->SetContextualLigatures(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_DiscretionaryLigaturesProperty(This, value) \
    ((This)->lpVtbl->get_DiscretionaryLigaturesProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetDiscretionaryLigatures(This, element, result) \
    ((This)->lpVtbl->GetDiscretionaryLigatures(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetDiscretionaryLigatures(This, element, value) \
    ((This)->lpVtbl->SetDiscretionaryLigatures(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_HistoricalLigaturesProperty(This, value) \
    ((This)->lpVtbl->get_HistoricalLigaturesProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetHistoricalLigatures(This, element, result) \
    ((This)->lpVtbl->GetHistoricalLigatures(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetHistoricalLigatures(This, element, value) \
    ((This)->lpVtbl->SetHistoricalLigatures(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StandardSwashesProperty(This, value) \
    ((This)->lpVtbl->get_StandardSwashesProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStandardSwashes(This, element, result) \
    ((This)->lpVtbl->GetStandardSwashes(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStandardSwashes(This, element, value) \
    ((This)->lpVtbl->SetStandardSwashes(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_ContextualSwashesProperty(This, value) \
    ((This)->lpVtbl->get_ContextualSwashesProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetContextualSwashes(This, element, result) \
    ((This)->lpVtbl->GetContextualSwashes(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetContextualSwashes(This, element, value) \
    ((This)->lpVtbl->SetContextualSwashes(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_ContextualAlternatesProperty(This, value) \
    ((This)->lpVtbl->get_ContextualAlternatesProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetContextualAlternates(This, element, result) \
    ((This)->lpVtbl->GetContextualAlternates(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetContextualAlternates(This, element, value) \
    ((This)->lpVtbl->SetContextualAlternates(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticAlternatesProperty(This, value) \
    ((This)->lpVtbl->get_StylisticAlternatesProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticAlternates(This, element, result) \
    ((This)->lpVtbl->GetStylisticAlternates(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticAlternates(This, element, value) \
    ((This)->lpVtbl->SetStylisticAlternates(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet1Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet1Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet1(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet1(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet1(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet1(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet2Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet2Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet2(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet2(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet2(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet2(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet3Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet3Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet3(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet3(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet3(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet3(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet4Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet4Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet4(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet4(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet4(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet4(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet5Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet5Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet5(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet5(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet5(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet5(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet6Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet6Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet6(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet6(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet6(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet6(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet7Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet7Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet7(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet7(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet7(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet7(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet8Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet8Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet8(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet8(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet8(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet8(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet9Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet9Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet9(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet9(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet9(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet9(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet10Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet10Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet10(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet10(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet10(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet10(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet11Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet11Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet11(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet11(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet11(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet11(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet12Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet12Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet12(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet12(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet12(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet12(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet13Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet13Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet13(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet13(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet13(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet13(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet14Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet14Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet14(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet14(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet14(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet14(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet15Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet15Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet15(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet15(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet15(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet15(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet16Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet16Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet16(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet16(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet16(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet16(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet17Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet17Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet17(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet17(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet17(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet17(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet18Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet18Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet18(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet18(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet18(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet18(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet19Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet19Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet19(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet19(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet19(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet19(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_StylisticSet20Property(This, value) \
    ((This)->lpVtbl->get_StylisticSet20Property(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetStylisticSet20(This, element, result) \
    ((This)->lpVtbl->GetStylisticSet20(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetStylisticSet20(This, element, value) \
    ((This)->lpVtbl->SetStylisticSet20(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_CapitalsProperty(This, value) \
    ((This)->lpVtbl->get_CapitalsProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetCapitals(This, element, result) \
    ((This)->lpVtbl->GetCapitals(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetCapitals(This, element, value) \
    ((This)->lpVtbl->SetCapitals(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_CapitalSpacingProperty(This, value) \
    ((This)->lpVtbl->get_CapitalSpacingProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetCapitalSpacing(This, element, result) \
    ((This)->lpVtbl->GetCapitalSpacing(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetCapitalSpacing(This, element, value) \
    ((This)->lpVtbl->SetCapitalSpacing(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_KerningProperty(This, value) \
    ((This)->lpVtbl->get_KerningProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetKerning(This, element, result) \
    ((This)->lpVtbl->GetKerning(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetKerning(This, element, value) \
    ((This)->lpVtbl->SetKerning(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_CaseSensitiveFormsProperty(This, value) \
    ((This)->lpVtbl->get_CaseSensitiveFormsProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetCaseSensitiveForms(This, element, result) \
    ((This)->lpVtbl->GetCaseSensitiveForms(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetCaseSensitiveForms(This, element, value) \
    ((This)->lpVtbl->SetCaseSensitiveForms(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_HistoricalFormsProperty(This, value) \
    ((This)->lpVtbl->get_HistoricalFormsProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetHistoricalForms(This, element, result) \
    ((This)->lpVtbl->GetHistoricalForms(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetHistoricalForms(This, element, value) \
    ((This)->lpVtbl->SetHistoricalForms(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_FractionProperty(This, value) \
    ((This)->lpVtbl->get_FractionProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetFraction(This, element, result) \
    ((This)->lpVtbl->GetFraction(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetFraction(This, element, value) \
    ((This)->lpVtbl->SetFraction(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_NumeralStyleProperty(This, value) \
    ((This)->lpVtbl->get_NumeralStyleProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetNumeralStyle(This, element, result) \
    ((This)->lpVtbl->GetNumeralStyle(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetNumeralStyle(This, element, value) \
    ((This)->lpVtbl->SetNumeralStyle(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_NumeralAlignmentProperty(This, value) \
    ((This)->lpVtbl->get_NumeralAlignmentProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetNumeralAlignment(This, element, result) \
    ((This)->lpVtbl->GetNumeralAlignment(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetNumeralAlignment(This, element, value) \
    ((This)->lpVtbl->SetNumeralAlignment(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_SlashedZeroProperty(This, value) \
    ((This)->lpVtbl->get_SlashedZeroProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetSlashedZero(This, element, result) \
    ((This)->lpVtbl->GetSlashedZero(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetSlashedZero(This, element, value) \
    ((This)->lpVtbl->SetSlashedZero(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_MathematicalGreekProperty(This, value) \
    ((This)->lpVtbl->get_MathematicalGreekProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetMathematicalGreek(This, element, result) \
    ((This)->lpVtbl->GetMathematicalGreek(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetMathematicalGreek(This, element, value) \
    ((This)->lpVtbl->SetMathematicalGreek(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_get_VariantsProperty(This, value) \
    ((This)->lpVtbl->get_VariantsProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_GetVariants(This, element, result) \
    ((This)->lpVtbl->GetVariants(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_SetVariants(This, element, value) \
    ((This)->lpVtbl->SetVariants(This, element, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CITypographyStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Documents.IUnderline
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Documents.Underline
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Documents_IUnderline[] = L"Microsoft.UI.Xaml.Documents.IUnderline";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderlineVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderlineVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderlineVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CDocuments_CIUnderline_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Block
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.IBlockStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IBlock ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Block_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Block_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Block[] = L"Microsoft.UI.Xaml.Documents.Block";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.BlockCollection
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Windows.Foundation.Collections.IVector`1<Microsoft.UI.Xaml.Documents.Block> ** Default Interface **
 *    Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Xaml.Documents.Block>
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_BlockCollection_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_BlockCollection_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_BlockCollection[] = L"Microsoft.UI.Xaml.Documents.BlockCollection";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Bold
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IBold ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Bold_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Bold_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Bold[] = L"Microsoft.UI.Xaml.Documents.Bold";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Glyphs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.IGlyphsStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IGlyphs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Glyphs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Glyphs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Glyphs[] = L"Microsoft.UI.Xaml.Documents.Glyphs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Hyperlink
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.IHyperlinkStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IHyperlink ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Hyperlink_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Hyperlink_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Hyperlink[] = L"Microsoft.UI.Xaml.Documents.Hyperlink";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.HyperlinkClickEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IHyperlinkClickEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_HyperlinkClickEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_HyperlinkClickEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_HyperlinkClickEventArgs[] = L"Microsoft.UI.Xaml.Documents.HyperlinkClickEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Inline
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IInline ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Inline_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Inline_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Inline[] = L"Microsoft.UI.Xaml.Documents.Inline";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.InlineCollection
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Windows.Foundation.Collections.IVector`1<Microsoft.UI.Xaml.Documents.Inline> ** Default Interface **
 *    Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Xaml.Documents.Inline>
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_InlineCollection_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_InlineCollection_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_InlineCollection[] = L"Microsoft.UI.Xaml.Documents.InlineCollection";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.InlineUIContainer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IInlineUIContainer ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_InlineUIContainer_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_InlineUIContainer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_InlineUIContainer[] = L"Microsoft.UI.Xaml.Documents.InlineUIContainer";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Italic
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IItalic ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Italic_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Italic_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Italic[] = L"Microsoft.UI.Xaml.Documents.Italic";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.LineBreak
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ILineBreak ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_LineBreak_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_LineBreak_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_LineBreak[] = L"Microsoft.UI.Xaml.Documents.LineBreak";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Paragraph
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.IParagraphStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IParagraph ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Paragraph_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Paragraph_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Paragraph[] = L"Microsoft.UI.Xaml.Documents.Paragraph";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Run
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.IRunStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IRun ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Run_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Run_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Run[] = L"Microsoft.UI.Xaml.Documents.Run";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Span
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ISpan ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Span_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Span_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Span[] = L"Microsoft.UI.Xaml.Documents.Span";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.TextElement
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.ITextElementStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ITextElement ** Default Interface **
 *    Microsoft.UI.Xaml.Documents.ITextElementOverrides
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextElement_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextElement_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_TextElement[] = L"Microsoft.UI.Xaml.Documents.TextElement";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.TextHighlighter
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.ITextHighlighterStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ITextHighlighter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextHighlighter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextHighlighter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_TextHighlighter[] = L"Microsoft.UI.Xaml.Documents.TextHighlighter";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.TextHighlighterBase
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ITextHighlighterBase ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextHighlighterBase_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextHighlighterBase_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_TextHighlighterBase[] = L"Microsoft.UI.Xaml.Documents.TextHighlighterBase";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.TextPointer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ITextPointer ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextPointer_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_TextPointer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_TextPointer[] = L"Microsoft.UI.Xaml.Documents.TextPointer";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Typography
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Documents.ITypographyStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.ITypography ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Typography_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Typography_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Typography[] = L"Microsoft.UI.Xaml.Documents.Typography";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Documents.Underline
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Documents.IUnderline ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Underline_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Documents_Underline_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Documents_Underline[] = L"Microsoft.UI.Xaml.Documents.Underline";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Edocuments_p_h__

#endif // __microsoft2Eui2Examl2Edocuments_h__
