// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "CameraCaptureUIPhotoCaptureSettings.h"
#include "Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoCaptureSettings.g.cpp"

using namespace winrt::Windows::Foundation;

namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    void CameraCaptureUIPhotoCaptureSettings::validate()
    {
        auto lock = m_lock.lock_shared();
        Size const size = m_croppedSizeInPixels; 
        Size const aspect = m_croppedAspectRatio; 
        auto hasPhotoFixedSizeConstraint = (size.Width != 0) || (size.Height != 0);
        auto hasPhotoAspectRatioConstraint = (aspect.Width != 0) || (aspect.Height != 0);
        auto hasPhotoSizeConstraint = hasPhotoFixedSizeConstraint || hasPhotoAspectRatioConstraint;

        if (hasPhotoAspectRatioConstraint && hasPhotoFixedSizeConstraint)
        {
            throw hresult_invalid_argument(L"PhotoSettings can't have both a size and aspect ratio specified");
        }
        else if (!m_allowCropping && hasPhotoSizeConstraint)
        {
            throw hresult_invalid_argument(L"PhotoSettings can't have a ratio or size specified with cropping disabled");
        }
    }

    hstring CameraCaptureUIPhotoCaptureSettings::GetFileExtension()
    {
        auto lock = m_lock.lock_shared();
        switch (m_format)
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

    void CameraCaptureUIPhotoCaptureSettings::Serialize(winrt::Windows::Foundation::Collections::ValueSet const& props)
    {
        auto lock = m_lock.lock_shared();
        props.Insert(L"AllowCropping", box_value(m_allowCropping));
        props.Insert(L"PhotoFormat", box_value<int32_t>(static_cast<int32_t>(m_format)));
        props.Insert(L"MaxResolution", box_value<int32_t>(static_cast<int32_t>(m_maxResolution)));
        props.Insert(L"PhotoCropWidth", box_value(static_cast<int32_t>(m_croppedSizeInPixels.Width)));
        props.Insert(L"PhotoCropHeight", box_value(static_cast<int32_t>(m_croppedSizeInPixels.Height)));
        props.Insert(L"PhotoCropARWidth", box_value(static_cast<int32_t>(m_croppedAspectRatio.Width)));
        props.Insert(L"PhotoCropARHeight", box_value(static_cast<int32_t>(m_croppedAspectRatio.Height)));
    }
}
