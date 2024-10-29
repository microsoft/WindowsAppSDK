// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "Microsoft.Windows.Media.Capture.CameraCaptureUIVideoCaptureSettings.g.h"

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    struct CameraCaptureUIVideoCaptureSettings : CameraCaptureUIVideoCaptureSettingsT<CameraCaptureUIVideoCaptureSettings>
    {
        CameraCaptureUIVideoCaptureSettings() = default;

        void validate();

        hstring GetFileExtension();
        void Serialize(winrt::Windows::Foundation::Collections::ValueSet const& props);

        wil::srwlock m_lock;

        bool AllowTrimming() { return read_with_lock(m_allowTrimming); }
        void AllowTrimming(bool value) { write_with_lock(m_allowTrimming, value); }

        winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat Format() { return read_with_lock(m_format); }
        void Format(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat const& value) { write_with_lock(m_format, value); }

        float MaxDurationInSeconds() { return read_with_lock(m_maxDurationInSeconds); }
        void MaxDurationInSeconds(float value) { write_with_lock(m_maxDurationInSeconds, value); }

        winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution MaxResolution() { return read_with_lock(m_maxResolution); }
        void MaxResolution(winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution const& value) { write_with_lock(m_maxResolution, value); }

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

        bool m_allowTrimming{ true };
        winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat m_format{ winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4 };
        float m_maxDurationInSeconds{ 0.0f };
        winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution m_maxResolution{ winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::HighestAvailable };
    };
}
namespace winrt::Microsoft::Windows::Media::Capture::factory_implementation
{
    struct CameraCaptureUIVideoCaptureSettings : CameraCaptureUIVideoCaptureSettingsT<CameraCaptureUIVideoCaptureSettings, implementation::CameraCaptureUIVideoCaptureSettings>
    {
    };
}
