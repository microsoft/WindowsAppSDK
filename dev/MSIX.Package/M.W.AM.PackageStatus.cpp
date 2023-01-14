// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.PackageStatus.h"

#include "Microsoft.Windows.ApplicationModel.PackageStatus.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    PackageStatus::PackageStatus(winrt::Windows::ApplicationModel::PackageStatus const& packageStatus) :
        m_packageStatus(packageStatus)
    {
    }
    bool PackageStatus::IsOK()
    {
        return m_packageStatus.VerifyIsOK();
    }
    bool PackageStatus::NotAvailable()
    {
        return m_packageStatus.NotAvailable();
    }
    bool PackageStatus::PackageOffline()
    {
        return m_packageStatus.PackageOffline();
    }
    bool PackageStatus::DataOffline()
    {
        return m_packageStatus.DataOffline();
    }
    bool PackageStatus::Disabled()
    {
        return m_packageStatus.Disabled();
    }
    bool PackageStatus::NeedsRemediation()
    {
        return m_packageStatus.NeedsRemediation();
    }
    bool PackageStatus::LicenseIssue()
    {
        return m_packageStatus.LicenseIssue();
    }
    bool PackageStatus::Modified()
    {
        return m_packageStatus.Modified();
    }
    bool PackageStatus::Tampered()
    {
        return m_packageStatus.Tampered();
    }
    bool PackageStatus::DependencyIssue()
    {
        return m_packageStatus.DependencyIssue();
    }
    bool PackageStatus::Servicing()
    {
        return m_packageStatus.Servicing();
    }
    bool PackageStatus::DeploymentInProgress()
    {
        return m_packageStatus.DeploymentInProgress();
    }
}
