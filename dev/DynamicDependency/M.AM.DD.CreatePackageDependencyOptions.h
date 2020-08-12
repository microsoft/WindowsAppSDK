// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions.g.h"

#include "winrt_namespaces.h"

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    struct CreatePackageDependencyOptions : CreatePackageDependencyOptionsT<CreatePackageDependencyOptions>
    {
        CreatePackageDependencyOptions() = default;

        winrt::PackageDependencyProcessorArchitectures Architectures();
        void Architectures(Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures const& value);
        bool VerifyDependencyResolution();
        void VerifyDependencyResolution(bool value);
        winrt::PackageDependencyLifetimeArtifactKind LifetimeArtifactKind();
        void LifetimeArtifactKind(Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind const& value);
        hstring LifetimeArtifact();
        void LifetimeArtifact(hstring const& value);

    private:
        winrt::PackageDependencyProcessorArchitectures m_architectures = winrt::PackageDependencyProcessorArchitectures::None;
        bool m_verifyDependencyResolution = false;
        winrt::PackageDependencyLifetimeArtifactKind m_lifetimeArtifactKind = winrt::PackageDependencyLifetimeArtifactKind::Process;
        hstring m_lifetimeArtifact;
    };
}
namespace winrt::Microsoft::ApplicationModel::DynamicDependency::factory_implementation
{
    struct CreatePackageDependencyOptions : CreatePackageDependencyOptionsT<CreatePackageDependencyOptions, implementation::CreatePackageDependencyOptions>
    {
    };
}
