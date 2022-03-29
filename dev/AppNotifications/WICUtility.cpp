
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
    winrt::com_ptr<IWICImagingFactory> const& wicImagingFactory,
    winrt::com_ptr<IWICBitmapSource> const& wicBitmapSource,
    WICPixelFormatGUID guidPixelFormatSource,
    WICBitmapDitherType bitmapDitherType)
{
    winrt::com_ptr<IWICFormatConverter> wicFormatConverter;
    THROW_IF_FAILED(wicImagingFactory->CreateFormatConverter(wicFormatConverter.put()));

    THROW_IF_FAILED(wicFormatConverter->Initialize(wicBitmapSource.get(), guidPixelFormatSource, bitmapDitherType, nullptr, 0.f, WICBitmapPaletteTypeCustom));

    // Store the converted bitmap as ppToRenderBitmapSource
    winrt::com_ptr<IWICBitmapSource> wicBitmapSourceConverted;
    THROW_IF_FAILED(wicFormatConverter->QueryInterface(_uuidof(IWICBitmapSource), wicBitmapSourceConverted.put_void()));

    return wicBitmapSourceConverted;
}

void AddFrameToWICBitmap(
    winrt::com_ptr<IWICImagingFactory> const& wicImagingFactory,
    winrt::com_ptr<IWICBitmapEncoder> const& wicEncoder,
    winrt::com_ptr<IWICBitmapSource> const& wicBitmapSource,
    BITMAP_VERSION bmpv)
{
    winrt::com_ptr<IWICBitmapFrameEncode> wicFrameEncoder;
    winrt::com_ptr<IPropertyBag2> wicEncoderOptions;

    THROW_IF_FAILED(wicEncoder->CreateNewFrame(wicFrameEncoder.put(), wicEncoderOptions.put()));

    GUID containerGuid;
    THROW_IF_FAILED(wicEncoder->GetContainerFormat(&containerGuid));

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

        THROW_IF_FAILED(wicEncoderOptions->Write(1, &v5HeaderOption, &varValue));
    }

    THROW_IF_FAILED(wicFrameEncoder->Initialize(wicEncoderOptions.get()));

    UINT uWidth, uHeight;
    THROW_IF_FAILED(wicBitmapSource->GetSize(&uWidth, &uHeight));

    THROW_IF_FAILED(wicFrameEncoder->SetSize(uWidth, uHeight));

    winrt::com_ptr<IWICBitmapSource> wicbitmapSourceConverted;
    wicbitmapSourceConverted = ConvertWICBitmapPixelFormat(wicImagingFactory, wicBitmapSource, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone);

    WICRect rect { 0, 0, static_cast<INT>(uWidth), static_cast<INT>(uHeight) };

    // Write the image data and commit
    THROW_IF_FAILED(wicFrameEncoder->WriteSource(wicbitmapSourceConverted.get(), &rect));

    THROW_IF_FAILED(wicFrameEncoder->Commit());
}

winrt::com_ptr<IStream> GetStreamOfWICBitmapSource(
    winrt::com_ptr<IWICImagingFactory> const& wicImagingFactory,
    winrt::com_ptr<IWICBitmapSource> const& wicBitmapSource,
    _In_ REFGUID guidContainerFormat,
    _In_ BITMAP_VERSION bmpv)
{
    winrt::com_ptr<IStream> spImageStream;
    THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr, true, spImageStream.put()));

    // Create encoder and initialize it
    winrt::com_ptr<IWICBitmapEncoder> wicEncoder;
    THROW_IF_FAILED(wicImagingFactory->CreateEncoder(guidContainerFormat, nullptr, wicEncoder.put()));

    THROW_IF_FAILED(wicEncoder->Initialize(spImageStream.get(), WICBitmapEncoderCacheOption::WICBitmapEncoderNoCache));

    // Add a single frame to the encoder with the Bitmap
    AddFrameToWICBitmap(wicImagingFactory, wicEncoder, wicBitmapSource, bmpv);

    THROW_IF_FAILED(wicEncoder->Commit());

    // Seek the stream to the beginning and transfer
    static const LARGE_INTEGER lnBeginning = {};
    THROW_IF_FAILED(spImageStream->Seek(lnBeginning, STREAM_SEEK_SET, nullptr));

    return spImageStream;
}

void SaveImageWithWIC(
    winrt::com_ptr<IWICImagingFactory> const& wicImagingFactory,
    winrt::com_ptr<IWICBitmapSource> const& wicBitmapSource,
    _In_ REFGUID guidContainerFormat,
    winrt::com_ptr<IStream>& pStream)
{
    winrt::com_ptr<IStream> spImageStream;
    spImageStream = GetStreamOfWICBitmapSource(wicImagingFactory, wicBitmapSource, guidContainerFormat, BMPV_1);

    // Seek the stream to the beginning and transfer
    static LARGE_INTEGER const lnBeginning{ 0 };
    THROW_IF_FAILED(spImageStream->Seek(lnBeginning, STREAM_SEEK_SET, nullptr));

    static ULARGE_INTEGER lnbuffer{ INT_MAX };
    THROW_IF_FAILED(spImageStream->CopyTo(pStream.get(), lnbuffer, nullptr, nullptr));
}

void Microsoft::Windows::AppNotifications::WICHelpers::WriteHIconToPngFile(wil::unique_hicon const& hIcon, _In_ PCWSTR pszFileName)
{
    auto wicImagingFactory{ winrt::create_instance<IWICImagingFactory>(CLSID_WICImagingFactory, CLSCTX_INPROC_SERVER) };
   
    winrt::com_ptr<IWICBitmap> wicBitmap;
    THROW_IF_FAILED(wicImagingFactory->CreateBitmapFromHICON(hIcon.get(), wicBitmap.put()));

    // Create stream to save the HICON to.
    winrt::com_ptr<IStream> spStream;
    THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr, TRUE, spStream.put()));

    winrt::com_ptr<IWICBitmapSource> wicBitmapSource;
    wicBitmapSource = wicBitmap;

    SaveImageWithWIC(wicImagingFactory, wicBitmapSource, GUID_ContainerFormatPng, spStream);

    // Write out the stream to a file.
    winrt::com_ptr<IStream> spStreamOut;
    THROW_IF_FAILED(SHCreateStreamOnFileEx(pszFileName, STGM_CREATE | STGM_WRITE | STGM_SHARE_DENY_WRITE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, spStreamOut.put()));

    STATSTG statstg;
    THROW_IF_FAILED(spStream->Stat(&statstg, STATFLAG_NONAME));

    THROW_IF_FAILED(IStream_Reset(spStream.get()));

    THROW_IF_FAILED(spStreamOut->SetSize(statstg.cbSize));

    // TODO: Comments need to be added
    THROW_IF_FAILED(spStream->CopyTo(spStreamOut.get(), statstg.cbSize, nullptr, nullptr));

    THROW_IF_FAILED(spStreamOut->Commit(STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE));
}
