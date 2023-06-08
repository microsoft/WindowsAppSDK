// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <ShellLocalization.h>
#include <AppNotificationUtility.h>

#include <cwctype>
#include <filesystem>
#include <winrt/Windows.Foundation.h>
#include <winrt/base.h>
#include <externs.h>

#include <ShObjIdl_core.h>
#include <wincodec.h>
#include <Ocidl.h>
#include <windows.h>

#include <frameworkudk/toastnotifications.h>

namespace std
{
    using namespace std::filesystem;
}

typedef enum
{
    VERSION1,
    VERSION5,
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
    BITMAP_VERSION bitmapVersion)
{
    winrt::com_ptr<IWICBitmapFrameEncode> wicFrameEncoder;
    winrt::com_ptr<IPropertyBag2> wicEncoderOptions;

    THROW_IF_FAILED(wicEncoder->CreateNewFrame(wicFrameEncoder.put(), wicEncoderOptions.put()));

    GUID containerGuid;
    THROW_IF_FAILED(wicEncoder->GetContainerFormat(&containerGuid));

    if ((containerGuid == GUID_ContainerFormatBmp) && (bitmapVersion == BITMAP_VERSION::VERSION5))
    {
        // Write the encoder option to the property bag instance.
        VARIANT varValue{};
        varValue.vt = VT_BOOL;
        varValue.boolVal = VARIANT_TRUE;

        // Options to enable the v5 header support for 32bppBGRA.
        PROPBAG2 v5HeaderOption{};
        v5HeaderOption.pstrName = (LPOLESTR) L"EnableV5Header32bppBGRA";

        THROW_IF_FAILED(wicEncoderOptions->Write(1, &v5HeaderOption, &varValue));
    }

    THROW_IF_FAILED(wicFrameEncoder->Initialize(wicEncoderOptions.get()));

    UINT width{};
    UINT height{};
    THROW_IF_FAILED(wicBitmapSource->GetSize(&width, &height));

    THROW_IF_FAILED(wicFrameEncoder->SetSize(width, height));

    winrt::com_ptr<IWICBitmapSource> wicbitmapSourceConverted
        { ConvertWICBitmapPixelFormat(wicImagingFactory, wicBitmapSource, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone) };

    WICRect rect{ 0 /* x-coordinate */, 0 /* y-coordinate */, static_cast<INT>(width), static_cast<INT>(height) };

    // Write the image data and commit
    THROW_IF_FAILED(wicFrameEncoder->WriteSource(wicbitmapSourceConverted.get(), &rect));
    THROW_IF_FAILED(wicFrameEncoder->Commit());
}

winrt::com_ptr<IStream> GetStreamOfWICBitmapSource(
    winrt::com_ptr<IWICImagingFactory> const& wicImagingFactory,
    winrt::com_ptr<IWICBitmapSource> const& wicBitmapSource,
    REFGUID guidContainerFormat,
    BITMAP_VERSION bitmapVersion)
{
    winrt::com_ptr<IStream> spImageStream;
    THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr /* handle */, true /* delete on release */, spImageStream.put()));

    // Create encoder and initialize it
    winrt::com_ptr<IWICBitmapEncoder> wicEncoder;
    THROW_IF_FAILED(wicImagingFactory->CreateEncoder(guidContainerFormat, nullptr, wicEncoder.put()));
    THROW_IF_FAILED(wicEncoder->Initialize(spImageStream.get(), WICBitmapEncoderCacheOption::WICBitmapEncoderNoCache));

    // Add a single frame to the encoder with the Bitmap
    AddFrameToWICBitmap(wicImagingFactory, wicEncoder, wicBitmapSource, bitmapVersion);
    THROW_IF_FAILED(wicEncoder->Commit());

    // Seek the stream to the beginning and transfer
    const LARGE_INTEGER lnBeginning{};
    THROW_IF_FAILED(spImageStream->Seek(lnBeginning, STREAM_SEEK_SET, nullptr /* new seek pointer */));

    return spImageStream;
}

void SaveImageWithWIC(
    winrt::com_ptr<IWICImagingFactory> const& wicImagingFactory,
    winrt::com_ptr<IWICBitmapSource> const& wicBitmapSource,
    GUID const& guidContainerFormat,
    winrt::com_ptr<IStream>& pStream)
{
    winrt::com_ptr<IStream> spImageStream = GetStreamOfWICBitmapSource(wicImagingFactory, wicBitmapSource, guidContainerFormat, BITMAP_VERSION::VERSION1);

    // Seek the stream to the beginning and transfer
    LARGE_INTEGER const lnBeginning{ 0 };
    THROW_IF_FAILED(spImageStream->Seek(lnBeginning, STREAM_SEEK_SET, nullptr /* new seek pointer */));

    ULARGE_INTEGER lnbuffer{ INT_MAX };
    THROW_IF_FAILED(spImageStream->CopyTo(pStream.get(), lnbuffer, nullptr /* pointer to number of bytes read */, nullptr /* pointer to number of bytes written */));
}

