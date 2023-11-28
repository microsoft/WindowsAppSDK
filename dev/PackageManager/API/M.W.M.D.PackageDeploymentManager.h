// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageDeploymentManager.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageDeploymentManager : PackageDeploymentManagerT<PackageDeploymentManager>
    {
        PackageDeploymentManager() = default;

        static winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager GetDefault();
        bool IsPackageReady(hstring const& package);
        bool IsPackageByUriReady(winrt::Windows::Foundation::Uri const& packageUri);
        bool IsPackageSetReady(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet);
        bool IsPackageSetReadyById(hstring const& packageSetId);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> EnsurePackageIsReadyAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::EnsureIsReadyOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> EnsurePackageByUriIsReadyAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::EnsureIsReadyOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> EnsurePackageSetIsReadyAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::EnsureIsReadyOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> EnsurePackageSetIsReadyByIdAsync(hstring packageSetId, winrt::Microsoft::Windows::Management::Deployment::EnsureIsReadyOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> AddPackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> AddPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> AddPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> AddPackageSetByIdAsync(hstring packageSetId, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> StagePackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> StagePackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> StagePackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::StagePackageSetOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> StagePackageSetByIdAsync(hstring packageSetId, winrt::Microsoft::Windows::Management::Deployment::StagePackageSetOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RegisterPackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RegisterPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RegisterPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RegisterPackageSetByIdAsync(hstring packageSetId, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageByFullNameAsync(hstring packageFullName, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageByFamilyNameAsync(hstring packageFamilyName, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageSetByIdAsync(hstring packageSetId, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> ResetPackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::ResetPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> ResetPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::ResetPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> ResetPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::ResetPackageSetOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> ResetPackageSetByIdAsync(hstring packageSetId, winrt::Microsoft::Windows::Management::Deployment::ResetPackageSetOptions options);
        bool IsPackageRegistrationPending(hstring const& packageFamilyName);
        bool IsPackageRegistrationPending(hstring const& userSecurityId, hstring const& packageFamilyName);

    private:
        bool IsReady(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSet);
        void Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet) const;
        void Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem) const;
        void EnsureIsReadyAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem, winrt::Microsoft::Windows::Management::Deployment::EnsureIsReadyOptions const& options);
        void AddAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions const& options);
        void AddAsync(winrt::Windows::Foundation::Uri const& packageUri, winrt::Windows::Management::Deployment::AddPackageOptions const& addOptions);
        winrt::Windows::Management::Deployment::PackageVolume ToPackageVolume(winrt::Microsoft::Windows::Management::Deployment::PackageVolume const& packageVolume) const;
        winrt::Windows::Management::Deployment::AddPackageOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions const& options) const;
        winrt::Windows::Management::Deployment::AddPackageOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions const& options) const;
        winrt::Windows::Management::Deployment::StagePackageOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions const& options) const;
        winrt::Windows::Management::Deployment::RegisterPackageOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions const& options) const;
        winrt::Windows::Management::Deployment::RemovalOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions const& options) const;
        winrt::Windows::Management::Deployment::AddPackageOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::EnsureIsReadyOptions const& options) const;

    private:
        winrt::Windows::Management::Deployment::PackageManager m_packageManager;
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageDeploymentManager : PackageDeploymentManagerT<PackageDeploymentManager, implementation::PackageDeploymentManager>
    {
    };
}
