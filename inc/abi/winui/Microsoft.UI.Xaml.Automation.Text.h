
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
#ifndef __microsoft2Eui2Examl2Eautomation2Etext_h__
#define __microsoft2Eui2Examl2Eautomation2Etext_h__
#ifndef __microsoft2Eui2Examl2Eautomation2Etext_p_h__
#define __microsoft2Eui2Examl2Eautomation2Etext_p_h__


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

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Microsoft.UI.Xaml.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
// Parameterized interface forward declarations (C++)

// Collection interface definitions
/*
 *
 * Struct Microsoft.UI.Xaml.Automation.Text.TextPatternRangeEndpoint
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Text {
                        enum TextPatternRangeEndpoint : int
                        {
                            TextPatternRangeEndpoint_Start = 0,
                            TextPatternRangeEndpoint_End = 1,
                        };
                    } /* Text */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Automation.Text.TextUnit
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Text {
                        enum TextUnit : int
                        {
                            TextUnit_Character = 0,
                            TextUnit_Format = 1,
                            TextUnit_Word = 2,
                            TextUnit_Line = 3,
                            TextUnit_Paragraph = 4,
                            TextUnit_Page = 5,
                            TextUnit_Document = 6,
                        };
                    } /* Text */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
// Parameterized interface forward declarations (C)

// Collection interface definitions

/*
 *
 * Struct Microsoft.UI.Xaml.Automation.Text.TextPatternRangeEndpoint
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextPatternRangeEndpoint
{
    TextPatternRangeEndpoint_Start = 0,
    TextPatternRangeEndpoint_End = 1,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Automation.Text.TextUnit
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextUnit
{
    TextUnit_Character = 0,
    TextUnit_Format = 1,
    TextUnit_Word = 2,
    TextUnit_Line = 3,
    TextUnit_Paragraph = 4,
    TextUnit_Page = 5,
    TextUnit_Document = 6,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Eautomation2Etext_p_h__

#endif // __microsoft2Eui2Examl2Eautomation2Etext_h__
