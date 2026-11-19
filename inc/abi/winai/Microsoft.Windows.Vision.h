
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
#ifndef __microsoft2Ewindows2Evision_h__
#define __microsoft2Ewindows2Evision_h__
#ifndef __microsoft2Ewindows2Evision_p_h__
#define __microsoft2Ewindows2Evision_p_h__


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
#if !defined(MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
// Parameterized interface forward declarations (C++)

// Collection interface definitions
/*
 *
 * Struct Microsoft.Windows.Vision.ScreenRegionLabel
 *
 * Introduced to Microsoft.Windows.Vision.ScreenRegionDetectionContract in version 1.0
 *
 * Type is for evaluation purposes and is subject to change or removal in future updates.
 *
 */
#if defined(ENABLE_WINRT_EXPERIMENTAL_TYPES)
#if MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Vision {
                enum ScreenRegionLabel : int
                {
                    ScreenRegionLabel_Text = 0,
                    ScreenRegionLabel_Image = 1,
                    ScreenRegionLabel_Table = 2,
                    ScreenRegionLabel_Container = 3,
                    ScreenRegionLabel_Menu = 4,
                    ScreenRegionLabel_ToolBar = 5,
                    ScreenRegionLabel_AddressBar = 6,
                    ScreenRegionLabel_Toolpane = 7,
                    ScreenRegionLabel_TabBar = 8,
                    ScreenRegionLabel_TitleBar = 9,
                };
            } /* Vision */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION >= 0x10000
#endif // defined(ENABLE_WINRT_EXPERIMENTAL_TYPES)

/*
 *
 * Struct Microsoft.Windows.Vision.ScreenRegionBoundingBox
 *
 * Introduced to Microsoft.Windows.Vision.ScreenRegionDetectionContract in version 1.0
 *
 * Type is for evaluation purposes and is subject to change or removal in future updates.
 *
 */
#if defined(ENABLE_WINRT_EXPERIMENTAL_TYPES)
#if MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Vision {
                struct ScreenRegionBoundingBox
                {
                    UINT32 Left;
                    UINT32 Top;
                    UINT32 Right;
                    UINT32 Bottom;
                };
            } /* Vision */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION >= 0x10000
#endif // defined(ENABLE_WINRT_EXPERIMENTAL_TYPES)

#else // !defined(__cplusplus)
/* Forward Declarations */
// Parameterized interface forward declarations (C)

// Collection interface definitions

/*
 *
 * Struct Microsoft.Windows.Vision.ScreenRegionLabel
 *
 * Introduced to Microsoft.Windows.Vision.ScreenRegionDetectionContract in version 1.0
 *
 * Type is for evaluation purposes and is subject to change or removal in future updates.
 *
 */
#if defined(ENABLE_WINRT_EXPERIMENTAL_TYPES)
#if MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CVision_CScreenRegionLabel
{
    ScreenRegionLabel_Text = 0,
    ScreenRegionLabel_Image = 1,
    ScreenRegionLabel_Table = 2,
    ScreenRegionLabel_Container = 3,
    ScreenRegionLabel_Menu = 4,
    ScreenRegionLabel_ToolBar = 5,
    ScreenRegionLabel_AddressBar = 6,
    ScreenRegionLabel_Toolpane = 7,
    ScreenRegionLabel_TabBar = 8,
    ScreenRegionLabel_TitleBar = 9,
};
#endif // MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION >= 0x10000
#endif // defined(ENABLE_WINRT_EXPERIMENTAL_TYPES)

/*
 *
 * Struct Microsoft.Windows.Vision.ScreenRegionBoundingBox
 *
 * Introduced to Microsoft.Windows.Vision.ScreenRegionDetectionContract in version 1.0
 *
 * Type is for evaluation purposes and is subject to change or removal in future updates.
 *
 */
#if defined(ENABLE_WINRT_EXPERIMENTAL_TYPES)
#if MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CWindows_CVision_CScreenRegionBoundingBox
{
    UINT32 Left;
    UINT32 Top;
    UINT32 Right;
    UINT32 Bottom;
};
#endif // MICROSOFT_WINDOWS_VISION_SCREENREGIONDETECTIONCONTRACT_VERSION >= 0x10000
#endif // defined(ENABLE_WINRT_EXPERIMENTAL_TYPES)

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Evision_p_h__

#endif // __microsoft2Ewindows2Evision_h__
