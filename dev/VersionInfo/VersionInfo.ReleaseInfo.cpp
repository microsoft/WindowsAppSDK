// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "VersionInfo.ReleaseInfo.h"

#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.ReleaseInfo.g.cpp>

#include <WindowsAppRuntime.VersionInfo.h>

#include <TerminalVelocityFeatures-VersionInfo.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    uint16_t ReleaseInfo::Major()
    {
        return GetVersionInfo().Release.Major;
    }
    uint16_t ReleaseInfo::Minor()
    {
        return GetVersionInfo().Release.Minor;
    }
    uint16_t ReleaseInfo::Patch()
    {
        return GetVersionInfo().Release.Patch;
    }
    hstring ReleaseInfo::VersionTag()
    {
        return GetVersionInfo().Release.VersionTag;
    }
    hstring ReleaseInfo::AsString()
    {
        WCHAR s[64]{};

        const auto& release{ GetVersionInfo().Release };
        PCWSTR versionTag{ release.VersionTag };
        if (versionTag && (versionTag[0] != L'\0'))
        {
            THROW_IF_FAILED(StringCchPrintfW(s, ARRAYSIZE(s), L"%hu.%hu-%s", release.Major, release.Minor, versionTag));
        }
        else
        {
            THROW_IF_FAILED(StringCchPrintfW(s, ARRAYSIZE(s), L"%hu.%hu.%hu", release.Major, release.Minor, release.Patch));
        }
        return winrt::hstring{ s };
    }

    const ::Microsoft::WindowsAppSDK::VersionInfo& ReleaseInfo::GetVersionInfo()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::Feature_VersionInfoAPI::IsEnabled());

        const ::Microsoft::WindowsAppSDK::VersionInfo* versionInfo{ ::Microsoft::WindowsAppSDK::GetVersionInfo() };
        return *versionInfo;
    }
}
