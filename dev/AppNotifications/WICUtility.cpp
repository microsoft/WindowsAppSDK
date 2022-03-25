
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "WICUtility.h"
#include <cwctype>
#include <winrt/Windows.Foundation.h>
#include <winrt/base.h>
#include <externs.h>

#include <ShObjIdl_core.h>
#include <wincodec.h>
#include <Ocidl.h>
#include <windows.h>

typedef enum
{
    BMPV_1,
    BMPV_5,
} BITMAP_VERSION;

winrt::com_ptr<IWICBitmapSource> ConvertWICBitmapPixelFormat(
    winrt::com_ptr<IWICImagingFactory> const& pWICImagingFactory,
    winrt::com_ptr<IWICBitmapSource> const& pWICBitmapSource,
    WICPixelFormatGUID guidPixelFormatSource,
    WICBitmapDitherType bitmapDitherType)
{
    winrt::com_ptr<IWICFormatConverter> spWICFormatConverter;

    THROW_IF_FAILED(pWICImagingFactory->CreateFormatConverter(spWICFormatConverter.put()));

    THROW_IF_FAILED(spWICFormatConverter->Initialize(pWICBitmapSource.get(), guidPixelFormatSource, bitmapDitherType, nullptr, 0.f, WICBitmapPaletteTypeCustom));

    // Store the converted bitmap as ppToRenderBitmapSource
    winrt::com_ptr<IWICBitmapSource> ppWICBitmapSource;
    THROW_IF_FAILED(spWICFormatConverter->QueryInterface(_uuidof(IWICBitmapSource), ppWICBitmapSource.put_void()));

    return ppWICBitmapSource;
}

void AddFrameToWICBitmap(
    winrt::com_ptr<IWICImagingFactory> const& pWICImagingFactory,
    winrt::com_ptr<IWICBitmapEncoder> const& pWICBitmapEncoder,
    winrt::com_ptr<IWICBitmapSource> const& pWICBitmapSource,
    BITMAP_VERSION bmpv)
{
    winrt::com_ptr<IWICBitmapFrameEncode> spWICFrameEncoder;
    winrt::com_ptr<IPropertyBag2> spWICEncoderOptions;

    THROW_IF_FAILED(pWICBitmapEncoder->CreateNewFrame(spWICFrameEncoder.put(), spWICEncoderOptions.put()));

    GUID containerGuid;
    THROW_IF_FAILED(pWICBitmapEncoder->GetContainerFormat(&containerGuid));

    if ((containerGuid == GUID_ContainerFormatBmp) && (bmpv == BMPV_5))
    {
        // Write the encoder option to the property bag instance.
        VARIANT varValue{};

        varValue.vt = VT_BOOL;
        varValue.boolVal = VARIANT_TRUE;

        // Options to enable the v5 header support for 32bppBGRA.
        PROPBAG2 v5HeaderOption{};

        std::wstring str = L"EnableV5Header32bppBGRA";
        v5HeaderOption.pstrName = (LPOLESTR)str.c_str();

        THROW_IF_FAILED(spWICEncoderOptions->Write(1, &v5HeaderOption, &varValue));
    }

    THROW_IF_FAILED(spWICFrameEncoder->Initialize(spWICEncoderOptions.get()));

    UINT uWidth, uHeight;
    THROW_IF_FAILED(pWICBitmapSource->GetSize(&uWidth, &uHeight));

    THROW_IF_FAILED(spWICFrameEncoder->SetSize(uWidth, uHeight));

    winrt::com_ptr<IWICBitmapSource> spBitmapSourceConverted;
    spBitmapSourceConverted = ConvertWICBitmapPixelFormat(pWICImagingFactory, pWICBitmapSource, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone);

    WICRect rect { 0, 0, static_cast<INT>(uWidth), static_cast<INT>(uHeight) };

    // Write the image data and commit
    THROW_IF_FAILED(spWICFrameEncoder->WriteSource(spBitmapSourceConverted.get(), &rect));

    THROW_IF_FAILED(spWICFrameEncoder->Commit());
}

