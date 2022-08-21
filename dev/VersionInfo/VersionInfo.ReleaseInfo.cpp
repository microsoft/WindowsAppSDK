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
        return m_versionInfo->Release.MajorMinor;
    }
    hstring ReleaseInfo::Channel()
    {
        return m_versionInfo->Release.Channel;
    }
    hstring ReleaseInfo::VersionTag()
    {
        return m_versionInfo->Release.VersionTag;
    }
    hstring ReleaseInfo::VersionShortTag()
    {
        return m_versionInfo->Release.VersionShortTag;
    }
    hstring ReleaseInfo::FormattedVersionTag()
    {
        PCWSTR versionTag{ m_versionInfo->Release.VersionTag };
        if (!versionTag || (versionTag[0] == L'\0'))
        {
            return winrt::hstring();
        }
        else
        {
            return winrt::hstring{ L"-" } + versionTag;
        }
    }
    hstring ReleaseInfo::FormattedVersionShortTag()
    {
        PCWSTR versionShortTag{ m_versionInfo->Release.VersionShortTag };
        if (!versionShortTag || (versionShortTag[0] == L'\0'))
        {
            return winrt::hstring();
        }
        else
        {
            return winrt::hstring{ L"-" } + versionShortTag;
        }
    }
    hstring ReleaseInfo::ToString()
    {
        WCHAR s[64]{};

        const auto& release{ m_versionInfo->Release };
        PCWSTR channel{ release.Channel };
        if (channel && (channel[0] != L'\0'))
        {
            THROW_IF_FAILED(StringCchPrintfW(s, ARRAYSIZE(s), L"%hu.%hu-%s", release.Major, release.Minor, channel));
        }
        else
        {
            THROW_IF_FAILED(StringCchPrintfW(s, ARRAYSIZE(s), L"%hu.%hu.%hu", release.Major, release.Minor, release.Patch));
        }
        return winrt::hstring{ s };
    }
}
