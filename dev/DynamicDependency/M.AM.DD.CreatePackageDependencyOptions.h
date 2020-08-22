// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions.g.h"

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    struct CreatePackageDependencyOptions : CreatePackageDependencyOptionsT<CreatePackageDependencyOptions>
    {
        CreatePackageDependencyOptions() = default;

        Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures Architectures();
        void Architectures(Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures const& value);
        bool VerifyDependencyResolution();
        void VerifyDependencyResolution(bool value);
        Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind LifetimeArtifactKind();
        void LifetimeArtifactKind(Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind const& value);
        hstring LifetimeArtifact();
        void LifetimeArtifact(hstring const& value);

    private:
        Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures m_architectures = Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::None;
        bool m_verifyDependencyResolution = false;
        Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind m_lifetimeArtifactKind = Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process;
        hstring m_lifetimeArtifact;
    };
}
namespace winrt::Microsoft::ApplicationModel::DynamicDependency::factory_implementation
{
    struct CreatePackageDependencyOptions : CreatePackageDependencyOptionsT<CreatePackageDependencyOptions, implementation::CreatePackageDependencyOptions>
    {
    };
}
