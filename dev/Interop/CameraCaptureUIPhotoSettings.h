// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoSettings.g.h"
#include "PropertyHelper.h"

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    struct CameraCaptureUIPhotoSettings : CameraCaptureUIPhotoSettingsT<CameraCaptureUIPhotoSettings>
    {
        CameraCaptureUIPhotoSettings() = default;

        void validate();

        hstring GetFileExtension();
        void Serialize(winrt::Windows::Foundation::Collections::ValueSet const& props);

        basic_property<bool> AllowCropping{ true };
        basic_property<winrt::Windows::Foundation::Size> CroppedAspectRatio{ 0.0f, 0.0f };
        basic_property<winrt::Windows::Foundation::Size> CroppedSizeInPixels{ 0.0f, 0.0f };
        basic_property<winrt::Windows::Media::Capture::CameraCaptureUIPhotoFormat> Format{ winrt::Windows::Media::Capture::CameraCaptureUIPhotoFormat::Jpeg };
        basic_property<winrt::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution> MaxResolution{ winrt::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution::HighestAvailable };
    };
}

namespace winrt::Microsoft::Windows::Media::Capture::factory_implementation
{
    struct CameraCaptureUIPhotoSettings : CameraCaptureUIPhotoSettingsT<CameraCaptureUIPhotoSettings, implementation::CameraCaptureUIPhotoSettings>
    {
    };
}