void WriteHIconToPngFile(wil::unique_hicon const& hIcon, _In_ PCWSTR pszFileName)
{
    auto wicImagingFactory{ winrt::create_instance<IWICImagingFactory>(CLSID_WICImagingFactory, CLSCTX_INPROC_SERVER) };

    winrt::com_ptr<IWICBitmap> wicBitmap;
    THROW_IF_FAILED(wicImagingFactory->CreateBitmapFromHICON(hIcon.get(), wicBitmap.put()));

    // Create stream to save the HICON to.
    winrt::com_ptr<IStream> spStream;
    THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr /* handle */, TRUE, spStream.put()));

    winrt::com_ptr<IWICBitmapSource> wicBitmapSource;
    wicBitmapSource = wicBitmap;

    SaveImageWithWIC(wicImagingFactory, wicBitmapSource, GUID_ContainerFormatPng, spStream);

    // Write out the stream to a file.
    winrt::com_ptr<IStream> spStreamOut;
    THROW_IF_FAILED(SHCreateStreamOnFileEx(pszFileName, STGM_CREATE | STGM_WRITE | STGM_SHARE_DENY_WRITE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, spStreamOut.put()));

    STATSTG statstg{};
    THROW_IF_FAILED(spStream->Stat(&statstg, STATFLAG_NONAME));

    THROW_IF_FAILED(IStream_Reset(spStream.get()));

    THROW_IF_FAILED(spStreamOut->SetSize(statstg.cbSize));

    THROW_IF_FAILED(spStream->CopyTo(spStreamOut.get(), statstg.cbSize, nullptr /* pointer to number of bytes read */, nullptr /* pointer to number of bytes written */));

    THROW_IF_FAILED(spStreamOut->Commit(STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE));
}


bool Microsoft::Windows::AppNotifications::ShellLocalization::IsIconFileExtensionSupported(std::filesystem::path const& iconFilePath)
{
    static PCWSTR c_supportedExtensions[]{ L".bmp", L".ico", L".jpg", L".png" };

    const auto fileExtension{ iconFilePath.extension() };
    const auto extension{ fileExtension.c_str() };
    for (auto supportedExtension : c_supportedExtensions)
    {
        if (CompareStringOrdinal(extension, -1, supportedExtension, -1, TRUE) == CSTR_EQUAL)
        {
            return true;
        }
    }

    return false;
}

inline std::path RetrieveLocalFolderPath()
{
    wil::unique_cotaskmem_string localAppDataPath;
    THROW_IF_FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0 /* flags */, nullptr /* access token handle */, &localAppDataPath));

    // path: C:\Users\<currentUser>\AppData\Local\Microsoft\WindowsAppSDK
    std::path localFolderPath{ localAppDataPath.get() };
    localFolderPath /= Microsoft::Windows::AppNotifications::ShellLocalization::c_localWindowsAppSDKFolder;

    if (!std::exists(localFolderPath))
    {
        std::create_directory(localFolderPath);
    }

    return localFolderPath;
}

inline wil::unique_hicon RetrieveIconFromProcess()
{
    std::wstring processPath{};
    THROW_IF_FAILED(wil::GetModuleFileNameExW(GetCurrentProcess(), nullptr, processPath));

    // Extract the Small icon as it is good enough for an App Notification icon since higher quality doesn't really impact in a substantial way.
    wil::unique_hicon hIcon{};
    THROW_HR_IF(E_FAIL, ExtractIconExW(processPath.c_str(), 0 /* index for first resource */, nullptr /* Large Icon */, &hIcon, 1) == 0);

    return hIcon;
}

HRESULT Microsoft::Windows::AppNotifications::ShellLocalization::RetrieveAssetsFromProcess(_Out_ Microsoft::Windows::AppNotifications::ShellLocalization::AppNotificationAssets& assets) noexcept try
{
    wil::unique_hicon hIcon{ RetrieveIconFromProcess() };

    std::wstring notificationAppId{ Microsoft::Windows::AppNotifications::Helpers::RetrieveNotificationAppId() };

    // path: C:\Users\<currentUser>\AppData\Local\Microsoft\WindowsAppSDK\{AppGUID}.png
    auto iconFilePath{ RetrieveLocalFolderPath() / (notificationAppId + c_pngExtension) };
    WriteHIconToPngFile(hIcon, iconFilePath.c_str());

    assets.displayName = Microsoft::Windows::AppNotifications::Helpers::GetDisplayNameBasedOnProcessName();
    assets.iconFilePath = iconFilePath;

    // TODO: In case we are caching icons from uninstalled apps who didn't call UnregisterAll,
    // we should make an effort to clean them up in an opportunistic way.

    return S_OK;
}
CATCH_RETURN()

HRESULT Microsoft::Windows::AppNotifications::ShellLocalization::RetrieveAssetsFromShortcut(_Out_ Microsoft::Windows::AppNotifications::ShellLocalization::AppNotificationAssets& assets) noexcept try
{
    wil::unique_cotaskmem_string displayName;
    wil::unique_cotaskmem_string iconFilePath;

    THROW_IF_FAILED(ToastNotifications_RetrieveAssets(&displayName, &iconFilePath));

    std::path iconFilePathAsSystemPath{ iconFilePath.get() };
    THROW_HR_IF(E_UNEXPECTED, !IsIconFileExtensionSupported(iconFilePathAsSystemPath));

    assets.displayName = displayName.get();
    assets.iconFilePath = iconFilePath.get();

    return S_OK;
}
CATCH_RETURN()

HRESULT Microsoft::Windows::AppNotifications::ShellLocalization::DeleteIconFromCache() noexcept try
{
    std::wstring notificationAppId{ Microsoft::Windows::AppNotifications::Helpers::RetrieveNotificationAppId() };

    // path: C:\Users\<currentUser>\AppData\Local\Microsoft\WindowsAppSDK\{AppGUID}.png
    std::path iconFilePath{ RetrieveLocalFolderPath() / (notificationAppId + c_pngExtension) };

    // If DeleteFile returned FALSE, then deletion failed and we should return the corresponding error code.
    RETURN_IF_WIN32_BOOL_FALSE(DeleteFileW(iconFilePath.c_str()));

    return S_OK;
}
CATCH_RETURN()
