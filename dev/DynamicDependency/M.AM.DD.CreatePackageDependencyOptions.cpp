// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "M.AM.DD.CreatePackageDependencyOptions.h"
#include "Microsoft.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions.g.cpp"

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    winrt::PackageDependencyProcessorArchitectures CreatePackageDependencyOptions::Architectures()
    {
        return m_architectures;
    }
    void CreatePackageDependencyOptions::Architectures(Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures const& value)
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

    void CreatePackageDependencyOptions::LifetimeArtifactKind(Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind const& value)
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
