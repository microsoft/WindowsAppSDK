// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "CameraCaptureUIVideoCaptureSettings.h"
#include "Microsoft.Windows.Media.Capture.CameraCaptureUIVideoCaptureSettings.g.cpp"


namespace winrt::Microsoft::Windows::Media::Capture::implementation
{
    void CameraCaptureUIVideoCaptureSettings::validate()
    {
        auto lock = m_lock.lock_shared();
        float durationInMs = m_maxDurationInSeconds * 1000.0f;
        if ((durationInMs < 0.0f) || (durationInMs > UINT32_MAX))
        {
            throw hresult_invalid_argument(L"VideoSettings.MaxDurationInSeconds must be valid");
        }

        if (!m_allowTrimming && m_maxDurationInSeconds != 0)
        {
            throw hresult_invalid_argument(L"VideoSettings.MaxDurationInSeconds can't be set if .AllowTrimming is false");
        }
    }

    hstring CameraCaptureUIVideoCaptureSettings::GetFileExtension()
    {
        auto lock = m_lock.lock_shared();
        switch (m_format)
        {
        case CameraCaptureUIVideoFormat::Mp4:
            return L".mp4";
        case CameraCaptureUIVideoFormat::Wmv:
            return L".wmv";
        default:
            throw hresult_invalid_argument(L"VideoSettings.Format unknown value");
        }
    }

    void CameraCaptureUIVideoCaptureSettings::Serialize(winrt::Windows::Foundation::Collections::ValueSet const& props)
    {
        auto lock = m_lock.lock_shared();
        props.Insert(L"AllowTrimming", box_value(m_allowTrimming));
        props.Insert(L"VideoFormat", box_value(static_cast<int32_t>(m_format)));
        props.Insert(L"MaxVideoResolution", box_value(static_cast<int32_t>(m_maxResolution)));
        props.Insert(L"MaxDurationInSeconds", box_value(static_cast<int32_t>(m_maxDurationInSeconds)));
    }
}
