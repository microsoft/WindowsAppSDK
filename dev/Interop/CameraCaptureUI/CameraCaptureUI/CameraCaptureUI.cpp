// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <future>
#include <ppltasks.h>
#include <pplawait.h>
#include <ShlObj.h>
#include "CameraCaptureUI.h"
#include "Microsoft.Windows.Media.Capture.CameraCaptureUI.g.cpp"
#include "CameraCaptureUITelemetry.h"
#include "TelemetryHelper.h"

//using namespace winrt::Windows::Media::Capture;
using namespace winrt::Windows::UI;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::ApplicationModel::DataTransfer;

static constexpr const wchar_t* CameraAppPackageName = L"Microsoft.WindowsCamera_8wekyb3d8bbwe";
static constexpr const wchar_t* CameraPickerUri = L"microsoft.windows.camera.picker:";


namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    IAsyncOperation<hstring> LaunchCameraForResultToken(winrt::Microsoft::UI::WindowId const& targetWindow, ValueSet const& properties)
    {
        LauncherOptions options;
        if (targetWindow.Value)
        {
            check_hresult(options.as<IInitializeWithWindow>()->Initialize(reinterpret_cast<HWND>(targetWindow.Value)));
        }

        options.TreatAsUntrusted(false);
        options.DisplayApplicationPicker(false);
        options.TargetApplicationPackageFamilyName(CameraAppPackageName);

        Uri launchUri(CameraPickerUri);
        winrt::Windows::System::LaunchUriResult result = co_await Launcher::LaunchUriForResultsAsync(launchUri, options, properties);
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
        bool isAppPackaged = m_telemetryHelper.IsPackagedApp();
        PCWSTR appName = m_telemetryHelper.GetAppName().c_str();
        try
        {
            auto strong = get_strong();
            CameraCaptureUITelemetry::CaptureInitiated(isAppPackaged, appName);
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

            auto tokenValue = co_await LaunchCameraForResultToken(m_windowId, properties);
            if (tokenValue.empty())
            {
                co_return nullptr;
            }
            StorageFile file = nullptr;

            if (tokenValue == m_photoTokenFile.token)
            {
                file = co_await StorageFile::GetFileFromPathAsync(m_photoTokenFile.path);
            }
            else if (tokenValue == m_videoTokenFile.token)
            {
                file = co_await StorageFile::GetFileFromPathAsync(m_videoTokenFile.path);
            }
            else
            {
                file = co_await SharedStorageAccessManager::RedeemTokenForFileAsync(tokenValue);
            }
            CameraCaptureUITelemetry::CaptureSuccessful(isAppPackaged, appName);
            co_return file;
        }
        catch (const hresult_error& ex)
        {
            CameraCaptureUITelemetry::CaptureError(isAppPackaged, appName, ex.code());
            throw ex;
        }
        catch (const std::exception& ex)
        {
            CameraCaptureUITelemetry::CaptureError(isAppPackaged, appName, E_FAIL);
            throw hresult_error(E_FAIL);
        }
    }
}
