// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.PackageStatus.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct PackageStatus : PackageStatusT<PackageStatus>
    {
        PackageStatus() = default;

        PackageStatus(winrt::Windows::ApplicationModel::PackageStatus const& packageStatus);
        bool IsOK();
        bool NotAvailable();
        bool PackageOffline();
        bool DataOffline();
        bool Disabled();
        bool NeedsRemediation();
        bool LicenseIssue();
        bool Modified();
        bool Tampered();
        bool DependencyIssue();
        bool Servicing();
        bool DeploymentInProgress();

    private:
        winrt::Windows::ApplicationModel::PackageStatus m_packageStatus;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct PackageStatus : PackageStatusT<PackageStatus, implementation::PackageStatus>
    {
    };
}
