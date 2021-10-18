// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "CameraCaptureUIVideoSettings.h"
#include "Microsoft.Windows.Media.Capture.CameraCaptureUIVideoSettings.g.cpp"

using namespace winrt;
using namespace Windows::Media::Capture;

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
	void CameraCaptureUIVideoSettings::validate()
	{
		float durationInMs = MaxDurationInSeconds * 1000.0f;
		if ((durationInMs < 0.0f) || (durationInMs > UINT32_MAX))
		{
			throw hresult_invalid_argument(L"VideoSettings.MaxDurationInSeconds must be greater than zero seconds");
		}

		if (!AllowTrimming && MaxDurationInSeconds != 0)
		{
			throw hresult_invalid_argument(L"VideoSettings.MaxDurationInSeconds can't be set if .AllowTrimming is false");
		}
	}

	hstring CameraCaptureUIVideoSettings::GetFileExtension()
	{
		switch (Format)
		{
		case CameraCaptureUIVideoFormat::Mp4:
			return L".mp4";
		case CameraCaptureUIVideoFormat::Wmv:
			return L".wmv";
		default:
			throw hresult_invalid_argument(L"VideoSettings.Format unknown value");
		}
	}

	void CameraCaptureUIVideoSettings::Serialize(winrt::Windows::Foundation::Collections::ValueSet const& props)
	{
		props.Insert(L"AllowTrimming", box_value(AllowTrimming()));
		props.Insert(L"VideoFormat", box_value(static_cast<int32_t>(Format())));
		props.Insert(L"MaxVideoResolution", box_value(static_cast<int32_t>(MaxResolution())));
		props.Insert(L"MaxDurationInSeconds", box_value(static_cast<int32_t>(MaxDurationInSeconds())));
	}
}
