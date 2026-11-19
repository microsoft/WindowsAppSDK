
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
#ifndef __microsoft2Ewindows2Eai2Evideo_h__
#define __microsoft2Ewindows2Eai2Evideo_h__
#ifndef __microsoft2Ewindows2Eai2Evideo_p_h__
#define __microsoft2Ewindows2Eai2Evideo_p_h__


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
#define MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION 0x40000
#endif // defined(MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION)

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
#include "Microsoft.Graphics.Imaging.h"
#include "Microsoft.Windows.AI.h"
#include "Windows.Graphics.h"
#include "Windows.Graphics.DirectX.Direct3D11.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    interface IVideoScaler;
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler ABI::Microsoft::Windows::AI::Video::IVideoScaler

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    interface IVideoScalerOptions;
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions ABI::Microsoft::Windows::AI::Video::IVideoScalerOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    interface IVideoScalerResult;
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult ABI::Microsoft::Windows::AI::Video::IVideoScalerResult

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    interface IVideoScalerStatics;
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics ABI::Microsoft::Windows::AI::Video::IVideoScalerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    class VideoScaler;
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */


#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("8ac5952e-f02d-5708-9659-f17859e5e31f"))
IAsyncOperation<ABI::Microsoft::Windows::AI::Video::VideoScaler*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Video::VideoScaler*, ABI::Microsoft::Windows::AI::Video::IVideoScaler*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.AI.Video.VideoScaler>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Windows::AI::Video::VideoScaler*> __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_USE */



#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("5c56f6ea-69f3-58ce-96b2-db6eb973d1e3"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Video::VideoScaler*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AI::Video::VideoScaler*, ABI::Microsoft::Windows::AI::Video::IVideoScaler*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.AI.Video.VideoScaler>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::AI::Video::VideoScaler*> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_USE */


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

#ifndef ____x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface_FWD_DEFINED__
#define ____x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Graphics {
            namespace DirectX {
                namespace Direct3D11 {
                    interface IDirect3DSurface;
                } /* Direct3D11 */
            } /* DirectX */
        } /* Graphics */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface ABI::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface

#endif // ____x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    typedef enum VideoScalerStatus : int VideoScalerStatus;
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    class VideoScalerOptions;
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    class VideoScalerResult;
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.AI.Video.VideoScalerStatus
 *
 */
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    enum VideoScalerStatus : int
                    {
                        VideoScalerStatus_Success = 0,
                        VideoScalerStatus_InvalidInputFormat = 1,
                        VideoScalerStatus_InvalidOutputFormat = 2,
                        VideoScalerStatus_InvalidPlaneSize = 3,
                        VideoScalerStatus_InvalidFrameData = 4,
                        VideoScalerStatus_ModelNotAvailable = 5,
                        VideoScalerStatus_OutOfMemory = 6,
                        VideoScalerStatus_Failure = 7,
                    };
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Interface Microsoft.Windows.AI.Video.IVideoScaler
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Video.VideoScaler
 *
 */
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Video_IVideoScaler[] = L"Microsoft.Windows.AI.Video.IVideoScaler";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    MIDL_INTERFACE("e5abe769-63cc-5498-a5e1-74205106bdfd")
                    IVideoScaler : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Scale(
                            ABI::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface* input,
                            ABI::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface* output,
                            ABI::Microsoft::Windows::AI::Video::IVideoScalerOptions* options,
                            ABI::Microsoft::Windows::AI::Video::IVideoScalerResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ScaleImageBuffer(
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer* input,
                            ABI::Microsoft::Graphics::Imaging::IImageBuffer* output,
                            ABI::Microsoft::Windows::AI::Video::IVideoScalerOptions* options,
                            ABI::Microsoft::Windows::AI::Video::IVideoScalerResult** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IVideoScaler = _uuidof(IVideoScaler);
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_INTERFACE_DEFINED__) */

/*
 *
 * Interface Microsoft.Windows.AI.Video.IVideoScalerOptions
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Video.VideoScalerOptions
 *
 */
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Video_IVideoScalerOptions[] = L"Microsoft.Windows.AI.Video.IVideoScalerOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    MIDL_INTERFACE("3a1427f8-ddad-519e-a028-7322bde4c4d2")
                    IVideoScalerOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_RegionsOfInterest(
                            __FIVector_1_Windows__CGraphics__CRectInt32** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IVideoScalerOptions = _uuidof(IVideoScalerOptions);
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_INTERFACE_DEFINED__) */

/*
 *
 * Interface Microsoft.Windows.AI.Video.IVideoScalerResult
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Video.VideoScalerResult
 *
 */
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Video_IVideoScalerResult[] = L"Microsoft.Windows.AI.Video.IVideoScalerResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    MIDL_INTERFACE("24a228fb-0af2-5a00-bb6d-52946d9460da")
                    IVideoScalerResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            ABI::Microsoft::Windows::AI::Video::VideoScalerStatus* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IVideoScalerResult = _uuidof(IVideoScalerResult);
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_INTERFACE_DEFINED__) */

