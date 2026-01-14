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
#ifndef __microsoft2Egraphics2Eimaging_h__
#define __microsoft2Egraphics2Eimaging_h__
#ifndef __microsoft2Egraphics2Eimaging_p_h__
#define __microsoft2Egraphics2Eimaging_p_h__


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
#include "Windows.Graphics.Imaging.h"
#include "Windows.Storage.Streams.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
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

#ifndef ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Imaging {
                interface IImageBufferStatics;
            } /* Imaging */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics ABI::Microsoft::Graphics::Imaging::IImageBufferStatics

#endif // ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
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

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIBuffer_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIBuffer_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Storage {
            namespace Streams {
                interface IBuffer;
            } /* Streams */
        } /* Storage */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CStorage_CStreams_CIBuffer ABI::Windows::Storage::Streams::IBuffer

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIBuffer_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Imaging {
                typedef enum ImageBufferPixelFormat : int ImageBufferPixelFormat;
            } /* Imaging */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Imaging {
                class ImageBuffer;
            } /* Imaging */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Graphics.Imaging.ImageBufferPixelFormat
 *
 * Introduced to Microsoft.Graphics.Imaging.ImageBufferContract in version 1.0
 *
 */
#if MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Imaging {
                enum ImageBufferPixelFormat : int
                {
                    ImageBufferPixelFormat_Rgb8 = 137224,
                    ImageBufferPixelFormat_Rgba8 = 30,
                    ImageBufferPixelFormat_Argb8 = 2498570,
                    ImageBufferPixelFormat_Bgra8 = 87,
                    ImageBufferPixelFormat_Gray8 = 62,
                };
            } /* Imaging */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Graphics.Imaging.IImageBuffer
 *
 * Introduced to Microsoft.Graphics.Imaging.ImageBufferContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Graphics.Imaging.ImageBuffer
 *
 */
