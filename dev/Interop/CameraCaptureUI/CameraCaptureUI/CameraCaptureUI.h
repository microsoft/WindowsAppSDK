// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "Microsoft.Windows.Media.Capture.CameraCaptureUI.g.h"
#include "CameraCaptureUIPhotoCaptureSettings.h"
#include "CameraCaptureUIVideoCaptureSettings.h"
#include "TelemetryHelper.h"
#include <TerminalVelocityFeatures-CameraCaptureUI.h>

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    struct token_and_path
    {
        hstring token;
        hstring path;
    };

    struct CameraCaptureUI : CameraCaptureUIT<CameraCaptureUI>
    {
        CameraCaptureUI(winrt::Microsoft::UI::WindowId const& windowId) :
            m_windowId(windowId)
        {
            THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Media::Capture::Feature_CameraCaptureUI::IsEnabled());
        }

        Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoCaptureSettings PhotoSettings()
        {
            return *m_photoSettings;
        }

        Microsoft::Windows::Media::Capture::CameraCaptureUIVideoCaptureSettings VideoSettings()
        {
            return *m_videoSettings;
        }

        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> CaptureFileAsync(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMode mode);

    private:
        std::mutex m_captureMutex; // Mutex for locking
        TelemetryHelper m_telemetryHelper;
        winrt::Microsoft::UI::WindowId m_windowId;
        token_and_path m_photoTokenFile;
        token_and_path m_videoTokenFile;
        com_ptr<CameraCaptureUIVideoCaptureSettings> m_videoSettings = make_self<CameraCaptureUIVideoCaptureSettings>();
        com_ptr<CameraCaptureUIPhotoCaptureSettings> m_photoSettings = make_self<CameraCaptureUIPhotoCaptureSettings>();
    };
}
namespace winrt::Microsoft::Windows::Media::Capture::factory_implementation
{
    struct CameraCaptureUI : CameraCaptureUIT<CameraCaptureUI, implementation::CameraCaptureUI>
    {
    };
}