/*
 *
 * Interface Microsoft.Windows.AI.Video.IVideoScalerStatics
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Video.VideoScaler
 *
 */
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Video_IVideoScalerStatics[] = L"Microsoft.Windows.AI.Video.IVideoScalerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Video {
                    MIDL_INTERFACE("311dd8bb-b7ac-55a7-a3d3-1a6c84430f84")
                    IVideoScalerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetReadyState(
                            ABI::Microsoft::Windows::AI::AIFeatureReadyState* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsureReadyAsync(
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateAsync(
                            __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IVideoScalerStatics = _uuidof(IVideoScalerStatics);
                } /* Video */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_INTERFACE_DEFINED__) */

/*
 *
 * Class Microsoft.Windows.AI.Video.VideoScaler
 *
 * RuntimeClass contains static methods.
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Video.IVideoScaler ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScaler_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScaler_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Video_VideoScaler[] = L"Microsoft.Windows.AI.Video.VideoScaler";
#endif

/*
 *
 * Class Microsoft.Windows.AI.Video.VideoScalerOptions
 *
 * RuntimeClass can be activated.
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Video.IVideoScalerOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScalerOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScalerOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Video_VideoScalerOptions[] = L"Microsoft.Windows.AI.Video.VideoScalerOptions";
#endif

/*
 *
 * Class Microsoft.Windows.AI.Video.VideoScalerResult
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Video.IVideoScalerResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScalerResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScalerResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Video_VideoScalerResult[] = L"Microsoft.Windows.AI.Video.VideoScalerResult";
#endif

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler;

#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScalerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScalerVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScalerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_INTERFACE_DEFINED__

#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScalerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScalerVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScalerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler_INTERFACE_DEFINED__

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

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface_FWD_DEFINED__
#define ____x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface __x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface;

#endif // ____x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CVideoScalerStatus __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CVideoScalerStatus;

/*
 *
 * Struct Microsoft.Windows.AI.Video.VideoScalerStatus
 *
 */
enum __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CVideoScalerStatus
{
    VideoScalerStatus_Success = 0,
    VideoScalerStatus_InvalidInputFormat = 1,
    VideoScalerStatus_InvalidOutputFormat = 2,
    VideoScalerStatus_InvalidPlaneSize = 3,
    VideoScalerStatus_InvalidFrameData = 4,
    VideoScalerStatus_ModelNotAvailable = 5,
    VideoScalerStatus_OutOfMemory = 6,
    VideoScalerStatus_Failure = 7,
};

/*
 *
 * Interface Microsoft.Windows.AI.Video.IVideoScaler
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Video.VideoScaler
 *
 */
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Video_IVideoScaler[] = L"Microsoft.Windows.AI.Video.IVideoScaler";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Scale)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler* This,
        __x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface* input,
        __x_ABI_CWindows_CGraphics_CDirectX_CDirect3D11_CIDirect3DSurface* output,
        __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions* options,
        __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult** result);
    HRESULT (STDMETHODCALLTYPE* ScaleImageBuffer)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler* This,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* input,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* output,
        __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions* options,
        __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_Scale(This, input, output, options, result) \
    ((This)->lpVtbl->Scale(This, input, output, options, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_ScaleImageBuffer(This, input, output, options, result) \
    ((This)->lpVtbl->ScaleImageBuffer(This, input, output, options, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScaler_INTERFACE_DEFINED__) */

/*
 *
 * Interface Microsoft.Windows.AI.Video.IVideoScalerOptions
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Video.VideoScalerOptions
 *
 */
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Video_IVideoScalerOptions[] = L"Microsoft.Windows.AI.Video.IVideoScalerOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RegionsOfInterest)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions* This,
        __FIVector_1_Windows__CGraphics__CRectInt32** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_get_RegionsOfInterest(This, value) \
    ((This)->lpVtbl->get_RegionsOfInterest(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerOptions_INTERFACE_DEFINED__) */

/*
 *
 * Interface Microsoft.Windows.AI.Video.IVideoScalerResult
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Video.VideoScalerResult
 *
 */
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Video_IVideoScalerResult[] = L"Microsoft.Windows.AI.Video.IVideoScalerResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CVideoScalerStatus* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerResult_INTERFACE_DEFINED__) */

/*
 *
 * Interface Microsoft.Windows.AI.Video.IVideoScalerStatics
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Video.VideoScaler
 *
 */
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Video_IVideoScalerStatics[] = L"Microsoft.Windows.AI.Video.IVideoScalerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetReadyState)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState* result);
    HRESULT (STDMETHODCALLTYPE* EnsureReadyAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CAI__CAIFeatureReadyResult_double** operation);
    HRESULT (STDMETHODCALLTYPE* CreateAsync)(__x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAI__CVideo__CVideoScaler** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_GetReadyState(This, result) \
    ((This)->lpVtbl->GetReadyState(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_EnsureReadyAsync(This, operation) \
    ((This)->lpVtbl->EnsureReadyAsync(This, operation))

#define __x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_CreateAsync(This, operation) \
    ((This)->lpVtbl->CreateAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CVideo_CIVideoScalerStatics_INTERFACE_DEFINED__) */

/*
 *
 * Class Microsoft.Windows.AI.Video.VideoScaler
 *
 * RuntimeClass contains static methods.
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Video.IVideoScaler ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScaler_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScaler_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Video_VideoScaler[] = L"Microsoft.Windows.AI.Video.VideoScaler";
#endif

/*
 *
 * Class Microsoft.Windows.AI.Video.VideoScalerOptions
 *
 * RuntimeClass can be activated.
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Video.IVideoScalerOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScalerOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScalerOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Video_VideoScalerOptions[] = L"Microsoft.Windows.AI.Video.VideoScalerOptions";
#endif

/*
 *
 * Class Microsoft.Windows.AI.Video.VideoScalerResult
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Video.IVideoScalerResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScalerResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Video_VideoScalerResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Video_VideoScalerResult[] = L"Microsoft.Windows.AI.Video.VideoScalerResult";
#endif

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eai2Evideo_p_h__

#endif // __microsoft2Ewindows2Eai2Evideo_h__
