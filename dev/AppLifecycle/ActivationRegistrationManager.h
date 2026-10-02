// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <Microsoft.Windows.AppLifecycle.ActivationRegistrationManager.g.h>

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    // Registration constant values.
    static PCWSTR c_argumentPrefix{ L"----" };
    static PCWSTR c_argumentSuffix{ L":" };
    static PCWSTR c_msProtocolArgumentString{ L"ms-protocol" };
    static PCWSTR c_pushProtocolArgumentString{ L"WindowsAppRuntimePushServer" };
    static PCWSTR c_appNotificationProtocolArgumentString{ L"AppNotificationActivated" };
    static PCWSTR c_runKeyPath{ LR"(Software\Microsoft\Windows\CurrentVersion\Run\)" };

    struct ActivationRegistrationManager
    {
        ActivationRegistrationManager() = default;

        static void RegisterForFileTypeActivation(array_view<hstring const> supportedFileTypes,
            hstring const& logo, hstring const& displayName, array_view<hstring const> supportedVerbs,
            hstring const& exePath);
        static void RegisterForProtocolActivation(hstring const& schemeName,
            hstring const& logo, hstring const& displayName, hstring const& exePath);
        static void RegisterForStartupActivation(hstring const& taskId, hstring const& exePath);

        static void UnregisterForFileTypeActivation(array_view<hstring const> fileTypes,
            hstring const& exePath);
        static void UnregisterForProtocolActivation(hstring const& scheme, hstring const& exePath);
        static void UnregisterForStartupActivation(hstring const& taskId);

    private:
        static void RegisterForProtocolActivationInternal(std::wstring const& schemeName,
            std::wstring const& appUserModelId, std::wstring const& logo, std::wstring const& displayName,
            std::wstring const& exePath);
        static void RegisterEncodedLaunchCommand();
        static void RegisterEncodedLaunchSupport(std::wstring const& appUserModelId, std::wstring const& exePath);
        static void ReportFeatureUsage();
    };
}

namespace winrt::Microsoft::Windows::AppLifecycle::factory_implementation
{
    struct ActivationRegistrationManager : ActivationRegistrationManagerT<ActivationRegistrationManager,
        implementation::ActivationRegistrationManager>
    {
    };
}