#if MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Graphics_Imaging_IImageBuffer[] = L"Microsoft.Graphics.Imaging.IImageBuffer";
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Imaging {
                MIDL_INTERFACE("3baabd0b-1854-51f1-bd2a-74c87858f461")
                IImageBuffer : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Buffer(
                        ABI::Windows::Storage::Streams::IBuffer** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_PixelFormat(
                        ABI::Microsoft::Graphics::Imaging::ImageBufferPixelFormat* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_PixelHeight(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_PixelWidth(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_RowStride(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CopyToByteArray(
                        UINT32 valuesLength,
                        BYTE* values
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CopyToSoftwareBitmap(
                        ABI::Windows::Graphics::Imaging::ISoftwareBitmap** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IImageBuffer = _uuidof(IImageBuffer);
            } /* Imaging */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer;
#endif /* !defined(____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Graphics.Imaging.IImageBufferStatics
 *
 * Introduced to Microsoft.Graphics.Imaging.ImageBufferContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Graphics.Imaging.ImageBuffer
 *
 */
#if MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Graphics_Imaging_IImageBufferStatics[] = L"Microsoft.Graphics.Imaging.IImageBufferStatics";
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Imaging {
                MIDL_INTERFACE("35b17bd3-f346-529f-8c0f-3bf96c56eb13")
                IImageBufferStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateForBuffer(
                        ABI::Windows::Storage::Streams::IBuffer* buffer,
                        ABI::Microsoft::Graphics::Imaging::ImageBufferPixelFormat pixelFormat,
                        INT32 width,
                        INT32 height,
                        INT32 rowStride,
                        ABI::Microsoft::Graphics::Imaging::IImageBuffer** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateForSoftwareBitmap(
                        ABI::Windows::Graphics::Imaging::ISoftwareBitmap* softwareBitmap,
                        ABI::Microsoft::Graphics::Imaging::IImageBuffer** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IImageBufferStatics = _uuidof(IImageBufferStatics);
            } /* Imaging */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Graphics.Imaging.ImageBuffer
 *
 * Introduced to Microsoft.Graphics.Imaging.ImageBufferContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Graphics.Imaging.IImageBufferStatics interface starting with version 1.0 of the Microsoft.Graphics.Imaging.ImageBufferContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Graphics.Imaging.IImageBuffer ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Graphics_Imaging_ImageBuffer_DEFINED
#define RUNTIMECLASS_Microsoft_Graphics_Imaging_ImageBuffer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Graphics_Imaging_ImageBuffer[] = L"Microsoft.Graphics.Imaging.ImageBuffer";
#endif
#endif // MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer;

#endif // ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics;

#endif // ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
#define ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap;

#endif // ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIBuffer_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIBuffer_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CStorage_CStreams_CIBuffer __x_ABI_CWindows_CStorage_CStreams_CIBuffer;

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIBuffer_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CGraphics_CImaging_CImageBufferPixelFormat __x_ABI_CMicrosoft_CGraphics_CImaging_CImageBufferPixelFormat;

/*
 *
 * Struct Microsoft.Graphics.Imaging.ImageBufferPixelFormat
 *
 * Introduced to Microsoft.Graphics.Imaging.ImageBufferContract in version 1.0
 *
 */
#if MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CGraphics_CImaging_CImageBufferPixelFormat
{
    ImageBufferPixelFormat_Rgb8 = 137224,
    ImageBufferPixelFormat_Rgba8 = 30,
    ImageBufferPixelFormat_Argb8 = 2498570,
    ImageBufferPixelFormat_Bgra8 = 87,
    ImageBufferPixelFormat_Gray8 = 62,
};
#endif // MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Graphics.Imaging.IImageBuffer
 *
 * Introduced to Microsoft.Graphics.Imaging.ImageBufferContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Graphics.Imaging.ImageBuffer
 *
 */
#if MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Graphics_Imaging_IImageBuffer[] = L"Microsoft.Graphics.Imaging.IImageBuffer";
typedef struct __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Buffer)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        __x_ABI_CWindows_CStorage_CStreams_CIBuffer** value);
    HRESULT (STDMETHODCALLTYPE* get_PixelFormat)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        enum __x_ABI_CMicrosoft_CGraphics_CImaging_CImageBufferPixelFormat* value);
    HRESULT (STDMETHODCALLTYPE* get_PixelHeight)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_PixelWidth)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_RowStride)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* CopyToByteArray)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        UINT32 valuesLength,
        BYTE* values);
    HRESULT (STDMETHODCALLTYPE* CopyToSoftwareBitmap)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer* This,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferVtbl;

interface __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_get_Buffer(This, value) \
    ((This)->lpVtbl->get_Buffer(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_get_PixelFormat(This, value) \
    ((This)->lpVtbl->get_PixelFormat(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_get_PixelHeight(This, value) \
    ((This)->lpVtbl->get_PixelHeight(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_get_PixelWidth(This, value) \
    ((This)->lpVtbl->get_PixelWidth(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_get_RowStride(This, value) \
    ((This)->lpVtbl->get_RowStride(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_CopyToByteArray(This, valuesLength, values) \
    ((This)->lpVtbl->CopyToByteArray(This, valuesLength, values))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_CopyToSoftwareBitmap(This, result) \
    ((This)->lpVtbl->CopyToSoftwareBitmap(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer;
#endif /* !defined(____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Graphics.Imaging.IImageBufferStatics
 *
 * Introduced to Microsoft.Graphics.Imaging.ImageBufferContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Graphics.Imaging.ImageBuffer
 *
 */
#if MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Graphics_Imaging_IImageBufferStatics[] = L"Microsoft.Graphics.Imaging.IImageBufferStatics";
typedef struct __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateForBuffer)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics* This,
        __x_ABI_CWindows_CStorage_CStreams_CIBuffer* buffer,
        enum __x_ABI_CMicrosoft_CGraphics_CImaging_CImageBufferPixelFormat pixelFormat,
        INT32 width,
        INT32 height,
        INT32 rowStride,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer** result);
    HRESULT (STDMETHODCALLTYPE* CreateForSoftwareBitmap)(__x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics* This,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* softwareBitmap,
        __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBuffer** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStaticsVtbl;

interface __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_CreateForBuffer(This, buffer, pixelFormat, width, height, rowStride, result) \
    ((This)->lpVtbl->CreateForBuffer(This, buffer, pixelFormat, width, height, rowStride, result))

#define __x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_CreateForSoftwareBitmap(This, softwareBitmap, result) \
    ((This)->lpVtbl->CreateForSoftwareBitmap(This, softwareBitmap, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CGraphics_CImaging_CIImageBufferStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Graphics.Imaging.ImageBuffer
 *
 * Introduced to Microsoft.Graphics.Imaging.ImageBufferContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Graphics.Imaging.IImageBufferStatics interface starting with version 1.0 of the Microsoft.Graphics.Imaging.ImageBufferContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Graphics.Imaging.IImageBuffer ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Graphics_Imaging_ImageBuffer_DEFINED
#define RUNTIMECLASS_Microsoft_Graphics_Imaging_ImageBuffer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Graphics_Imaging_ImageBuffer[] = L"Microsoft.Graphics.Imaging.ImageBuffer";
#endif
#endif // MICROSOFT_GRAPHICS_IMAGING_IMAGEBUFFERCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Egraphics2Eimaging_p_h__

#endif // __microsoft2Egraphics2Eimaging_h__
