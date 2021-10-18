// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "Microsoft.Windows.Media.Capture.CameraCaptureUI.g.h"
#include "CameraCaptureUIPhotoSettings.h"
#include "CameraCaptureUIVideoSettings.h"

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    struct token_and_path
    {
        hstring token;
        hstring path;
    };

    struct CameraCaptureUI : CameraCaptureUIT<CameraCaptureUI>
    {
        CameraCaptureUI(Microsoft::Windows::Media::Capture::WindowId const& window) :
            m_windowId(window)
        {
        }

        Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoSettings PhotoSettings()
        {
            return *m_photoSettings;
        }

        Microsoft::Windows::Media::Capture::CameraCaptureUIVideoSettings VideoSettings()
        {
            return *m_videoSettings;
        }

        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> CaptureFileAsync(winrt::Windows::Media::Capture::CameraCaptureUIMode mode);

    private:
        Microsoft::Windows::Media::Capture::WindowId m_windowId;
        token_and_path m_photoTokenFile;
        token_and_path m_videoTokenFile;
        com_ptr<CameraCaptureUIVideoSettings> m_videoSettings = make_self<CameraCaptureUIVideoSettings>();
        com_ptr<CameraCaptureUIPhotoSettings> m_photoSettings = make_self<CameraCaptureUIPhotoSettings>();
    };
}
namespace winrt::Microsoft::Windows::Media::Capture::factory_implementation
{
    struct CameraCaptureUI : CameraCaptureUIT<CameraCaptureUI, implementation::CameraCaptureUI>
    {
    };
}
