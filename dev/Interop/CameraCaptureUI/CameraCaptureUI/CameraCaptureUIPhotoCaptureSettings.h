// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoCaptureSettings.g.h"

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    struct CameraCaptureUIPhotoCaptureSettings : CameraCaptureUIPhotoCaptureSettingsT<CameraCaptureUIPhotoCaptureSettings>
    {
        CameraCaptureUIPhotoCaptureSettings() = default;

        void validate();
        hstring GetFileExtension();
        void Serialize(winrt::Windows::Foundation::Collections::ValueSet const& props);

        wil::srwlock m_lock;

        bool AllowCropping() { return read_with_lock(m_allowCropping); }
        void AllowCropping(bool value) { write_with_lock(m_allowCropping, value); }

        winrt::Windows::Foundation::Size CroppedAspectRatio() { return read_with_lock(m_croppedAspectRatio); }
        void CroppedAspectRatio(winrt::Windows::Foundation::Size const& value) { write_with_lock(m_croppedAspectRatio, value); }

        winrt::Windows::Foundation::Size CroppedSizeInPixels() { return read_with_lock(m_croppedSizeInPixels); }
        void CroppedSizeInPixels(winrt::Windows::Foundation::Size const& value) { write_with_lock(m_croppedSizeInPixels, value); }

        winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat Format() { return read_with_lock(m_format); }
        void Format(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat const& value) { write_with_lock(m_format, value); }

        winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution MaxResolution() { return read_with_lock(m_maxResolution); }
        void MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution const& value) { write_with_lock(m_maxResolution, value); }

    private:
        template<typename T> auto read_with_lock(T& t)
        {
            auto lock = m_lock.lock_shared();
            return t;
        }
        template<typename T, typename R> void write_with_lock(T& t, R&& r)
        {
            auto lock = m_lock.lock_exclusive();
            t = std::forward<R>(r);
        }

        bool m_allowCropping{ true };
        winrt::Windows::Foundation::Size m_croppedAspectRatio{ 0.0f, 0.0f };
        winrt::Windows::Foundation::Size m_croppedSizeInPixels{ 0.0f, 0.0f };
        winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat m_format{ winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg };
        winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution m_maxResolution{ winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::HighestAvailable };
    };
}

namespace winrt::Microsoft::Windows::Media::Capture::factory_implementation
{
    struct CameraCaptureUIPhotoCaptureSettings : CameraCaptureUIPhotoCaptureSettingsT<CameraCaptureUIPhotoCaptureSettings, implementation::CameraCaptureUIPhotoCaptureSettings>
    {
    };
}