winrt::com_ptr<IStream> GetStreamOfWICBitmapSource(
    winrt::com_ptr<IWICImagingFactory> const& pWICImagingFactory,
    winrt::com_ptr<IWICBitmapSource> const& pWICBitmapSource,
    _In_ REFGUID guidContainerFormat,
    _In_ BITMAP_VERSION bmpv)
{
    winrt::com_ptr<IStream> spImageStream;
    THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr, true, spImageStream.put()));

    // Create encoder and initialize it
    winrt::com_ptr<IWICBitmapEncoder> spWICEncoder;
    THROW_IF_FAILED(pWICImagingFactory->CreateEncoder(guidContainerFormat, nullptr, spWICEncoder.put()));

    THROW_IF_FAILED(spWICEncoder->Initialize(spImageStream.get(), WICBitmapEncoderCacheOption::WICBitmapEncoderNoCache));

    // Add a single frame to the encoder with the Bitmap
    AddFrameToWICBitmap(pWICImagingFactory, spWICEncoder, pWICBitmapSource, bmpv);

    THROW_IF_FAILED(spWICEncoder->Commit());

    // Seek the stream to the beginning and transfer
    static const LARGE_INTEGER lnBeginning = {};
    THROW_IF_FAILED(spImageStream->Seek(lnBeginning, STREAM_SEEK_SET, nullptr));

    return spImageStream;
}

void SaveImageWithWIC(
    winrt::com_ptr<IWICImagingFactory> const& pWICImagingFactory,
    winrt::com_ptr<IWICBitmapSource> const& pWICBitmapSource,
    _In_ REFGUID guidContainerFormat,
    winrt::com_ptr<IStream>& pStream)
{
    winrt::com_ptr<IStream> spImageStream;
    spImageStream = GetStreamOfWICBitmapSource(pWICImagingFactory, pWICBitmapSource, guidContainerFormat, BMPV_1);

    // Seek the stream to the beginning and transfer
    static LARGE_INTEGER const lnBeginning{ 0 };
    THROW_IF_FAILED(spImageStream->Seek(lnBeginning, STREAM_SEEK_SET, nullptr));

    static ULARGE_INTEGER lnbuffer{ INT_MAX };
    THROW_IF_FAILED(spImageStream->CopyTo(pStream.get(), lnbuffer, nullptr, nullptr));
}

void Microsoft::Windows::AppNotifications::WICHelpers::WriteHIconToPngFile(_In_ HICON hIcon, _In_ PCWSTR pszFileName)
{
    winrt::com_ptr<IWICImagingFactory> spWICImagingFactory;
    THROW_IF_FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&spWICImagingFactory)));

    winrt::com_ptr<IWICBitmap> spWICBitmap;
    THROW_IF_FAILED(spWICImagingFactory->CreateBitmapFromHICON(hIcon, spWICBitmap.put()));

    // Create stream to save the HICON to.
    winrt::com_ptr<IStream> spStream;
    THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr, TRUE, spStream.put()));

    winrt::com_ptr<IWICBitmapSource> spWICBitmapSource;
    spWICBitmapSource = spWICBitmap;

    SaveImageWithWIC(spWICImagingFactory, spWICBitmapSource, GUID_ContainerFormatPng, spStream);

    // Write out the stream to a file.
    winrt::com_ptr<IStream> spStreamOut;
    THROW_IF_FAILED(SHCreateStreamOnFileEx(pszFileName, STGM_CREATE | STGM_WRITE | STGM_SHARE_DENY_WRITE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, spStreamOut.put()));

    STATSTG statstg;
    THROW_IF_FAILED(spStream->Stat(&statstg, STATFLAG_NONAME));

    THROW_IF_FAILED(IStream_Reset(spStream.get()));

    THROW_IF_FAILED(spStreamOut->SetSize(statstg.cbSize));

    THROW_IF_FAILED(spStream->CopyTo(spStreamOut.get(), statstg.cbSize, nullptr, nullptr));

    THROW_IF_FAILED(spStreamOut->Commit(STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE));
}
