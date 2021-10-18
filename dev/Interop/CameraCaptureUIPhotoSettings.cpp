// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "CameraCaptureUIPhotoSettings.h"
#include "Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoSettings.g.cpp"

using namespace winrt;
using namespace Windows::Media::Capture;
using namespace Windows::Foundation;

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
	void CameraCaptureUIPhotoSettings::validate()
	{
		Size const size = CroppedSizeInPixels;
		Size const aspect = CroppedAspectRatio;
		auto hasPhotoFixedSizeConstraint = (size.Width != 0) || (size.Height != 0);
		auto hasPhotoAspectRatioConstraint = (aspect.Width != 0) || (aspect.Height != 0);
		auto hasPhotoSizeConstraint = hasPhotoFixedSizeConstraint || hasPhotoAspectRatioConstraint;

		if (hasPhotoAspectRatioConstraint && hasPhotoAspectRatioConstraint)
		{
			throw hresult_invalid_argument(L"PhotoSettings can't have both a size and aspect ratio specified");
		}
		else if (AllowCropping && hasPhotoSizeConstraint)
		{
			throw hresult_invalid_argument(L"PhotoSettings allowing cropping can't have a ratio or size specified");
		}
	}

	hstring CameraCaptureUIPhotoSettings::GetFileExtension()
	{
		switch (Format)
		{
		case CameraCaptureUIPhotoFormat::Jpeg:
			return L".jpg";
		case CameraCaptureUIPhotoFormat::Png:
			return L".png";
		case CameraCaptureUIPhotoFormat::JpegXR:
			return L".jxr";
		default:
			throw hresult_invalid_argument(L"PhotoSettings.Format");
		}
	}

	void CameraCaptureUIPhotoSettings::Serialize(winrt::Windows::Foundation::Collections::ValueSet const& props)
	{
		props.Insert(L"AllowCropping", box_value(AllowCropping()));
		props.Insert(L"PhotoFormat", box_value<int32_t>(static_cast<int32_t>(Format())));
		props.Insert(L"MaxResolution", box_value<int32_t>(static_cast<int32_t>(MaxResolution())));
		props.Insert(L"PhotoCropWidth", box_value(static_cast<int32_t>(CroppedSizeInPixels().Width)));
		props.Insert(L"PhotoCropHeight", box_value(static_cast<int32_t>(CroppedSizeInPixels().Height)));
		props.Insert(L"PhotoCropARWidth", box_value(static_cast<int32_t>(CroppedAspectRatio().Width)));
		props.Insert(L"PhotoCropARHeight", box_value(static_cast<int32_t>(CroppedAspectRatio().Height)));
	}
}
