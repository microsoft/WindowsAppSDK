// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "Microsoft.Windows.Media.Capture.CameraCaptureUIVideoSettings.g.h"
#include "PropertyHelper.h"

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    struct CameraCaptureUIVideoSettings : CameraCaptureUIVideoSettingsT<CameraCaptureUIVideoSettings>
    {
        CameraCaptureUIVideoSettings() = default;

        void validate();

        hstring GetFileExtension();
        void Serialize(winrt::Windows::Foundation::Collections::ValueSet const& props);

        basic_property<bool> AllowTrimming{ true };
        basic_property<winrt::Windows::Media::Capture::CameraCaptureUIVideoFormat> Format{ winrt::Windows::Media::Capture::CameraCaptureUIVideoFormat::Mp4 };
        basic_property<float> MaxDurationInSeconds{ 0.0f };
        basic_property<winrt::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution> MaxResolution{ winrt::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution::HighestAvailable };
    };
}
namespace winrt::Microsoft::Windows::Media::Capture::factory_implementation
{
    struct CameraCaptureUIVideoSettings : CameraCaptureUIVideoSettingsT<CameraCaptureUIVideoSettings, implementation::CameraCaptureUIVideoSettings>
    {
    };
}
