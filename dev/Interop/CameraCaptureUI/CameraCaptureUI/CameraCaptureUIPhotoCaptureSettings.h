// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoCaptureSettings.g.h"
#include "PropertyHelper.h"

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    struct CameraCaptureUIPhotoCaptureSettings : CameraCaptureUIPhotoCaptureSettingsT<CameraCaptureUIPhotoCaptureSettings>
    {
        CameraCaptureUIPhotoCaptureSettings() = default;

        void validate();

        hstring GetFileExtension();
        void Serialize(winrt::Windows::Foundation::Collections::ValueSet const& props);

        basic_property<bool> AllowCropping{ true };
        basic_property<winrt::Windows::Foundation::Size> CroppedAspectRatio{ 0.0f, 0.0f };
        basic_property<winrt::Windows::Foundation::Size> CroppedSizeInPixels{ 0.0f, 0.0f };
        basic_property<winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat> Format{ winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg };
        basic_property<winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution> MaxResolution{ winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::HighestAvailable };
    };
}

namespace winrt::Microsoft::Windows::Media::Capture::factory_implementation
{
    struct CameraCaptureUIPhotoCaptureSettings : CameraCaptureUIPhotoCaptureSettingsT<CameraCaptureUIPhotoCaptureSettings, implementation::CameraCaptureUIPhotoCaptureSettings>
    {
    };
}
