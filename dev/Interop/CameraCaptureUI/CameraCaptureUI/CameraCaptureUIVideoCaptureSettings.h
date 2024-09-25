// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "Microsoft.Windows.Media.Capture.CameraCaptureUIVideoCaptureSettings.g.h"
#include "PropertyHelper.h"

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    struct CameraCaptureUIVideoCaptureSettings : CameraCaptureUIVideoCaptureSettingsT<CameraCaptureUIVideoCaptureSettings>
    {
        CameraCaptureUIVideoCaptureSettings() = default;

        void validate();

        hstring GetFileExtension();
        void Serialize(winrt::Windows::Foundation::Collections::ValueSet const& props);

        basic_property<bool> AllowTrimming{ true };
        basic_property<winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat> Format{ winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4 };
        basic_property<float> MaxDurationInSeconds{ 0.0f };
        basic_property<winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution> MaxResolution{ winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::HighestAvailable };
    };
}
namespace winrt::Microsoft::Windows::Media::Capture::factory_implementation
{
    struct CameraCaptureUIVideoCaptureSettings : CameraCaptureUIVideoCaptureSettingsT<CameraCaptureUIVideoCaptureSettings, implementation::CameraCaptureUIVideoCaptureSettings>
    {
    };
}
