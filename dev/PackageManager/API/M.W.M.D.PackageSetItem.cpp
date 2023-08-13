// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageSetItem.h"
#include "Microsoft.Windows.Management.Deployment.PackageSetItem.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    hstring PackageSetItem::Id()
    {
        return m_id;
    }
    void PackageSetItem::Id(hstring const& value)
    {
        m_id = value;
    }
    hstring PackageSetItem::PackageFamilyName()
    {
        return m_packageFamilyName;
    }
    void PackageSetItem::PackageFamilyName(hstring const& value)
    {
        m_packageFamilyName = value;
    }
    winrt::Windows::ApplicationModel::PackageVersion PackageSetItem::MinVersion()
    {
        return m_minVersion;
    }
    void PackageSetItem::MinVersion(winrt::Windows::ApplicationModel::PackageVersion const& value)
    {
        m_minVersion = value;
    }
    winrt::Windows::Foundation::Uri PackageSetItem::PackageUri()
    {
        return m_packageUri;
    }
    void PackageSetItem::PackageUri(winrt::Windows::Foundation::Uri const& value)
    {
        m_packageUri = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel PackageSetItem::DeploymentProcessingModel()
    {
        return m_deploymentProcessingModel;
    }
    void PackageSetItem::DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value)
    {
        m_deploymentProcessingModel = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority PackageSetItem::DeploymentPriority()
    {
        return m_deploymentPriority;
    }
    void PackageSetItem::DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value)
    {
        m_deploymentPriority = value;
    }
}
