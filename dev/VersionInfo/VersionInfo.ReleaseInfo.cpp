// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include <pch.h>

#include "VersionInfo.ReleaseInfo.h"

#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfo.ReleaseInfo.g.cpp>

#include <WindowsAppRuntime.VersionInfo.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::implementation
{
    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::ReleaseInfo ReleaseInfo::Current()
    {
        const ::Microsoft::WindowsAppSDK::VersionInfo* versionInfo{ ::Microsoft::WindowsAppSDK::GetVersionInfo() };
        return winrt::make<implementation::ReleaseInfo>(versionInfo);
    }
    uint16_t ReleaseInfo::Major()
    {
        return m_versionInfo->Release.Major;
    }
    uint16_t ReleaseInfo::Minor()
    {
        return m_versionInfo->Release.Minor;
    }
    uint16_t ReleaseInfo::Patch()
    {
        return m_versionInfo->Release.Patch;
    }
    uint32_t ReleaseInfo::MajorMinor()
    {
        throw hresult_not_implemented();
    }
    hstring ReleaseInfo::Channel()
    {
        throw hresult_not_implemented();
    }
    hstring ReleaseInfo::VersionTag()
    {
        throw hresult_not_implemented();
    }
    hstring ReleaseInfo::VersionShortTag()
    {
        throw hresult_not_implemented();
    }
    hstring ReleaseInfo::FormattedVersionTag()
    {
        throw hresult_not_implemented();
    }
    hstring ReleaseInfo::FormattedVersionShortTag()
    {
        throw hresult_not_implemented();
    }
    hstring ReleaseInfo::ToString()
    {
        throw hresult_not_implemented();
    }
}
