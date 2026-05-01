
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
#ifndef __microsoft2Eui2Etext_h__
#define __microsoft2Eui2Etext_h__
#ifndef __microsoft2Eui2Etext_p_h__
#define __microsoft2Eui2Etext_p_h__


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
#if !defined(MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION)
#define MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION)

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
#include "Windows.Storage.Streams.h"
#include "Windows.UI.h"
#include "Windows.UI.Text.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                interface IFontWeights;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeights ABI::Microsoft::UI::Text::IFontWeights

#endif // ____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                interface IFontWeightsStatics;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics ABI::Microsoft::UI::Text::IFontWeightsStatics

#endif // ____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                interface ITextCharacterFormat;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat ABI::Microsoft::UI::Text::ITextCharacterFormat

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                interface ITextConstantsStatics;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics ABI::Microsoft::UI::Text::ITextConstantsStatics

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextDocument_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextDocument_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                interface ITextDocument;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument ABI::Microsoft::UI::Text::ITextDocument

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextDocument_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                interface ITextDocument2;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2 ABI::Microsoft::UI::Text::ITextDocument2

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                interface ITextParagraphFormat;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat ABI::Microsoft::UI::Text::ITextParagraphFormat

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextRange_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextRange_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                interface ITextRange;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CText_CITextRange ABI::Microsoft::UI::Text::ITextRange

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextRange_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextSelection_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextSelection_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                interface ITextSelection;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection ABI::Microsoft::UI::Text::ITextSelection

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextSelection_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
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

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Storage {
            namespace Streams {
                interface IRandomAccessStream;
            } /* Streams */
        } /* Storage */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream ABI::Windows::Storage::Streams::IRandomAccessStream

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace UI {
            typedef struct Color Color;
        } /* UI */
    } /* Windows */
} /* ABI */

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
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum CaretType : int CaretType;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum FindOptions : unsigned int FindOptions;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum FormatEffect : int FormatEffect;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum HorizontalCharacterAlignment : int HorizontalCharacterAlignment;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum LetterCase : int LetterCase;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum LineSpacingRule : int LineSpacingRule;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum LinkType : int LinkType;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum MarkerAlignment : int MarkerAlignment;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum MarkerStyle : int MarkerStyle;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum MarkerType : int MarkerType;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum ParagraphAlignment : int ParagraphAlignment;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum ParagraphStyle : int ParagraphStyle;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum PointOptions : unsigned int PointOptions;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum RangeGravity : int RangeGravity;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum RichEditMathMode : int RichEditMathMode;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum SelectionOptions : unsigned int SelectionOptions;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum SelectionType : int SelectionType;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum TabAlignment : int TabAlignment;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum TabLeader : int TabLeader;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum TextGetOptions : unsigned int TextGetOptions;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum TextRangeUnit : int TextRangeUnit;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum TextScript : int TextScript;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum TextSetOptions : unsigned int TextSetOptions;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum UnderlineType : int UnderlineType;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                typedef enum VerticalCharacterAlignment : int VerticalCharacterAlignment;
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.CaretType
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum CaretType : int
                {
                    CaretType_Normal = 0,
                    CaretType_Null = 1,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.FindOptions
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum FindOptions : unsigned int
                {
                    FindOptions_None = 0,
                    FindOptions_Word = 0x2,
                    FindOptions_Case = 0x4,
                };

                DEFINE_ENUM_FLAG_OPERATORS(FindOptions)
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.FormatEffect
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum FormatEffect : int
                {
                    FormatEffect_Off = 0,
                    FormatEffect_On = 1,
                    FormatEffect_Toggle = 2,
                    FormatEffect_Undefined = 3,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.HorizontalCharacterAlignment
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum HorizontalCharacterAlignment : int
                {
                    HorizontalCharacterAlignment_Left = 0,
                    HorizontalCharacterAlignment_Right = 1,
                    HorizontalCharacterAlignment_Center = 2,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.LetterCase
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum LetterCase : int
                {
                    LetterCase_Lower = 0,
                    LetterCase_Upper = 1,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.LineSpacingRule
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum LineSpacingRule : int
                {
                    LineSpacingRule_Undefined = 0,
                    LineSpacingRule_Single = 1,
                    LineSpacingRule_OneAndHalf = 2,
                    LineSpacingRule_Double = 3,
                    LineSpacingRule_AtLeast = 4,
                    LineSpacingRule_Exactly = 5,
                    LineSpacingRule_Multiple = 6,
                    LineSpacingRule_Percent = 7,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.LinkType
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum LinkType : int
                {
                    LinkType_Undefined = 0,
                    LinkType_NotALink = 1,
                    LinkType_ClientLink = 2,
                    LinkType_FriendlyLinkName = 3,
                    LinkType_FriendlyLinkAddress = 4,
                    LinkType_AutoLink = 5,
                    LinkType_AutoLinkEmail = 6,
                    LinkType_AutoLinkPhone = 7,
                    LinkType_AutoLinkPath = 8,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.MarkerAlignment
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum MarkerAlignment : int
                {
                    MarkerAlignment_Undefined = 0,
                    MarkerAlignment_Left = 1,
                    MarkerAlignment_Center = 2,
                    MarkerAlignment_Right = 3,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.MarkerStyle
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum MarkerStyle : int
                {
                    MarkerStyle_Undefined = 0,
                    MarkerStyle_Parenthesis = 1,
                    MarkerStyle_Parentheses = 2,
                    MarkerStyle_Period = 3,
                    MarkerStyle_Plain = 4,
                    MarkerStyle_Minus = 5,
                    MarkerStyle_NoNumber = 6,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.MarkerType
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum MarkerType : int
                {
                    MarkerType_Undefined = 0,
                    MarkerType_None = 1,
                    MarkerType_Bullet = 2,
                    MarkerType_Arabic = 3,
                    MarkerType_LowercaseEnglishLetter = 4,
                    MarkerType_UppercaseEnglishLetter = 5,
                    MarkerType_LowercaseRoman = 6,
                    MarkerType_UppercaseRoman = 7,
                    MarkerType_UnicodeSequence = 8,
                    MarkerType_CircledNumber = 9,
                    MarkerType_BlackCircleWingding = 10,
                    MarkerType_WhiteCircleWingding = 11,
                    MarkerType_ArabicWide = 12,
                    MarkerType_SimplifiedChinese = 13,
                    MarkerType_TraditionalChinese = 14,
                    MarkerType_JapanSimplifiedChinese = 15,
                    MarkerType_JapanKorea = 16,
                    MarkerType_ArabicDictionary = 17,
                    MarkerType_ArabicAbjad = 18,
                    MarkerType_Hebrew = 19,
                    MarkerType_ThaiAlphabetic = 20,
                    MarkerType_ThaiNumeric = 21,
                    MarkerType_DevanagariVowel = 22,
                    MarkerType_DevanagariConsonant = 23,
                    MarkerType_DevanagariNumeric = 24,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.ParagraphAlignment
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum ParagraphAlignment : int
                {
                    ParagraphAlignment_Undefined = 0,
                    ParagraphAlignment_Left = 1,
                    ParagraphAlignment_Center = 2,
                    ParagraphAlignment_Right = 3,
                    ParagraphAlignment_Justify = 4,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.ParagraphStyle
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum ParagraphStyle : int
                {
                    ParagraphStyle_Undefined = 0,
                    ParagraphStyle_None = 1,
                    ParagraphStyle_Normal = 2,
                    ParagraphStyle_Heading1 = 3,
                    ParagraphStyle_Heading2 = 4,
                    ParagraphStyle_Heading3 = 5,
                    ParagraphStyle_Heading4 = 6,
                    ParagraphStyle_Heading5 = 7,
                    ParagraphStyle_Heading6 = 8,
                    ParagraphStyle_Heading7 = 9,
                    ParagraphStyle_Heading8 = 10,
                    ParagraphStyle_Heading9 = 11,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.PointOptions
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum PointOptions : unsigned int
                {
                    PointOptions_None = 0,
                    PointOptions_IncludeInset = 0x1,
                    PointOptions_Start = 0x20,
                    PointOptions_ClientCoordinates = 0x100,
                    PointOptions_AllowOffClient = 0x200,
                    PointOptions_Transform = 0x400,
                    PointOptions_NoHorizontalScroll = 0x10000,
                    PointOptions_NoVerticalScroll = 0x40000,
                };

                DEFINE_ENUM_FLAG_OPERATORS(PointOptions)
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.RangeGravity
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum RangeGravity : int
                {
                    RangeGravity_UIBehavior = 0,
                    RangeGravity_Backward = 1,
                    RangeGravity_Forward = 2,
                    RangeGravity_Inward = 3,
                    RangeGravity_Outward = 4,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.RichEditMathMode
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum RichEditMathMode : int
                {
                    RichEditMathMode_NoMath = 0,
                    RichEditMathMode_MathOnly = 1,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.SelectionOptions
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum SelectionOptions : unsigned int
                {
                    SelectionOptions_StartActive = 0x1,
                    SelectionOptions_AtEndOfLine = 0x2,
                    SelectionOptions_Overtype = 0x4,
                    SelectionOptions_Active = 0x8,
                    SelectionOptions_Replace = 0x10,
                };

                DEFINE_ENUM_FLAG_OPERATORS(SelectionOptions)
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.SelectionType
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum SelectionType : int
                {
                    SelectionType_None = 0,
                    SelectionType_InsertionPoint = 1,
                    SelectionType_Normal = 2,
                    SelectionType_InlineShape = 7,
                    SelectionType_Shape = 8,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.TabAlignment
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum TabAlignment : int
                {
                    TabAlignment_Left = 0,
                    TabAlignment_Center = 1,
                    TabAlignment_Right = 2,
                    TabAlignment_Decimal = 3,
                    TabAlignment_Bar = 4,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.TabLeader
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum TabLeader : int
                {
                    TabLeader_Spaces = 0,
                    TabLeader_Dots = 1,
                    TabLeader_Dashes = 2,
                    TabLeader_Lines = 3,
                    TabLeader_ThickLines = 4,
                    TabLeader_Equals = 5,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.TextGetOptions
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum TextGetOptions : unsigned int
                {
                    TextGetOptions_None = 0,
                    TextGetOptions_AdjustCrlf = 0x1,
                    TextGetOptions_UseCrlf = 0x2,
                    TextGetOptions_UseObjectText = 0x4,
                    TextGetOptions_AllowFinalEop = 0x8,
                    TextGetOptions_NoHidden = 0x20,
                    TextGetOptions_IncludeNumbering = 0x40,
                    TextGetOptions_FormatRtf = 0x2000,
                    TextGetOptions_UseLf = 0x1000000,
                };

                DEFINE_ENUM_FLAG_OPERATORS(TextGetOptions)
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.TextRangeUnit
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum TextRangeUnit : int
                {
                    TextRangeUnit_Character = 0,
                    TextRangeUnit_Word = 1,
                    TextRangeUnit_Sentence = 2,
                    TextRangeUnit_Paragraph = 3,
                    TextRangeUnit_Line = 4,
                    TextRangeUnit_Story = 5,
                    TextRangeUnit_Screen = 6,
                    TextRangeUnit_Section = 7,
                    TextRangeUnit_Window = 8,
                    TextRangeUnit_CharacterFormat = 9,
                    TextRangeUnit_ParagraphFormat = 10,
                    TextRangeUnit_Object = 11,
                    TextRangeUnit_HardParagraph = 12,
                    TextRangeUnit_Cluster = 13,
                    TextRangeUnit_Bold = 14,
                    TextRangeUnit_Italic = 15,
                    TextRangeUnit_Underline = 16,
                    TextRangeUnit_Strikethrough = 17,
                    TextRangeUnit_ProtectedText = 18,
                    TextRangeUnit_Link = 19,
                    TextRangeUnit_SmallCaps = 20,
                    TextRangeUnit_AllCaps = 21,
                    TextRangeUnit_Hidden = 22,
                    TextRangeUnit_Outline = 23,
                    TextRangeUnit_Shadow = 24,
                    TextRangeUnit_Imprint = 25,
                    TextRangeUnit_Disabled = 26,
                    TextRangeUnit_Revised = 27,
                    TextRangeUnit_Subscript = 28,
                    TextRangeUnit_Superscript = 29,
                    TextRangeUnit_FontBound = 30,
                    TextRangeUnit_LinkProtected = 31,
                    TextRangeUnit_ContentLink = 32,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.TextScript
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum TextScript : int
                {
                    TextScript_Undefined = 0,
                    TextScript_Ansi = 1,
                    TextScript_EastEurope = 2,
                    TextScript_Cyrillic = 3,
                    TextScript_Greek = 4,
                    TextScript_Turkish = 5,
                    TextScript_Hebrew = 6,
                    TextScript_Arabic = 7,
                    TextScript_Baltic = 8,
                    TextScript_Vietnamese = 9,
                    TextScript_Default = 10,
                    TextScript_Symbol = 11,
                    TextScript_Thai = 12,
                    TextScript_ShiftJis = 13,
                    TextScript_GB2312 = 14,
                    TextScript_Hangul = 15,
                    TextScript_Big5 = 16,
                    TextScript_PC437 = 17,
                    TextScript_Oem = 18,
                    TextScript_Mac = 19,
                    TextScript_Armenian = 20,
                    TextScript_Syriac = 21,
                    TextScript_Thaana = 22,
                    TextScript_Devanagari = 23,
                    TextScript_Bengali = 24,
                    TextScript_Gurmukhi = 25,
                    TextScript_Gujarati = 26,
                    TextScript_Oriya = 27,
                    TextScript_Tamil = 28,
                    TextScript_Telugu = 29,
                    TextScript_Kannada = 30,
                    TextScript_Malayalam = 31,
                    TextScript_Sinhala = 32,
                    TextScript_Lao = 33,
                    TextScript_Tibetan = 34,
                    TextScript_Myanmar = 35,
                    TextScript_Georgian = 36,
                    TextScript_Jamo = 37,
                    TextScript_Ethiopic = 38,
                    TextScript_Cherokee = 39,
                    TextScript_Aboriginal = 40,
                    TextScript_Ogham = 41,
                    TextScript_Runic = 42,
                    TextScript_Khmer = 43,
                    TextScript_Mongolian = 44,
                    TextScript_Braille = 45,
                    TextScript_Yi = 46,
                    TextScript_Limbu = 47,
                    TextScript_TaiLe = 48,
                    TextScript_NewTaiLue = 49,
                    TextScript_SylotiNagri = 50,
                    TextScript_Kharoshthi = 51,
                    TextScript_Kayahli = 52,
                    TextScript_UnicodeSymbol = 53,
                    TextScript_Emoji = 54,
                    TextScript_Glagolitic = 55,
                    TextScript_Lisu = 56,
                    TextScript_Vai = 57,
                    TextScript_NKo = 58,
                    TextScript_Osmanya = 59,
                    TextScript_PhagsPa = 60,
                    TextScript_Gothic = 61,
                    TextScript_Deseret = 62,
                    TextScript_Tifinagh = 63,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.TextSetOptions
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum TextSetOptions : unsigned int
                {
                    TextSetOptions_None = 0,
                    TextSetOptions_UnicodeBidi = 0x1,
                    TextSetOptions_Unlink = 0x8,
                    TextSetOptions_Unhide = 0x10,
                    TextSetOptions_CheckTextLimit = 0x20,
                    TextSetOptions_FormatRtf = 0x2000,
                    TextSetOptions_ApplyRtfDocumentDefaults = 0x4000,
                };

                DEFINE_ENUM_FLAG_OPERATORS(TextSetOptions)
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.UnderlineType
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum UnderlineType : int
                {
                    UnderlineType_Undefined = 0,
                    UnderlineType_None = 1,
                    UnderlineType_Single = 2,
                    UnderlineType_Words = 3,
                    UnderlineType_Double = 4,
                    UnderlineType_Dotted = 5,
                    UnderlineType_Dash = 6,
                    UnderlineType_DashDot = 7,
                    UnderlineType_DashDotDot = 8,
                    UnderlineType_Wave = 9,
                    UnderlineType_Thick = 10,
                    UnderlineType_Thin = 11,
                    UnderlineType_DoubleWave = 12,
                    UnderlineType_HeavyWave = 13,
                    UnderlineType_LongDash = 14,
                    UnderlineType_ThickDash = 15,
                    UnderlineType_ThickDashDot = 16,
                    UnderlineType_ThickDashDotDot = 17,
                    UnderlineType_ThickDotted = 18,
                    UnderlineType_ThickLongDash = 19,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Text.VerticalCharacterAlignment
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                enum VerticalCharacterAlignment : int
                {
                    VerticalCharacterAlignment_Top = 0,
                    VerticalCharacterAlignment_Baseline = 1,
                    VerticalCharacterAlignment_Bottom = 2,
                };
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Interface Microsoft.UI.Text.IFontWeights
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Text.FontWeights
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_IFontWeights[] = L"Microsoft.UI.Text.IFontWeights";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                MIDL_INTERFACE("386cd040-5404-5a8d-8bc7-2ca989f5c065")
                IFontWeights : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IFontWeights = _uuidof(IFontWeights);
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CIFontWeights;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.IFontWeightsStatics
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Text.FontWeights
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_IFontWeightsStatics[] = L"Microsoft.UI.Text.IFontWeightsStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                MIDL_INTERFACE("cc390df6-76b0-5807-8b9d-e949a4e623ae")
                IFontWeightsStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Black(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Bold(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ExtraBlack(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ExtraBold(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ExtraLight(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Light(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Medium(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Normal(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SemiBold(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SemiLight(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Thin(
                        ABI::Windows::UI::Text::FontWeight* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IFontWeightsStatics = _uuidof(IFontWeightsStatics);
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextCharacterFormat
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextCharacterFormat[] = L"Microsoft.UI.Text.ITextCharacterFormat";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                MIDL_INTERFACE("f5710050-98e5-5788-b1e3-32191eebf94d")
                ITextCharacterFormat : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AllCaps(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_AllCaps(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_BackgroundColor(
                        ABI::Windows::UI::Color* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_BackgroundColor(
                        ABI::Windows::UI::Color value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Bold(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Bold(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_FontStretch(
                        ABI::Windows::UI::Text::FontStretch* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_FontStretch(
                        ABI::Windows::UI::Text::FontStretch value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_FontStyle(
                        ABI::Windows::UI::Text::FontStyle* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_FontStyle(
                        ABI::Windows::UI::Text::FontStyle value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ForegroundColor(
                        ABI::Windows::UI::Color* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ForegroundColor(
                        ABI::Windows::UI::Color value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Hidden(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Hidden(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Italic(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Italic(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Kerning(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Kerning(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LanguageTag(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_LanguageTag(
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LinkType(
                        ABI::Microsoft::UI::Text::LinkType* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Name(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Name(
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Outline(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Outline(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Position(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Position(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ProtectedText(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ProtectedText(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Size(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Size(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SmallCaps(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_SmallCaps(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Spacing(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Spacing(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Strikethrough(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Strikethrough(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Subscript(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Subscript(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Superscript(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Superscript(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_TextScript(
                        ABI::Microsoft::UI::Text::TextScript* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_TextScript(
                        ABI::Microsoft::UI::Text::TextScript value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Underline(
                        ABI::Microsoft::UI::Text::UnderlineType* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Underline(
                        ABI::Microsoft::UI::Text::UnderlineType value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Weight(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Weight(
                        INT32 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetClone(
                        ABI::Microsoft::UI::Text::ITextCharacterFormat* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetClone(
                        ABI::Microsoft::UI::Text::ITextCharacterFormat** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE IsEqual(
                        ABI::Microsoft::UI::Text::ITextCharacterFormat* format,
                        boolean* result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_ITextCharacterFormat = _uuidof(ITextCharacterFormat);
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextConstantsStatics
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Text.TextConstants
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextConstantsStatics[] = L"Microsoft.UI.Text.ITextConstantsStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                MIDL_INTERFACE("cd353b3c-af63-5cfb-918c-0f9c8931a161")
                ITextConstantsStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AutoColor(
                        ABI::Windows::UI::Color* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_MinUnitCount(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_MaxUnitCount(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_UndefinedColor(
                        ABI::Windows::UI::Color* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_UndefinedFloatValue(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_UndefinedInt32Value(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_UndefinedFontStretch(
                        ABI::Windows::UI::Text::FontStretch* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_UndefinedFontStyle(
                        ABI::Windows::UI::Text::FontStyle* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_ITextConstantsStatics = _uuidof(ITextConstantsStatics);
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextDocument
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Text.RichEditTextDocument
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextDocument_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextDocument_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextDocument[] = L"Microsoft.UI.Text.ITextDocument";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                MIDL_INTERFACE("1149d57d-86a6-59dd-88d9-196f27bc5c85")
                ITextDocument : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_CaretType(
                        ABI::Microsoft::UI::Text::CaretType* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_CaretType(
                        ABI::Microsoft::UI::Text::CaretType value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DefaultTabStop(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_DefaultTabStop(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Selection(
                        ABI::Microsoft::UI::Text::ITextSelection** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_UndoLimit(
                        UINT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_UndoLimit(
                        UINT32 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CanCopy(
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CanPaste(
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CanRedo(
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CanUndo(
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ApplyDisplayUpdates(
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE BatchDisplayUpdates(
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE BeginUndoGroup(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE EndUndoGroup(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetDefaultCharacterFormat(
                        ABI::Microsoft::UI::Text::ITextCharacterFormat** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetDefaultParagraphFormat(
                        ABI::Microsoft::UI::Text::ITextParagraphFormat** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetRange(
                        INT32 startPosition,
                        INT32 endPosition,
                        ABI::Microsoft::UI::Text::ITextRange** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetRangeFromPoint(
                        ABI::Windows::Foundation::Point point,
                        ABI::Microsoft::UI::Text::PointOptions options,
                        ABI::Microsoft::UI::Text::ITextRange** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetText(
                        ABI::Microsoft::UI::Text::TextGetOptions options,
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE LoadFromStream(
                        ABI::Microsoft::UI::Text::TextSetOptions options,
                        ABI::Windows::Storage::Streams::IRandomAccessStream* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Redo(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SaveToStream(
                        ABI::Microsoft::UI::Text::TextGetOptions options,
                        ABI::Windows::Storage::Streams::IRandomAccessStream* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetDefaultCharacterFormat(
                        ABI::Microsoft::UI::Text::ITextCharacterFormat* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetDefaultParagraphFormat(
                        ABI::Microsoft::UI::Text::ITextParagraphFormat* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetText(
                        ABI::Microsoft::UI::Text::TextSetOptions options,
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Undo(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_AlignmentIncludesTrailingWhitespace(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_AlignmentIncludesTrailingWhitespace(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IgnoreTrailingCharacterSpacing(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IgnoreTrailingCharacterSpacing(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ClearUndoRedoHistory(void) = 0;
                };

                MIDL_CONST_ID IID& IID_ITextDocument = _uuidof(ITextDocument);
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextDocument;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextDocument_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextDocument2
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Text.RichEditTextDocument
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextDocument2[] = L"Microsoft.UI.Text.ITextDocument2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                MIDL_INTERFACE("21febcf1-2110-5879-b1da-b343097e71e1")
                ITextDocument2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE GetMathMode(
                        ABI::Microsoft::UI::Text::RichEditMathMode* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetMathMode(
                        ABI::Microsoft::UI::Text::RichEditMathMode mode
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetMathML(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetMathML(
                        HSTRING value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_ITextDocument2 = _uuidof(ITextDocument2);
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextDocument2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.UI.Text.ITextParagraphFormat
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextParagraphFormat[] = L"Microsoft.UI.Text.ITextParagraphFormat";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                MIDL_INTERFACE("219b6cdf-0d0b-5701-b8a1-6c906b3ebbe1")
                ITextParagraphFormat : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Alignment(
                        ABI::Microsoft::UI::Text::ParagraphAlignment* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Alignment(
                        ABI::Microsoft::UI::Text::ParagraphAlignment value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_FirstLineIndent(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_KeepTogether(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_KeepTogether(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_KeepWithNext(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_KeepWithNext(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LeftIndent(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LineSpacing(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LineSpacingRule(
                        ABI::Microsoft::UI::Text::LineSpacingRule* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ListAlignment(
                        ABI::Microsoft::UI::Text::MarkerAlignment* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ListAlignment(
                        ABI::Microsoft::UI::Text::MarkerAlignment value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ListLevelIndex(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ListLevelIndex(
                        INT32 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ListStart(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ListStart(
                        INT32 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ListStyle(
                        ABI::Microsoft::UI::Text::MarkerStyle* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ListStyle(
                        ABI::Microsoft::UI::Text::MarkerStyle value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ListTab(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ListTab(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ListType(
                        ABI::Microsoft::UI::Text::MarkerType* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ListType(
                        ABI::Microsoft::UI::Text::MarkerType value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_NoLineNumber(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_NoLineNumber(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_PageBreakBefore(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_PageBreakBefore(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_RightIndent(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_RightIndent(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_RightToLeft(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_RightToLeft(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Style(
                        ABI::Microsoft::UI::Text::ParagraphStyle* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Style(
                        ABI::Microsoft::UI::Text::ParagraphStyle value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SpaceAfter(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_SpaceAfter(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SpaceBefore(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_SpaceBefore(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_WidowControl(
                        ABI::Microsoft::UI::Text::FormatEffect* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_WidowControl(
                        ABI::Microsoft::UI::Text::FormatEffect value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_TabCount(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE AddTab(
                        FLOAT position,
                        ABI::Microsoft::UI::Text::TabAlignment align,
                        ABI::Microsoft::UI::Text::TabLeader leader
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ClearAllTabs(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE DeleteTab(
                        FLOAT position
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetClone(
                        ABI::Microsoft::UI::Text::ITextParagraphFormat** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetTab(
                        INT32 index,
                        FLOAT* position,
                        ABI::Microsoft::UI::Text::TabAlignment* align,
                        ABI::Microsoft::UI::Text::TabLeader* leader
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE IsEqual(
                        ABI::Microsoft::UI::Text::ITextParagraphFormat* format,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetClone(
                        ABI::Microsoft::UI::Text::ITextParagraphFormat* format
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetIndents(
                        FLOAT start,
                        FLOAT left,
                        FLOAT right
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetLineSpacing(
                        ABI::Microsoft::UI::Text::LineSpacingRule rule,
                        FLOAT spacing
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_ITextParagraphFormat = _uuidof(ITextParagraphFormat);
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextRange
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextRange_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextRange_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextRange[] = L"Microsoft.UI.Text.ITextRange";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                MIDL_INTERFACE("06d4abcf-0c06-5d12-a743-85537efd09ea")
                ITextRange : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Character(
                        WCHAR* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Character(
                        WCHAR value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_CharacterFormat(
                        ABI::Microsoft::UI::Text::ITextCharacterFormat** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_CharacterFormat(
                        ABI::Microsoft::UI::Text::ITextCharacterFormat* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_FormattedText(
                        ABI::Microsoft::UI::Text::ITextRange** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_FormattedText(
                        ABI::Microsoft::UI::Text::ITextRange* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_EndPosition(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_EndPosition(
                        INT32 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Gravity(
                        ABI::Microsoft::UI::Text::RangeGravity* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Gravity(
                        ABI::Microsoft::UI::Text::RangeGravity value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Length(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Link(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Link(
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ParagraphFormat(
                        ABI::Microsoft::UI::Text::ITextParagraphFormat** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ParagraphFormat(
                        ABI::Microsoft::UI::Text::ITextParagraphFormat* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_StartPosition(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_StartPosition(
                        INT32 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_StoryLength(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Text(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Text(
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CanPaste(
                        INT32 format,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ChangeCase(
                        ABI::Microsoft::UI::Text::LetterCase value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Collapse(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Copy(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Cut(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Delete(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32 count,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE EndOf(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        boolean extend,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Expand(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FindText(
                        HSTRING value,
                        INT32 scanLength,
                        ABI::Microsoft::UI::Text::FindOptions options,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetCharacterUtf32(
                        UINT32* value,
                        INT32 offset
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetClone(
                        ABI::Microsoft::UI::Text::ITextRange** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetIndex(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetPoint(
                        ABI::Microsoft::UI::Text::HorizontalCharacterAlignment horizontalAlign,
                        ABI::Microsoft::UI::Text::VerticalCharacterAlignment verticalAlign,
                        ABI::Microsoft::UI::Text::PointOptions options,
                        ABI::Windows::Foundation::Point* point
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetRect(
                        ABI::Microsoft::UI::Text::PointOptions options,
                        ABI::Windows::Foundation::Rect* rect,
                        INT32* hit
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetText(
                        ABI::Microsoft::UI::Text::TextGetOptions options,
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetTextViaStream(
                        ABI::Microsoft::UI::Text::TextGetOptions options,
                        ABI::Windows::Storage::Streams::IRandomAccessStream* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE InRange(
                        ABI::Microsoft::UI::Text::ITextRange* range,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE InsertImage(
                        INT32 width,
                        INT32 height,
                        INT32 ascent,
                        ABI::Microsoft::UI::Text::VerticalCharacterAlignment verticalAlign,
                        HSTRING alternateText,
                        ABI::Windows::Storage::Streams::IRandomAccessStream* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE InStory(
                        ABI::Microsoft::UI::Text::ITextRange* range,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE IsEqual(
                        ABI::Microsoft::UI::Text::ITextRange* range,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Move(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32 count,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveEnd(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32 count,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveStart(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32 count,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Paste(
                        INT32 format
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ScrollIntoView(
                        ABI::Microsoft::UI::Text::PointOptions value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MatchSelection(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetIndex(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32 index,
                        boolean extend
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetPoint(
                        ABI::Windows::Foundation::Point point,
                        ABI::Microsoft::UI::Text::PointOptions options,
                        boolean extend
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetRange(
                        INT32 startPosition,
                        INT32 endPosition
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetText(
                        ABI::Microsoft::UI::Text::TextSetOptions options,
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetTextViaStream(
                        ABI::Microsoft::UI::Text::TextSetOptions options,
                        ABI::Windows::Storage::Streams::IRandomAccessStream* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE StartOf(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        boolean extend,
                        INT32* result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_ITextRange = _uuidof(ITextRange);
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextRange;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextRange_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextSelection
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Text.ITextRange
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextSelection_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextSelection_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextSelection[] = L"Microsoft.UI.Text.ITextSelection";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Text {
                MIDL_INTERFACE("8f5e6cb1-2b04-589f-bd24-54e5cd8dd399")
                ITextSelection : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Options(
                        ABI::Microsoft::UI::Text::SelectionOptions* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Options(
                        ABI::Microsoft::UI::Text::SelectionOptions value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Type(
                        ABI::Microsoft::UI::Text::SelectionType* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE EndKey(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        boolean extend,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE HomeKey(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        boolean extend,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveDown(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32 count,
                        boolean extend,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveLeft(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32 count,
                        boolean extend,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveRight(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32 count,
                        boolean extend,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveUp(
                        ABI::Microsoft::UI::Text::TextRangeUnit unit,
                        INT32 count,
                        boolean extend,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE TypeText(
                        HSTRING value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_ITextSelection = _uuidof(ITextSelection);
            } /* Text */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextSelection;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextSelection_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Text.FontWeights
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Text.IFontWeightsStatics interface starting with version 1.0 of the Microsoft.UI.Text.TextApiContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Text.IFontWeights ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Text_FontWeights_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Text_FontWeights_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Text_FontWeights[] = L"Microsoft.UI.Text.FontWeights";
#endif
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Text.RichEditTextDocument
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Text.ITextDocument ** Default Interface **
 *    Microsoft.UI.Text.ITextDocument2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Text_RichEditTextDocument_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Text_RichEditTextDocument_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Text_RichEditTextDocument[] = L"Microsoft.UI.Text.RichEditTextDocument";
#endif
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Text.RichEditTextRange
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Text.ITextRange ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Text_RichEditTextRange_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Text_RichEditTextRange_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Text_RichEditTextRange[] = L"Microsoft.UI.Text.RichEditTextRange";
#endif
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Text.TextConstants
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Text.ITextConstantsStatics interface starting with version 1.0 of the Microsoft.UI.Text.TextApiContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Text_TextConstants_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Text_TextConstants_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Text_TextConstants[] = L"Microsoft.UI.Text.TextConstants";
#endif
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CText_CIFontWeights __x_ABI_CMicrosoft_CUI_CText_CIFontWeights;

#endif // ____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat;

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextDocument_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextDocument_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CText_CITextDocument __x_ABI_CMicrosoft_CUI_CText_CITextDocument;

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextDocument_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CText_CITextDocument2 __x_ABI_CMicrosoft_CUI_CText_CITextDocument2;

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat;

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextRange_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextRange_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CText_CITextRange __x_ABI_CMicrosoft_CUI_CText_CITextRange;

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextRange_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CText_CITextSelection_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CText_CITextSelection_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CText_CITextSelection __x_ABI_CMicrosoft_CUI_CText_CITextSelection;

#endif // ____x_ABI_CMicrosoft_CUI_CText_CITextSelection_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef struct __x_ABI_CWindows_CFoundation_CPoint __x_ABI_CWindows_CFoundation_CPoint;

typedef struct __x_ABI_CWindows_CFoundation_CRect __x_ABI_CWindows_CFoundation_CRect;

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream;

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CUI_CColor __x_ABI_CWindows_CUI_CColor;

typedef enum __x_ABI_CWindows_CUI_CText_CFontStretch __x_ABI_CWindows_CUI_CText_CFontStretch;

typedef enum __x_ABI_CWindows_CUI_CText_CFontStyle __x_ABI_CWindows_CUI_CText_CFontStyle;

typedef struct __x_ABI_CWindows_CUI_CText_CFontWeight __x_ABI_CWindows_CUI_CText_CFontWeight;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CCaretType __x_ABI_CMicrosoft_CUI_CText_CCaretType;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CFindOptions __x_ABI_CMicrosoft_CUI_CText_CFindOptions;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect __x_ABI_CMicrosoft_CUI_CText_CFormatEffect;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CHorizontalCharacterAlignment __x_ABI_CMicrosoft_CUI_CText_CHorizontalCharacterAlignment;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CLetterCase __x_ABI_CMicrosoft_CUI_CText_CLetterCase;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CLineSpacingRule __x_ABI_CMicrosoft_CUI_CText_CLineSpacingRule;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CLinkType __x_ABI_CMicrosoft_CUI_CText_CLinkType;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CMarkerAlignment __x_ABI_CMicrosoft_CUI_CText_CMarkerAlignment;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CMarkerStyle __x_ABI_CMicrosoft_CUI_CText_CMarkerStyle;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CMarkerType __x_ABI_CMicrosoft_CUI_CText_CMarkerType;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CParagraphAlignment __x_ABI_CMicrosoft_CUI_CText_CParagraphAlignment;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CParagraphStyle __x_ABI_CMicrosoft_CUI_CText_CParagraphStyle;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CPointOptions __x_ABI_CMicrosoft_CUI_CText_CPointOptions;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CRangeGravity __x_ABI_CMicrosoft_CUI_CText_CRangeGravity;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CRichEditMathMode __x_ABI_CMicrosoft_CUI_CText_CRichEditMathMode;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CSelectionOptions __x_ABI_CMicrosoft_CUI_CText_CSelectionOptions;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CSelectionType __x_ABI_CMicrosoft_CUI_CText_CSelectionType;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CTabAlignment __x_ABI_CMicrosoft_CUI_CText_CTabAlignment;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CTabLeader __x_ABI_CMicrosoft_CUI_CText_CTabLeader;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CTextGetOptions __x_ABI_CMicrosoft_CUI_CText_CTextGetOptions;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CTextScript __x_ABI_CMicrosoft_CUI_CText_CTextScript;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CTextSetOptions __x_ABI_CMicrosoft_CUI_CText_CTextSetOptions;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CUnderlineType __x_ABI_CMicrosoft_CUI_CText_CUnderlineType;

typedef enum __x_ABI_CMicrosoft_CUI_CText_CVerticalCharacterAlignment __x_ABI_CMicrosoft_CUI_CText_CVerticalCharacterAlignment;

/*
 *
 * Struct Microsoft.UI.Text.CaretType
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CCaretType
{
    CaretType_Normal = 0,
    CaretType_Null = 1,
};

/*
 *
 * Struct Microsoft.UI.Text.FindOptions
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CFindOptions
{
    FindOptions_None = 0,
    FindOptions_Word = 0x2,
    FindOptions_Case = 0x4,
};

/*
 *
 * Struct Microsoft.UI.Text.FormatEffect
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect
{
    FormatEffect_Off = 0,
    FormatEffect_On = 1,
    FormatEffect_Toggle = 2,
    FormatEffect_Undefined = 3,
};

/*
 *
 * Struct Microsoft.UI.Text.HorizontalCharacterAlignment
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CHorizontalCharacterAlignment
{
    HorizontalCharacterAlignment_Left = 0,
    HorizontalCharacterAlignment_Right = 1,
    HorizontalCharacterAlignment_Center = 2,
};

/*
 *
 * Struct Microsoft.UI.Text.LetterCase
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CLetterCase
{
    LetterCase_Lower = 0,
    LetterCase_Upper = 1,
};

/*
 *
 * Struct Microsoft.UI.Text.LineSpacingRule
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CLineSpacingRule
{
    LineSpacingRule_Undefined = 0,
    LineSpacingRule_Single = 1,
    LineSpacingRule_OneAndHalf = 2,
    LineSpacingRule_Double = 3,
    LineSpacingRule_AtLeast = 4,
    LineSpacingRule_Exactly = 5,
    LineSpacingRule_Multiple = 6,
    LineSpacingRule_Percent = 7,
};

/*
 *
 * Struct Microsoft.UI.Text.LinkType
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CLinkType
{
    LinkType_Undefined = 0,
    LinkType_NotALink = 1,
    LinkType_ClientLink = 2,
    LinkType_FriendlyLinkName = 3,
    LinkType_FriendlyLinkAddress = 4,
    LinkType_AutoLink = 5,
    LinkType_AutoLinkEmail = 6,
    LinkType_AutoLinkPhone = 7,
    LinkType_AutoLinkPath = 8,
};

/*
 *
 * Struct Microsoft.UI.Text.MarkerAlignment
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CMarkerAlignment
{
    MarkerAlignment_Undefined = 0,
    MarkerAlignment_Left = 1,
    MarkerAlignment_Center = 2,
    MarkerAlignment_Right = 3,
};

/*
 *
 * Struct Microsoft.UI.Text.MarkerStyle
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CMarkerStyle
{
    MarkerStyle_Undefined = 0,
    MarkerStyle_Parenthesis = 1,
    MarkerStyle_Parentheses = 2,
    MarkerStyle_Period = 3,
    MarkerStyle_Plain = 4,
    MarkerStyle_Minus = 5,
    MarkerStyle_NoNumber = 6,
};

/*
 *
 * Struct Microsoft.UI.Text.MarkerType
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CMarkerType
{
    MarkerType_Undefined = 0,
    MarkerType_None = 1,
    MarkerType_Bullet = 2,
    MarkerType_Arabic = 3,
    MarkerType_LowercaseEnglishLetter = 4,
    MarkerType_UppercaseEnglishLetter = 5,
    MarkerType_LowercaseRoman = 6,
    MarkerType_UppercaseRoman = 7,
    MarkerType_UnicodeSequence = 8,
    MarkerType_CircledNumber = 9,
    MarkerType_BlackCircleWingding = 10,
    MarkerType_WhiteCircleWingding = 11,
    MarkerType_ArabicWide = 12,
    MarkerType_SimplifiedChinese = 13,
    MarkerType_TraditionalChinese = 14,
    MarkerType_JapanSimplifiedChinese = 15,
    MarkerType_JapanKorea = 16,
    MarkerType_ArabicDictionary = 17,
    MarkerType_ArabicAbjad = 18,
    MarkerType_Hebrew = 19,
    MarkerType_ThaiAlphabetic = 20,
    MarkerType_ThaiNumeric = 21,
    MarkerType_DevanagariVowel = 22,
    MarkerType_DevanagariConsonant = 23,
    MarkerType_DevanagariNumeric = 24,
};

/*
 *
 * Struct Microsoft.UI.Text.ParagraphAlignment
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CParagraphAlignment
{
    ParagraphAlignment_Undefined = 0,
    ParagraphAlignment_Left = 1,
    ParagraphAlignment_Center = 2,
    ParagraphAlignment_Right = 3,
    ParagraphAlignment_Justify = 4,
};

/*
 *
 * Struct Microsoft.UI.Text.ParagraphStyle
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CParagraphStyle
{
    ParagraphStyle_Undefined = 0,
    ParagraphStyle_None = 1,
    ParagraphStyle_Normal = 2,
    ParagraphStyle_Heading1 = 3,
    ParagraphStyle_Heading2 = 4,
    ParagraphStyle_Heading3 = 5,
    ParagraphStyle_Heading4 = 6,
    ParagraphStyle_Heading5 = 7,
    ParagraphStyle_Heading6 = 8,
    ParagraphStyle_Heading7 = 9,
    ParagraphStyle_Heading8 = 10,
    ParagraphStyle_Heading9 = 11,
};

/*
 *
 * Struct Microsoft.UI.Text.PointOptions
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CPointOptions
{
    PointOptions_None = 0,
    PointOptions_IncludeInset = 0x1,
    PointOptions_Start = 0x20,
    PointOptions_ClientCoordinates = 0x100,
    PointOptions_AllowOffClient = 0x200,
    PointOptions_Transform = 0x400,
    PointOptions_NoHorizontalScroll = 0x10000,
    PointOptions_NoVerticalScroll = 0x40000,
};

/*
 *
 * Struct Microsoft.UI.Text.RangeGravity
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CRangeGravity
{
    RangeGravity_UIBehavior = 0,
    RangeGravity_Backward = 1,
    RangeGravity_Forward = 2,
    RangeGravity_Inward = 3,
    RangeGravity_Outward = 4,
};

/*
 *
 * Struct Microsoft.UI.Text.RichEditMathMode
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CRichEditMathMode
{
    RichEditMathMode_NoMath = 0,
    RichEditMathMode_MathOnly = 1,
};

/*
 *
 * Struct Microsoft.UI.Text.SelectionOptions
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CSelectionOptions
{
    SelectionOptions_StartActive = 0x1,
    SelectionOptions_AtEndOfLine = 0x2,
    SelectionOptions_Overtype = 0x4,
    SelectionOptions_Active = 0x8,
    SelectionOptions_Replace = 0x10,
};

/*
 *
 * Struct Microsoft.UI.Text.SelectionType
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CSelectionType
{
    SelectionType_None = 0,
    SelectionType_InsertionPoint = 1,
    SelectionType_Normal = 2,
    SelectionType_InlineShape = 7,
    SelectionType_Shape = 8,
};

/*
 *
 * Struct Microsoft.UI.Text.TabAlignment
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CTabAlignment
{
    TabAlignment_Left = 0,
    TabAlignment_Center = 1,
    TabAlignment_Right = 2,
    TabAlignment_Decimal = 3,
    TabAlignment_Bar = 4,
};

/*
 *
 * Struct Microsoft.UI.Text.TabLeader
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CTabLeader
{
    TabLeader_Spaces = 0,
    TabLeader_Dots = 1,
    TabLeader_Dashes = 2,
    TabLeader_Lines = 3,
    TabLeader_ThickLines = 4,
    TabLeader_Equals = 5,
};

/*
 *
 * Struct Microsoft.UI.Text.TextGetOptions
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CTextGetOptions
{
    TextGetOptions_None = 0,
    TextGetOptions_AdjustCrlf = 0x1,
    TextGetOptions_UseCrlf = 0x2,
    TextGetOptions_UseObjectText = 0x4,
    TextGetOptions_AllowFinalEop = 0x8,
    TextGetOptions_NoHidden = 0x20,
    TextGetOptions_IncludeNumbering = 0x40,
    TextGetOptions_FormatRtf = 0x2000,
    TextGetOptions_UseLf = 0x1000000,
};

/*
 *
 * Struct Microsoft.UI.Text.TextRangeUnit
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit
{
    TextRangeUnit_Character = 0,
    TextRangeUnit_Word = 1,
    TextRangeUnit_Sentence = 2,
    TextRangeUnit_Paragraph = 3,
    TextRangeUnit_Line = 4,
    TextRangeUnit_Story = 5,
    TextRangeUnit_Screen = 6,
    TextRangeUnit_Section = 7,
    TextRangeUnit_Window = 8,
    TextRangeUnit_CharacterFormat = 9,
    TextRangeUnit_ParagraphFormat = 10,
    TextRangeUnit_Object = 11,
    TextRangeUnit_HardParagraph = 12,
    TextRangeUnit_Cluster = 13,
    TextRangeUnit_Bold = 14,
    TextRangeUnit_Italic = 15,
    TextRangeUnit_Underline = 16,
    TextRangeUnit_Strikethrough = 17,
    TextRangeUnit_ProtectedText = 18,
    TextRangeUnit_Link = 19,
    TextRangeUnit_SmallCaps = 20,
    TextRangeUnit_AllCaps = 21,
    TextRangeUnit_Hidden = 22,
    TextRangeUnit_Outline = 23,
    TextRangeUnit_Shadow = 24,
    TextRangeUnit_Imprint = 25,
    TextRangeUnit_Disabled = 26,
    TextRangeUnit_Revised = 27,
    TextRangeUnit_Subscript = 28,
    TextRangeUnit_Superscript = 29,
    TextRangeUnit_FontBound = 30,
    TextRangeUnit_LinkProtected = 31,
    TextRangeUnit_ContentLink = 32,
};

/*
 *
 * Struct Microsoft.UI.Text.TextScript
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CTextScript
{
    TextScript_Undefined = 0,
    TextScript_Ansi = 1,
    TextScript_EastEurope = 2,
    TextScript_Cyrillic = 3,
    TextScript_Greek = 4,
    TextScript_Turkish = 5,
    TextScript_Hebrew = 6,
    TextScript_Arabic = 7,
    TextScript_Baltic = 8,
    TextScript_Vietnamese = 9,
    TextScript_Default = 10,
    TextScript_Symbol = 11,
    TextScript_Thai = 12,
    TextScript_ShiftJis = 13,
    TextScript_GB2312 = 14,
    TextScript_Hangul = 15,
    TextScript_Big5 = 16,
    TextScript_PC437 = 17,
    TextScript_Oem = 18,
    TextScript_Mac = 19,
    TextScript_Armenian = 20,
    TextScript_Syriac = 21,
    TextScript_Thaana = 22,
    TextScript_Devanagari = 23,
    TextScript_Bengali = 24,
    TextScript_Gurmukhi = 25,
    TextScript_Gujarati = 26,
    TextScript_Oriya = 27,
    TextScript_Tamil = 28,
    TextScript_Telugu = 29,
    TextScript_Kannada = 30,
    TextScript_Malayalam = 31,
    TextScript_Sinhala = 32,
    TextScript_Lao = 33,
    TextScript_Tibetan = 34,
    TextScript_Myanmar = 35,
    TextScript_Georgian = 36,
    TextScript_Jamo = 37,
    TextScript_Ethiopic = 38,
    TextScript_Cherokee = 39,
    TextScript_Aboriginal = 40,
    TextScript_Ogham = 41,
    TextScript_Runic = 42,
    TextScript_Khmer = 43,
    TextScript_Mongolian = 44,
    TextScript_Braille = 45,
    TextScript_Yi = 46,
    TextScript_Limbu = 47,
    TextScript_TaiLe = 48,
    TextScript_NewTaiLue = 49,
    TextScript_SylotiNagri = 50,
    TextScript_Kharoshthi = 51,
    TextScript_Kayahli = 52,
    TextScript_UnicodeSymbol = 53,
    TextScript_Emoji = 54,
    TextScript_Glagolitic = 55,
    TextScript_Lisu = 56,
    TextScript_Vai = 57,
    TextScript_NKo = 58,
    TextScript_Osmanya = 59,
    TextScript_PhagsPa = 60,
    TextScript_Gothic = 61,
    TextScript_Deseret = 62,
    TextScript_Tifinagh = 63,
};

/*
 *
 * Struct Microsoft.UI.Text.TextSetOptions
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CTextSetOptions
{
    TextSetOptions_None = 0,
    TextSetOptions_UnicodeBidi = 0x1,
    TextSetOptions_Unlink = 0x8,
    TextSetOptions_Unhide = 0x10,
    TextSetOptions_CheckTextLimit = 0x20,
    TextSetOptions_FormatRtf = 0x2000,
    TextSetOptions_ApplyRtfDocumentDefaults = 0x4000,
};

/*
 *
 * Struct Microsoft.UI.Text.UnderlineType
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CUnderlineType
{
    UnderlineType_Undefined = 0,
    UnderlineType_None = 1,
    UnderlineType_Single = 2,
    UnderlineType_Words = 3,
    UnderlineType_Double = 4,
    UnderlineType_Dotted = 5,
    UnderlineType_Dash = 6,
    UnderlineType_DashDot = 7,
    UnderlineType_DashDotDot = 8,
    UnderlineType_Wave = 9,
    UnderlineType_Thick = 10,
    UnderlineType_Thin = 11,
    UnderlineType_DoubleWave = 12,
    UnderlineType_HeavyWave = 13,
    UnderlineType_LongDash = 14,
    UnderlineType_ThickDash = 15,
    UnderlineType_ThickDashDot = 16,
    UnderlineType_ThickDashDotDot = 17,
    UnderlineType_ThickDotted = 18,
    UnderlineType_ThickLongDash = 19,
};

/*
 *
 * Struct Microsoft.UI.Text.VerticalCharacterAlignment
 *
 */
enum __x_ABI_CMicrosoft_CUI_CText_CVerticalCharacterAlignment
{
    VerticalCharacterAlignment_Top = 0,
    VerticalCharacterAlignment_Baseline = 1,
    VerticalCharacterAlignment_Bottom = 2,
};

/*
 *
 * Interface Microsoft.UI.Text.IFontWeights
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Text.FontWeights
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_IFontWeights[] = L"Microsoft.UI.Text.IFontWeights";
typedef struct __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeights* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeights* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeights* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeights* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeights* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeights* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsVtbl;

interface __x_ABI_CMicrosoft_CUI_CText_CIFontWeights
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeights_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeights_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeights_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeights_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeights_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeights_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CIFontWeights;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CIFontWeights_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.IFontWeightsStatics
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Text.FontWeights
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_IFontWeightsStatics[] = L"Microsoft.UI.Text.IFontWeightsStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Black)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* get_Bold)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtraBlack)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtraBold)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtraLight)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* get_Light)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* get_Medium)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* get_Normal)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* get_SemiBold)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* get_SemiLight)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);
    HRESULT (STDMETHODCALLTYPE* get_Thin)(__x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics* This,
        struct __x_ABI_CWindows_CUI_CText_CFontWeight* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_Black(This, value) \
    ((This)->lpVtbl->get_Black(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_Bold(This, value) \
    ((This)->lpVtbl->get_Bold(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_ExtraBlack(This, value) \
    ((This)->lpVtbl->get_ExtraBlack(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_ExtraBold(This, value) \
    ((This)->lpVtbl->get_ExtraBold(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_ExtraLight(This, value) \
    ((This)->lpVtbl->get_ExtraLight(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_Light(This, value) \
    ((This)->lpVtbl->get_Light(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_Medium(This, value) \
    ((This)->lpVtbl->get_Medium(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_Normal(This, value) \
    ((This)->lpVtbl->get_Normal(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_SemiBold(This, value) \
    ((This)->lpVtbl->get_SemiBold(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_SemiLight(This, value) \
    ((This)->lpVtbl->get_SemiLight(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_get_Thin(This, value) \
    ((This)->lpVtbl->get_Thin(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CIFontWeightsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextCharacterFormat
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextCharacterFormat[] = L"Microsoft.UI.Text.ITextCharacterFormat";
typedef struct __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormatVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AllCaps)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_AllCaps)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_BackgroundColor)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* put_BackgroundColor)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        struct __x_ABI_CWindows_CUI_CColor value);
    HRESULT (STDMETHODCALLTYPE* get_Bold)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_Bold)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_FontStretch)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CWindows_CUI_CText_CFontStretch* value);
    HRESULT (STDMETHODCALLTYPE* put_FontStretch)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CWindows_CUI_CText_CFontStretch value);
    HRESULT (STDMETHODCALLTYPE* get_FontStyle)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CWindows_CUI_CText_CFontStyle* value);
    HRESULT (STDMETHODCALLTYPE* put_FontStyle)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CWindows_CUI_CText_CFontStyle value);
    HRESULT (STDMETHODCALLTYPE* get_ForegroundColor)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* put_ForegroundColor)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        struct __x_ABI_CWindows_CUI_CColor value);
    HRESULT (STDMETHODCALLTYPE* get_Hidden)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_Hidden)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_Italic)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_Italic)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_Kerning)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_Kerning)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_LanguageTag)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_LanguageTag)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_LinkType)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CLinkType* value);
    HRESULT (STDMETHODCALLTYPE* get_Name)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Name)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Outline)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_Outline)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_Position)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_Position)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_ProtectedText)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_ProtectedText)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_Size)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_SmallCaps)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_SmallCaps)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_Spacing)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_Spacing)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_Strikethrough)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_Strikethrough)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_Subscript)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_Subscript)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_Superscript)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_Superscript)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_TextScript)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextScript* value);
    HRESULT (STDMETHODCALLTYPE* put_TextScript)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextScript value);
    HRESULT (STDMETHODCALLTYPE* get_Underline)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CUnderlineType* value);
    HRESULT (STDMETHODCALLTYPE* put_Underline)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CUnderlineType value);
    HRESULT (STDMETHODCALLTYPE* get_Weight)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_Weight)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* SetClone)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* value);
    HRESULT (STDMETHODCALLTYPE* GetClone)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat** result);
    HRESULT (STDMETHODCALLTYPE* IsEqual)(__x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* format,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormatVtbl;

interface __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormatVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_AllCaps(This, value) \
    ((This)->lpVtbl->get_AllCaps(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_AllCaps(This, value) \
    ((This)->lpVtbl->put_AllCaps(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_BackgroundColor(This, value) \
    ((This)->lpVtbl->get_BackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_BackgroundColor(This, value) \
    ((This)->lpVtbl->put_BackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Bold(This, value) \
    ((This)->lpVtbl->get_Bold(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Bold(This, value) \
    ((This)->lpVtbl->put_Bold(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_FontStretch(This, value) \
    ((This)->lpVtbl->get_FontStretch(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_FontStretch(This, value) \
    ((This)->lpVtbl->put_FontStretch(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_FontStyle(This, value) \
    ((This)->lpVtbl->get_FontStyle(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_FontStyle(This, value) \
    ((This)->lpVtbl->put_FontStyle(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_ForegroundColor(This, value) \
    ((This)->lpVtbl->get_ForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_ForegroundColor(This, value) \
    ((This)->lpVtbl->put_ForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Hidden(This, value) \
    ((This)->lpVtbl->get_Hidden(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Hidden(This, value) \
    ((This)->lpVtbl->put_Hidden(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Italic(This, value) \
    ((This)->lpVtbl->get_Italic(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Italic(This, value) \
    ((This)->lpVtbl->put_Italic(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Kerning(This, value) \
    ((This)->lpVtbl->get_Kerning(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Kerning(This, value) \
    ((This)->lpVtbl->put_Kerning(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_LanguageTag(This, value) \
    ((This)->lpVtbl->get_LanguageTag(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_LanguageTag(This, value) \
    ((This)->lpVtbl->put_LanguageTag(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_LinkType(This, value) \
    ((This)->lpVtbl->get_LinkType(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Name(This, value) \
    ((This)->lpVtbl->get_Name(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Name(This, value) \
    ((This)->lpVtbl->put_Name(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Outline(This, value) \
    ((This)->lpVtbl->get_Outline(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Outline(This, value) \
    ((This)->lpVtbl->put_Outline(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Position(This, value) \
    ((This)->lpVtbl->get_Position(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Position(This, value) \
    ((This)->lpVtbl->put_Position(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_ProtectedText(This, value) \
    ((This)->lpVtbl->get_ProtectedText(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_ProtectedText(This, value) \
    ((This)->lpVtbl->put_ProtectedText(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Size(This, value) \
    ((This)->lpVtbl->get_Size(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Size(This, value) \
    ((This)->lpVtbl->put_Size(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_SmallCaps(This, value) \
    ((This)->lpVtbl->get_SmallCaps(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_SmallCaps(This, value) \
    ((This)->lpVtbl->put_SmallCaps(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Spacing(This, value) \
    ((This)->lpVtbl->get_Spacing(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Spacing(This, value) \
    ((This)->lpVtbl->put_Spacing(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Strikethrough(This, value) \
    ((This)->lpVtbl->get_Strikethrough(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Strikethrough(This, value) \
    ((This)->lpVtbl->put_Strikethrough(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Subscript(This, value) \
    ((This)->lpVtbl->get_Subscript(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Subscript(This, value) \
    ((This)->lpVtbl->put_Subscript(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Superscript(This, value) \
    ((This)->lpVtbl->get_Superscript(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Superscript(This, value) \
    ((This)->lpVtbl->put_Superscript(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_TextScript(This, value) \
    ((This)->lpVtbl->get_TextScript(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_TextScript(This, value) \
    ((This)->lpVtbl->put_TextScript(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Underline(This, value) \
    ((This)->lpVtbl->get_Underline(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Underline(This, value) \
    ((This)->lpVtbl->put_Underline(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_get_Weight(This, value) \
    ((This)->lpVtbl->get_Weight(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_put_Weight(This, value) \
    ((This)->lpVtbl->put_Weight(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_SetClone(This, value) \
    ((This)->lpVtbl->SetClone(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_GetClone(This, result) \
    ((This)->lpVtbl->GetClone(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_IsEqual(This, format, result) \
    ((This)->lpVtbl->IsEqual(This, format, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextConstantsStatics
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Text.TextConstants
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextConstantsStatics[] = L"Microsoft.UI.Text.ITextConstantsStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AutoColor)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MinUnitCount)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_MaxUnitCount)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_UndefinedColor)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_UndefinedFloatValue)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_UndefinedInt32Value)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_UndefinedFontStretch)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        enum __x_ABI_CWindows_CUI_CText_CFontStretch* value);
    HRESULT (STDMETHODCALLTYPE* get_UndefinedFontStyle)(__x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics* This,
        enum __x_ABI_CWindows_CUI_CText_CFontStyle* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_get_AutoColor(This, value) \
    ((This)->lpVtbl->get_AutoColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_get_MinUnitCount(This, value) \
    ((This)->lpVtbl->get_MinUnitCount(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_get_MaxUnitCount(This, value) \
    ((This)->lpVtbl->get_MaxUnitCount(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_get_UndefinedColor(This, value) \
    ((This)->lpVtbl->get_UndefinedColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_get_UndefinedFloatValue(This, value) \
    ((This)->lpVtbl->get_UndefinedFloatValue(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_get_UndefinedInt32Value(This, value) \
    ((This)->lpVtbl->get_UndefinedInt32Value(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_get_UndefinedFontStretch(This, value) \
    ((This)->lpVtbl->get_UndefinedFontStretch(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_get_UndefinedFontStyle(This, value) \
    ((This)->lpVtbl->get_UndefinedFontStyle(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextConstantsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextDocument
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Text.RichEditTextDocument
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextDocument_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextDocument_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextDocument[] = L"Microsoft.UI.Text.ITextDocument";
typedef struct __x_ABI_CMicrosoft_CUI_CText_CITextDocumentVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_CaretType)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CCaretType* value);
    HRESULT (STDMETHODCALLTYPE* put_CaretType)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CCaretType value);
    HRESULT (STDMETHODCALLTYPE* get_DefaultTabStop)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_DefaultTabStop)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_Selection)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextSelection** value);
    HRESULT (STDMETHODCALLTYPE* get_UndoLimit)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        UINT32* value);
    HRESULT (STDMETHODCALLTYPE* put_UndoLimit)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        UINT32 value);
    HRESULT (STDMETHODCALLTYPE* CanCopy)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* CanPaste)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* CanRedo)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* CanUndo)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* ApplyDisplayUpdates)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* BatchDisplayUpdates)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* BeginUndoGroup)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This);
    HRESULT (STDMETHODCALLTYPE* EndUndoGroup)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This);
    HRESULT (STDMETHODCALLTYPE* GetDefaultCharacterFormat)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat** result);
    HRESULT (STDMETHODCALLTYPE* GetDefaultParagraphFormat)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat** result);
    HRESULT (STDMETHODCALLTYPE* GetRange)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        INT32 startPosition,
        INT32 endPosition,
        __x_ABI_CMicrosoft_CUI_CText_CITextRange** result);
    HRESULT (STDMETHODCALLTYPE* GetRangeFromPoint)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        struct __x_ABI_CWindows_CFoundation_CPoint point,
        enum __x_ABI_CMicrosoft_CUI_CText_CPointOptions options,
        __x_ABI_CMicrosoft_CUI_CText_CITextRange** result);
    HRESULT (STDMETHODCALLTYPE* GetText)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextGetOptions options,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* LoadFromStream)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextSetOptions options,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream* value);
    HRESULT (STDMETHODCALLTYPE* Redo)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This);
    HRESULT (STDMETHODCALLTYPE* SaveToStream)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextGetOptions options,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream* value);
    HRESULT (STDMETHODCALLTYPE* SetDefaultCharacterFormat)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* value);
    HRESULT (STDMETHODCALLTYPE* SetDefaultParagraphFormat)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* value);
    HRESULT (STDMETHODCALLTYPE* SetText)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextSetOptions options,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* Undo)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This);
    HRESULT (STDMETHODCALLTYPE* get_AlignmentIncludesTrailingWhitespace)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_AlignmentIncludesTrailingWhitespace)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IgnoreTrailingCharacterSpacing)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IgnoreTrailingCharacterSpacing)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* ClearUndoRedoHistory)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CText_CITextDocumentVtbl;

interface __x_ABI_CMicrosoft_CUI_CText_CITextDocument
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CText_CITextDocumentVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_get_CaretType(This, value) \
    ((This)->lpVtbl->get_CaretType(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_put_CaretType(This, value) \
    ((This)->lpVtbl->put_CaretType(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_get_DefaultTabStop(This, value) \
    ((This)->lpVtbl->get_DefaultTabStop(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_put_DefaultTabStop(This, value) \
    ((This)->lpVtbl->put_DefaultTabStop(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_get_Selection(This, value) \
    ((This)->lpVtbl->get_Selection(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_get_UndoLimit(This, value) \
    ((This)->lpVtbl->get_UndoLimit(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_put_UndoLimit(This, value) \
    ((This)->lpVtbl->put_UndoLimit(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_CanCopy(This, result) \
    ((This)->lpVtbl->CanCopy(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_CanPaste(This, result) \
    ((This)->lpVtbl->CanPaste(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_CanRedo(This, result) \
    ((This)->lpVtbl->CanRedo(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_CanUndo(This, result) \
    ((This)->lpVtbl->CanUndo(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_ApplyDisplayUpdates(This, result) \
    ((This)->lpVtbl->ApplyDisplayUpdates(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_BatchDisplayUpdates(This, result) \
    ((This)->lpVtbl->BatchDisplayUpdates(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_BeginUndoGroup(This) \
    ((This)->lpVtbl->BeginUndoGroup(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_EndUndoGroup(This) \
    ((This)->lpVtbl->EndUndoGroup(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_GetDefaultCharacterFormat(This, result) \
    ((This)->lpVtbl->GetDefaultCharacterFormat(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_GetDefaultParagraphFormat(This, result) \
    ((This)->lpVtbl->GetDefaultParagraphFormat(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_GetRange(This, startPosition, endPosition, result) \
    ((This)->lpVtbl->GetRange(This, startPosition, endPosition, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_GetRangeFromPoint(This, point, options, result) \
    ((This)->lpVtbl->GetRangeFromPoint(This, point, options, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_GetText(This, options, value) \
    ((This)->lpVtbl->GetText(This, options, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_LoadFromStream(This, options, value) \
    ((This)->lpVtbl->LoadFromStream(This, options, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_Redo(This) \
    ((This)->lpVtbl->Redo(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_SaveToStream(This, options, value) \
    ((This)->lpVtbl->SaveToStream(This, options, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_SetDefaultCharacterFormat(This, value) \
    ((This)->lpVtbl->SetDefaultCharacterFormat(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_SetDefaultParagraphFormat(This, value) \
    ((This)->lpVtbl->SetDefaultParagraphFormat(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_SetText(This, options, value) \
    ((This)->lpVtbl->SetText(This, options, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_Undo(This) \
    ((This)->lpVtbl->Undo(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_get_AlignmentIncludesTrailingWhitespace(This, value) \
    ((This)->lpVtbl->get_AlignmentIncludesTrailingWhitespace(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_put_AlignmentIncludesTrailingWhitespace(This, value) \
    ((This)->lpVtbl->put_AlignmentIncludesTrailingWhitespace(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_get_IgnoreTrailingCharacterSpacing(This, value) \
    ((This)->lpVtbl->get_IgnoreTrailingCharacterSpacing(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_put_IgnoreTrailingCharacterSpacing(This, value) \
    ((This)->lpVtbl->put_IgnoreTrailingCharacterSpacing(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument_ClearUndoRedoHistory(This) \
    ((This)->lpVtbl->ClearUndoRedoHistory(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextDocument;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextDocument_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextDocument2
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Text.RichEditTextDocument
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextDocument2[] = L"Microsoft.UI.Text.ITextDocument2";
typedef struct __x_ABI_CMicrosoft_CUI_CText_CITextDocument2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetMathMode)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument2* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CRichEditMathMode* result);
    HRESULT (STDMETHODCALLTYPE* SetMathMode)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument2* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CRichEditMathMode mode);
    HRESULT (STDMETHODCALLTYPE* GetMathML)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument2* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* SetMathML)(__x_ABI_CMicrosoft_CUI_CText_CITextDocument2* This,
        HSTRING value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CText_CITextDocument2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CText_CITextDocument2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CText_CITextDocument2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2_GetMathMode(This, result) \
    ((This)->lpVtbl->GetMathMode(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2_SetMathMode(This, mode) \
    ((This)->lpVtbl->SetMathMode(This, mode))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2_GetMathML(This, value) \
    ((This)->lpVtbl->GetMathML(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextDocument2_SetMathML(This, value) \
    ((This)->lpVtbl->SetMathML(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextDocument2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextDocument2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.UI.Text.ITextParagraphFormat
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextParagraphFormat[] = L"Microsoft.UI.Text.ITextParagraphFormat";
typedef struct __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormatVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Alignment)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CParagraphAlignment* value);
    HRESULT (STDMETHODCALLTYPE* put_Alignment)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CParagraphAlignment value);
    HRESULT (STDMETHODCALLTYPE* get_FirstLineIndent)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_KeepTogether)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_KeepTogether)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_KeepWithNext)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_KeepWithNext)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_LeftIndent)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_LineSpacing)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_LineSpacingRule)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CLineSpacingRule* value);
    HRESULT (STDMETHODCALLTYPE* get_ListAlignment)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CMarkerAlignment* value);
    HRESULT (STDMETHODCALLTYPE* put_ListAlignment)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CMarkerAlignment value);
    HRESULT (STDMETHODCALLTYPE* get_ListLevelIndex)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_ListLevelIndex)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* get_ListStart)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_ListStart)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* get_ListStyle)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CMarkerStyle* value);
    HRESULT (STDMETHODCALLTYPE* put_ListStyle)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CMarkerStyle value);
    HRESULT (STDMETHODCALLTYPE* get_ListTab)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_ListTab)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_ListType)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CMarkerType* value);
    HRESULT (STDMETHODCALLTYPE* put_ListType)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CMarkerType value);
    HRESULT (STDMETHODCALLTYPE* get_NoLineNumber)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_NoLineNumber)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_PageBreakBefore)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_PageBreakBefore)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_RightIndent)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_RightIndent)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_RightToLeft)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_RightToLeft)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_Style)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CParagraphStyle* value);
    HRESULT (STDMETHODCALLTYPE* put_Style)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CParagraphStyle value);
    HRESULT (STDMETHODCALLTYPE* get_SpaceAfter)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_SpaceAfter)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_SpaceBefore)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_SpaceBefore)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_WidowControl)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect* value);
    HRESULT (STDMETHODCALLTYPE* put_WidowControl)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CFormatEffect value);
    HRESULT (STDMETHODCALLTYPE* get_TabCount)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* AddTab)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT position,
        enum __x_ABI_CMicrosoft_CUI_CText_CTabAlignment align,
        enum __x_ABI_CMicrosoft_CUI_CText_CTabLeader leader);
    HRESULT (STDMETHODCALLTYPE* ClearAllTabs)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This);
    HRESULT (STDMETHODCALLTYPE* DeleteTab)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT position);
    HRESULT (STDMETHODCALLTYPE* GetClone)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat** result);
    HRESULT (STDMETHODCALLTYPE* GetTab)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        INT32 index,
        FLOAT* position,
        enum __x_ABI_CMicrosoft_CUI_CText_CTabAlignment* align,
        enum __x_ABI_CMicrosoft_CUI_CText_CTabLeader* leader);
    HRESULT (STDMETHODCALLTYPE* IsEqual)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* format,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetClone)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* format);
    HRESULT (STDMETHODCALLTYPE* SetIndents)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        FLOAT start,
        FLOAT left,
        FLOAT right);
    HRESULT (STDMETHODCALLTYPE* SetLineSpacing)(__x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CLineSpacingRule rule,
        FLOAT spacing);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormatVtbl;

interface __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormatVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_Alignment(This, value) \
    ((This)->lpVtbl->get_Alignment(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_Alignment(This, value) \
    ((This)->lpVtbl->put_Alignment(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_FirstLineIndent(This, value) \
    ((This)->lpVtbl->get_FirstLineIndent(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_KeepTogether(This, value) \
    ((This)->lpVtbl->get_KeepTogether(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_KeepTogether(This, value) \
    ((This)->lpVtbl->put_KeepTogether(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_KeepWithNext(This, value) \
    ((This)->lpVtbl->get_KeepWithNext(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_KeepWithNext(This, value) \
    ((This)->lpVtbl->put_KeepWithNext(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_LeftIndent(This, value) \
    ((This)->lpVtbl->get_LeftIndent(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_LineSpacing(This, value) \
    ((This)->lpVtbl->get_LineSpacing(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_LineSpacingRule(This, value) \
    ((This)->lpVtbl->get_LineSpacingRule(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_ListAlignment(This, value) \
    ((This)->lpVtbl->get_ListAlignment(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_ListAlignment(This, value) \
    ((This)->lpVtbl->put_ListAlignment(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_ListLevelIndex(This, value) \
    ((This)->lpVtbl->get_ListLevelIndex(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_ListLevelIndex(This, value) \
    ((This)->lpVtbl->put_ListLevelIndex(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_ListStart(This, value) \
    ((This)->lpVtbl->get_ListStart(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_ListStart(This, value) \
    ((This)->lpVtbl->put_ListStart(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_ListStyle(This, value) \
    ((This)->lpVtbl->get_ListStyle(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_ListStyle(This, value) \
    ((This)->lpVtbl->put_ListStyle(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_ListTab(This, value) \
    ((This)->lpVtbl->get_ListTab(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_ListTab(This, value) \
    ((This)->lpVtbl->put_ListTab(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_ListType(This, value) \
    ((This)->lpVtbl->get_ListType(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_ListType(This, value) \
    ((This)->lpVtbl->put_ListType(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_NoLineNumber(This, value) \
    ((This)->lpVtbl->get_NoLineNumber(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_NoLineNumber(This, value) \
    ((This)->lpVtbl->put_NoLineNumber(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_PageBreakBefore(This, value) \
    ((This)->lpVtbl->get_PageBreakBefore(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_PageBreakBefore(This, value) \
    ((This)->lpVtbl->put_PageBreakBefore(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_RightIndent(This, value) \
    ((This)->lpVtbl->get_RightIndent(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_RightIndent(This, value) \
    ((This)->lpVtbl->put_RightIndent(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_RightToLeft(This, value) \
    ((This)->lpVtbl->get_RightToLeft(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_RightToLeft(This, value) \
    ((This)->lpVtbl->put_RightToLeft(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_Style(This, value) \
    ((This)->lpVtbl->get_Style(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_Style(This, value) \
    ((This)->lpVtbl->put_Style(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_SpaceAfter(This, value) \
    ((This)->lpVtbl->get_SpaceAfter(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_SpaceAfter(This, value) \
    ((This)->lpVtbl->put_SpaceAfter(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_SpaceBefore(This, value) \
    ((This)->lpVtbl->get_SpaceBefore(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_SpaceBefore(This, value) \
    ((This)->lpVtbl->put_SpaceBefore(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_WidowControl(This, value) \
    ((This)->lpVtbl->get_WidowControl(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_put_WidowControl(This, value) \
    ((This)->lpVtbl->put_WidowControl(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_get_TabCount(This, value) \
    ((This)->lpVtbl->get_TabCount(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_AddTab(This, position, align, leader) \
    ((This)->lpVtbl->AddTab(This, position, align, leader))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_ClearAllTabs(This) \
    ((This)->lpVtbl->ClearAllTabs(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_DeleteTab(This, position) \
    ((This)->lpVtbl->DeleteTab(This, position))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_GetClone(This, result) \
    ((This)->lpVtbl->GetClone(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_GetTab(This, index, position, align, leader) \
    ((This)->lpVtbl->GetTab(This, index, position, align, leader))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_IsEqual(This, format, result) \
    ((This)->lpVtbl->IsEqual(This, format, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_SetClone(This, format) \
    ((This)->lpVtbl->SetClone(This, format))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_SetIndents(This, start, left, right) \
    ((This)->lpVtbl->SetIndents(This, start, left, right))

#define __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_SetLineSpacing(This, rule, spacing) \
    ((This)->lpVtbl->SetLineSpacing(This, rule, spacing))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextRange
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextRange_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextRange_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextRange[] = L"Microsoft.UI.Text.ITextRange";
typedef struct __x_ABI_CMicrosoft_CUI_CText_CITextRangeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Character)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        WCHAR* value);
    HRESULT (STDMETHODCALLTYPE* put_Character)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        WCHAR value);
    HRESULT (STDMETHODCALLTYPE* get_CharacterFormat)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat** value);
    HRESULT (STDMETHODCALLTYPE* put_CharacterFormat)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextCharacterFormat* value);
    HRESULT (STDMETHODCALLTYPE* get_FormattedText)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextRange** value);
    HRESULT (STDMETHODCALLTYPE* put_FormattedText)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextRange* value);
    HRESULT (STDMETHODCALLTYPE* get_EndPosition)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_EndPosition)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* get_Gravity)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CRangeGravity* value);
    HRESULT (STDMETHODCALLTYPE* put_Gravity)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CRangeGravity value);
    HRESULT (STDMETHODCALLTYPE* get_Length)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_Link)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Link)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_ParagraphFormat)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat** value);
    HRESULT (STDMETHODCALLTYPE* put_ParagraphFormat)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextParagraphFormat* value);
    HRESULT (STDMETHODCALLTYPE* get_StartPosition)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_StartPosition)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* get_StoryLength)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_Text)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Text)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* CanPaste)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        INT32 format,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* ChangeCase)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CLetterCase value);
    HRESULT (STDMETHODCALLTYPE* Collapse)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* Copy)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This);
    HRESULT (STDMETHODCALLTYPE* Cut)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This);
    HRESULT (STDMETHODCALLTYPE* Delete)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32 count,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* EndOf)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        boolean extend,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* Expand)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* FindText)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        HSTRING value,
        INT32 scanLength,
        enum __x_ABI_CMicrosoft_CUI_CText_CFindOptions options,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* GetCharacterUtf32)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        UINT32* value,
        INT32 offset);
    HRESULT (STDMETHODCALLTYPE* GetClone)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextRange** result);
    HRESULT (STDMETHODCALLTYPE* GetIndex)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* GetPoint)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CHorizontalCharacterAlignment horizontalAlign,
        enum __x_ABI_CMicrosoft_CUI_CText_CVerticalCharacterAlignment verticalAlign,
        enum __x_ABI_CMicrosoft_CUI_CText_CPointOptions options,
        struct __x_ABI_CWindows_CFoundation_CPoint* point);
    HRESULT (STDMETHODCALLTYPE* GetRect)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CPointOptions options,
        struct __x_ABI_CWindows_CFoundation_CRect* rect,
        INT32* hit);
    HRESULT (STDMETHODCALLTYPE* GetText)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextGetOptions options,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* GetTextViaStream)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextGetOptions options,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream* value);
    HRESULT (STDMETHODCALLTYPE* InRange)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextRange* range,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* InsertImage)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        INT32 width,
        INT32 height,
        INT32 ascent,
        enum __x_ABI_CMicrosoft_CUI_CText_CVerticalCharacterAlignment verticalAlign,
        HSTRING alternateText,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream* value);
    HRESULT (STDMETHODCALLTYPE* InStory)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextRange* range,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsEqual)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        __x_ABI_CMicrosoft_CUI_CText_CITextRange* range,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Move)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32 count,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* MoveEnd)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32 count,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* MoveStart)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32 count,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* Paste)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        INT32 format);
    HRESULT (STDMETHODCALLTYPE* ScrollIntoView)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CPointOptions value);
    HRESULT (STDMETHODCALLTYPE* MatchSelection)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This);
    HRESULT (STDMETHODCALLTYPE* SetIndex)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32 index,
        boolean extend);
    HRESULT (STDMETHODCALLTYPE* SetPoint)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        struct __x_ABI_CWindows_CFoundation_CPoint point,
        enum __x_ABI_CMicrosoft_CUI_CText_CPointOptions options,
        boolean extend);
    HRESULT (STDMETHODCALLTYPE* SetRange)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        INT32 startPosition,
        INT32 endPosition);
    HRESULT (STDMETHODCALLTYPE* SetText)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextSetOptions options,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* SetTextViaStream)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextSetOptions options,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream* value);
    HRESULT (STDMETHODCALLTYPE* StartOf)(__x_ABI_CMicrosoft_CUI_CText_CITextRange* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        boolean extend,
        INT32* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CText_CITextRangeVtbl;

interface __x_ABI_CMicrosoft_CUI_CText_CITextRange
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CText_CITextRangeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_Character(This, value) \
    ((This)->lpVtbl->get_Character(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_put_Character(This, value) \
    ((This)->lpVtbl->put_Character(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_CharacterFormat(This, value) \
    ((This)->lpVtbl->get_CharacterFormat(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_put_CharacterFormat(This, value) \
    ((This)->lpVtbl->put_CharacterFormat(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_FormattedText(This, value) \
    ((This)->lpVtbl->get_FormattedText(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_put_FormattedText(This, value) \
    ((This)->lpVtbl->put_FormattedText(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_EndPosition(This, value) \
    ((This)->lpVtbl->get_EndPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_put_EndPosition(This, value) \
    ((This)->lpVtbl->put_EndPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_Gravity(This, value) \
    ((This)->lpVtbl->get_Gravity(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_put_Gravity(This, value) \
    ((This)->lpVtbl->put_Gravity(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_Length(This, value) \
    ((This)->lpVtbl->get_Length(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_Link(This, value) \
    ((This)->lpVtbl->get_Link(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_put_Link(This, value) \
    ((This)->lpVtbl->put_Link(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_ParagraphFormat(This, value) \
    ((This)->lpVtbl->get_ParagraphFormat(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_put_ParagraphFormat(This, value) \
    ((This)->lpVtbl->put_ParagraphFormat(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_StartPosition(This, value) \
    ((This)->lpVtbl->get_StartPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_put_StartPosition(This, value) \
    ((This)->lpVtbl->put_StartPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_StoryLength(This, value) \
    ((This)->lpVtbl->get_StoryLength(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_get_Text(This, value) \
    ((This)->lpVtbl->get_Text(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_put_Text(This, value) \
    ((This)->lpVtbl->put_Text(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_CanPaste(This, format, result) \
    ((This)->lpVtbl->CanPaste(This, format, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_ChangeCase(This, value) \
    ((This)->lpVtbl->ChangeCase(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_Collapse(This, value) \
    ((This)->lpVtbl->Collapse(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_Copy(This) \
    ((This)->lpVtbl->Copy(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_Cut(This) \
    ((This)->lpVtbl->Cut(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_Delete(This, unit, count, result) \
    ((This)->lpVtbl->Delete(This, unit, count, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_EndOf(This, unit, extend, result) \
    ((This)->lpVtbl->EndOf(This, unit, extend, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_Expand(This, unit, result) \
    ((This)->lpVtbl->Expand(This, unit, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_FindText(This, value, scanLength, options, result) \
    ((This)->lpVtbl->FindText(This, value, scanLength, options, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_GetCharacterUtf32(This, value, offset) \
    ((This)->lpVtbl->GetCharacterUtf32(This, value, offset))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_GetClone(This, result) \
    ((This)->lpVtbl->GetClone(This, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_GetIndex(This, unit, result) \
    ((This)->lpVtbl->GetIndex(This, unit, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_GetPoint(This, horizontalAlign, verticalAlign, options, point) \
    ((This)->lpVtbl->GetPoint(This, horizontalAlign, verticalAlign, options, point))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_GetRect(This, options, rect, hit) \
    ((This)->lpVtbl->GetRect(This, options, rect, hit))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_GetText(This, options, value) \
    ((This)->lpVtbl->GetText(This, options, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_GetTextViaStream(This, options, value) \
    ((This)->lpVtbl->GetTextViaStream(This, options, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_InRange(This, range, result) \
    ((This)->lpVtbl->InRange(This, range, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_InsertImage(This, width, height, ascent, verticalAlign, alternateText, value) \
    ((This)->lpVtbl->InsertImage(This, width, height, ascent, verticalAlign, alternateText, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_InStory(This, range, result) \
    ((This)->lpVtbl->InStory(This, range, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_IsEqual(This, range, result) \
    ((This)->lpVtbl->IsEqual(This, range, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_Move(This, unit, count, result) \
    ((This)->lpVtbl->Move(This, unit, count, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_MoveEnd(This, unit, count, result) \
    ((This)->lpVtbl->MoveEnd(This, unit, count, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_MoveStart(This, unit, count, result) \
    ((This)->lpVtbl->MoveStart(This, unit, count, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_Paste(This, format) \
    ((This)->lpVtbl->Paste(This, format))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_ScrollIntoView(This, value) \
    ((This)->lpVtbl->ScrollIntoView(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_MatchSelection(This) \
    ((This)->lpVtbl->MatchSelection(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_SetIndex(This, unit, index, extend) \
    ((This)->lpVtbl->SetIndex(This, unit, index, extend))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_SetPoint(This, point, options, extend) \
    ((This)->lpVtbl->SetPoint(This, point, options, extend))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_SetRange(This, startPosition, endPosition) \
    ((This)->lpVtbl->SetRange(This, startPosition, endPosition))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_SetText(This, options, value) \
    ((This)->lpVtbl->SetText(This, options, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_SetTextViaStream(This, options, value) \
    ((This)->lpVtbl->SetTextViaStream(This, options, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextRange_StartOf(This, unit, extend, result) \
    ((This)->lpVtbl->StartOf(This, unit, extend, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextRange;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextRange_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Text.ITextSelection
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Text.ITextRange
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CText_CITextSelection_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CText_CITextSelection_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Text_ITextSelection[] = L"Microsoft.UI.Text.ITextSelection";
typedef struct __x_ABI_CMicrosoft_CUI_CText_CITextSelectionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Options)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CSelectionOptions* value);
    HRESULT (STDMETHODCALLTYPE* put_Options)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CSelectionOptions value);
    HRESULT (STDMETHODCALLTYPE* get_Type)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CSelectionType* value);
    HRESULT (STDMETHODCALLTYPE* EndKey)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        boolean extend,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* HomeKey)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        boolean extend,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* MoveDown)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32 count,
        boolean extend,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* MoveLeft)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32 count,
        boolean extend,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* MoveRight)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32 count,
        boolean extend,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* MoveUp)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        enum __x_ABI_CMicrosoft_CUI_CText_CTextRangeUnit unit,
        INT32 count,
        boolean extend,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* TypeText)(__x_ABI_CMicrosoft_CUI_CText_CITextSelection* This,
        HSTRING value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CText_CITextSelectionVtbl;

interface __x_ABI_CMicrosoft_CUI_CText_CITextSelection
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CText_CITextSelectionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_get_Options(This, value) \
    ((This)->lpVtbl->get_Options(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_put_Options(This, value) \
    ((This)->lpVtbl->put_Options(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_get_Type(This, value) \
    ((This)->lpVtbl->get_Type(This, value))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_EndKey(This, unit, extend, result) \
    ((This)->lpVtbl->EndKey(This, unit, extend, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_HomeKey(This, unit, extend, result) \
    ((This)->lpVtbl->HomeKey(This, unit, extend, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_MoveDown(This, unit, count, extend, result) \
    ((This)->lpVtbl->MoveDown(This, unit, count, extend, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_MoveLeft(This, unit, count, extend, result) \
    ((This)->lpVtbl->MoveLeft(This, unit, count, extend, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_MoveRight(This, unit, count, extend, result) \
    ((This)->lpVtbl->MoveRight(This, unit, count, extend, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_MoveUp(This, unit, count, extend, result) \
    ((This)->lpVtbl->MoveUp(This, unit, count, extend, result))

#define __x_ABI_CMicrosoft_CUI_CText_CITextSelection_TypeText(This, value) \
    ((This)->lpVtbl->TypeText(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CText_CITextSelection;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CText_CITextSelection_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Text.FontWeights
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Text.IFontWeightsStatics interface starting with version 1.0 of the Microsoft.UI.Text.TextApiContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Text.IFontWeights ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Text_FontWeights_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Text_FontWeights_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Text_FontWeights[] = L"Microsoft.UI.Text.FontWeights";
#endif
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Text.RichEditTextDocument
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Text.ITextDocument ** Default Interface **
 *    Microsoft.UI.Text.ITextDocument2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Text_RichEditTextDocument_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Text_RichEditTextDocument_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Text_RichEditTextDocument[] = L"Microsoft.UI.Text.RichEditTextDocument";
#endif
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Text.RichEditTextRange
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Text.ITextRange ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Text_RichEditTextRange_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Text_RichEditTextRange_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Text_RichEditTextRange[] = L"Microsoft.UI.Text.RichEditTextRange";
#endif
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Text.TextConstants
 *
 * Introduced to Microsoft.UI.Text.TextApiContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Text.ITextConstantsStatics interface starting with version 1.0 of the Microsoft.UI.Text.TextApiContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Text_TextConstants_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Text_TextConstants_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Text_TextConstants[] = L"Microsoft.UI.Text.TextConstants";
#endif
#endif // MICROSOFT_UI_TEXT_TEXTAPICONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Etext_p_h__

#endif // __microsoft2Eui2Etext_h__
