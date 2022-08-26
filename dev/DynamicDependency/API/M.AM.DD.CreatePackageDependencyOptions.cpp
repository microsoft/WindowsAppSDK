// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.AM.DD.CreatePackageDependencyOptions.h"
#include "Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::implementation
{
    winrt::PackageDependencyProcessorArchitectures CreatePackageDependencyOptions::Architectures()
    {
        return m_architectures;
    }
    void CreatePackageDependencyOptions::Architectures(Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures const& value)
    {
        m_architectures = value;
    }

    bool CreatePackageDependencyOptions::VerifyDependencyResolution()
    {
        return m_verifyDependencyResolution;
    }

    void CreatePackageDependencyOptions::VerifyDependencyResolution(bool value)
    {
        m_verifyDependencyResolution = value;
    }

    winrt::PackageDependencyLifetimeArtifactKind CreatePackageDependencyOptions::LifetimeArtifactKind()
    {
        return m_lifetimeArtifactKind;
    }

    void CreatePackageDependencyOptions::LifetimeArtifactKind(Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind const& value)
    {
        m_lifetimeArtifactKind = value;
    }

    hstring CreatePackageDependencyOptions::LifetimeArtifact()
    {
        return m_lifetimeArtifact;
    }

    void CreatePackageDependencyOptions::LifetimeArtifact(hstring const& value)
    {
        m_lifetimeArtifact = value;
    }
}
