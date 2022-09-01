// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions.g.h"

#include "winrt_namespaces.h"

namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::implementation
{
    struct CreatePackageDependencyOptions : CreatePackageDependencyOptionsT<CreatePackageDependencyOptions>
    {
        CreatePackageDependencyOptions() = default;

        winrt::PackageDependencyProcessorArchitectures Architectures();
        void Architectures(Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures const& value);
        bool VerifyDependencyResolution();
        void VerifyDependencyResolution(bool value);
        winrt::PackageDependencyLifetimeArtifactKind LifetimeArtifactKind();
        void LifetimeArtifactKind(Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind const& value);
        hstring LifetimeArtifact();
        void LifetimeArtifact(hstring const& value);

    private:
        winrt::PackageDependencyProcessorArchitectures m_architectures{ winrt::PackageDependencyProcessorArchitectures::None };
        bool m_verifyDependencyResolution{};
        winrt::PackageDependencyLifetimeArtifactKind m_lifetimeArtifactKind{ winrt::PackageDependencyLifetimeArtifactKind::Process };
        hstring m_lifetimeArtifact;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::factory_implementation
{
    struct CreatePackageDependencyOptions : CreatePackageDependencyOptionsT<CreatePackageDependencyOptions, implementation::CreatePackageDependencyOptions>
    {
    };
}
