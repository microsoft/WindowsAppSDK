// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <future>
#include <ppltasks.h>
#include <pplawait.h>
#include <ShlObj.h>
#include "CameraCaptureUI.h"
#include "Microsoft.Windows.Media.Capture.CameraCaptureUI.g.cpp"

using namespace winrt;
using namespace Windows::Media::Capture;
using namespace Windows::Storage;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::ApplicationModel::DataTransfer;

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    IAsyncOperation<hstring> LaunchCameraForResultToken(WindowId const& targetWindow, ValueSet const& properties)
    {
        LauncherOptions options;
        if (targetWindow.Value)
        {
            check_hresult(options.as<IInitializeWithWindow>()->Initialize(reinterpret_cast<HWND>(targetWindow.Value)));
        }

        options.TreatAsUntrusted(false);
        options.DisplayApplicationPicker(false);
        options.TargetApplicationPackageFamilyName(L"Microsoft.WindowsCamera_8wekyb3d8bbwe");

        Uri launchUri{ L"microsoft.windows.camera.picker:" };
        auto result = co_await Launcher::LaunchUriForResultsAsync(launchUri, options, properties);
        switch (result.Status())
        {
        case LaunchUriStatus::AppUnavailable:
            throw hresult_error(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));

        case LaunchUriStatus::ProtocolUnavailable:
            throw hresult_error(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED));

        case LaunchUriStatus::Success:
            break;

        default:
            throw hresult_error(E_FAIL);
        }

        if (!result.Result())
        {
            co_return L"";
        }
        else if (auto t = result.Result().TryLookup(L"SelectedTokens"))
        {
            co_return t.as<hstring>();
        }
        else
        {
            throw hresult_canceled();
        }
    }

    concurrency::task<token_and_path> CreateEmptyFileAndGetToken(hstring const& fileExtension)
    {
        auto tempFolder = ApplicationData::Current().TemporaryFolder();
        auto tempFile = co_await tempFolder.CreateFileAsync(L"CCapture" + fileExtension, CreationCollisionOption::GenerateUniqueName);
        auto tempFilePath = tempFile.Path();
        auto token = SharedStorageAccessManager::AddFile(tempFile);

        co_return token_and_path{ token, tempFilePath };
    }

    IAsyncOperation<StorageFile> CameraCaptureUI::CaptureFileAsync(CameraCaptureUIMode mode)
    {
        auto strong = get_strong();

        bool addPicker = false;
        const wchar_t* mediaType = nullptr;
        if (mode == CameraCaptureUIMode::PhotoOrVideo)
        {
            mediaType = L"photoOrVideo";
        }
        else if (mode == CameraCaptureUIMode::Photo)
        {
            mediaType = L"photo";
        }
        else if (mode == CameraCaptureUIMode::Video)
        {
            mediaType = L"video";
        }
        else
        {
            throw hresult_invalid_argument();
        }

        ValueSet properties;
        properties.Insert(L"MediaType", box_value(mediaType));

        if ((mode == CameraCaptureUIMode::PhotoOrVideo) || (mode == CameraCaptureUIMode::Photo))
        {
            m_photoSettings->validate();
            m_photoTokenFile = co_await CreateEmptyFileAndGetToken(m_photoSettings->GetFileExtension());
            properties.Insert(L"PhotoFileToken", box_value(m_photoTokenFile.token));
            m_photoSettings->Serialize(properties);
        }

        if ((mode == CameraCaptureUIMode::PhotoOrVideo) || (mode == CameraCaptureUIMode::Video))
        {
            m_videoSettings->validate();
            m_videoTokenFile = co_await CreateEmptyFileAndGetToken(m_videoSettings->GetFileExtension());
            properties.Insert(L"VideoFileToken", box_value(m_videoTokenFile.token));
            m_videoSettings->Serialize(properties);
        }

        if (addPicker)
        {
            properties.Insert(L"id", box_value(L"picker"));
        }

        auto tokenValue = co_await LaunchCameraForResultToken(m_windowId, properties);
        if (tokenValue == m_photoTokenFile.token)
        {
            co_return co_await StorageFile::GetFileFromPathAsync(m_photoTokenFile.path);
        }
        else if (tokenValue == m_videoTokenFile.token)
        {
            co_return co_await StorageFile::GetFileFromPathAsync(m_videoTokenFile.path);
        }
        else
        {
            co_return co_await SharedStorageAccessManager::RedeemTokenForFileAsync(tokenValue);
        }
    }
}
