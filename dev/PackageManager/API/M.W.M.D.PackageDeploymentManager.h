// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageDeploymentManager.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageDeploymentManager : PackageDeploymentManagerT<PackageDeploymentManager>
    {
        static winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager GetDefault();
        static bool IsPackageDeploymentFeatureSupported(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature feature);
        bool IsPackageReady(hstring const& package);
        bool IsPackageReadyByUri(winrt::Windows::Foundation::Uri const& packageUri);
        bool IsPackageSetReady(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet);
        winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus IsPackageReadyOrNewerAvailable(hstring const& package);
        winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus IsPackageReadyOrNewerAvailableByUri(winrt::Windows::Foundation::Uri const& packageUri);
        winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus IsPackageSetReadyOrNewerAvailable(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> EnsurePackageReadyAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> EnsurePackageReadyByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> EnsurePackageSetReadyAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> AddPackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> AddPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> AddPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> StagePackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> StagePackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> StagePackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RegisterPackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RegisterPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RegisterPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageByFullNameAsync(hstring packageFullName, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageByFamilyNameAsync(hstring packageFamilyName, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemovePackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> ResetPackageAsync(hstring package);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> ResetPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> ResetPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RepairPackageAsync(hstring package);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RepairPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RepairPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> ProvisionPackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::ProvisionPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> ProvisionPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::ProvisionPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> ProvisionPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::ProvisionPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> DeprovisionPackageAsync(hstring package);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> DeprovisionPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> DeprovisionPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet);
        bool IsPackageRegistrationPending(hstring const& packageFullName);
        bool IsPackageRegistrationPendingForUser(hstring const& userSecurityId, hstring const& packageFullName);

    private:
        bool IsPackageRegistrationPendingForUser(PSID userSid, PCWSTR packageFullName);

    private:
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> AddPackageByAppInstallerFileAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RegisterPackageByPackageFamilyNameAsync(winrt::hstring const& packageFamilyName, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RegisterPackageByPackageFullNameAsync(winrt::hstring const& packageFullName, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options);

    private:
        winrt::hstring GetUupProductIdIfMsUup(winrt::Windows::Foundation::Uri const& uri) const;
        wil::unique_cotaskmem_array_ptr<wil::unique_cotaskmem_string> GetPackageFullNamesFromUupProductUriIfMsUup(winrt::Windows::Foundation::Uri const& uri) const;
        bool IsReadyByPackageFullName(hstring const& packageFullName);
        bool IsReady(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSet);
        winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus IsReadyOrNewerAvailableByPackageFullName(hstring const& packageFullName);
        winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus IsReadyOrNewerAvailable(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSet);
        void Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet) const;
        void Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem) const;
        HRESULT EnsureReadyAsync(
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem,
            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions const& options,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            const double progressMaxPerPackageSetItem,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);
        HRESULT AddPackage(
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem,
            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions const& options,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            const double progressMaxPerPackageSetItem,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);
        HRESULT AddPackage(
            winrt::Windows::Foundation::Uri const& packageUri,
            winrt::Windows::Management::Deployment::AddPackageOptions const& addOptions,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            const double progressMaxPerPackage,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);
        HRESULT StagePackage(
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem,
            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions const& options,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            const double progressMaxPerPackageSetItem,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);
        HRESULT StagePackage(
            winrt::Windows::Foundation::Uri const& packageUri,
            winrt::Windows::Management::Deployment::StagePackageOptions const& stageOptions,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            const double progressMaxPerPackage,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);
        HRESULT RegisterPackage(
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem,
            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions const& options,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            const double progressMaxPerPackageSetItem,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);
        HRESULT RegisterPackage(
            winrt::Windows::Foundation::Uri const& packageUri,
            winrt::Windows::Management::Deployment::RegisterPackageOptions const& registerOptions,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            const double progressMaxPerPackage,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);
        HRESULT RegisterPackageByPackageFamilyName(
            winrt::hstring const& packageFamilyName,
            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions const& registerOptions,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);
        HRESULT RegisterPackageByPackageFullName(
            winrt::hstring const& packageFullName,
            winrt::Windows::Management::Deployment::RegisterPackageOptions const& registerOptions,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);
        HRESULT RemovePackageByFullName(
            winrt::hstring const& packageFullName,
            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions const& options,
            winrt::Windows::Management::Deployment::RemovalOptions const& removeOptions,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);
        winrt::Windows::Management::Deployment::PackageVolume ToPackageVolume(winrt::Microsoft::Windows::Management::Deployment::PackageVolume const& packageVolume) const;
        winrt::Windows::Management::Deployment::AddPackageOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions const& options) const;
        winrt::Windows::Management::Deployment::StagePackageOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions const& options) const;
        winrt::Windows::Management::Deployment::RegisterPackageOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions const& options) const;
        winrt::Windows::Management::Deployment::RemovalOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions const& options) const;
        winrt::Windows::Management::Deployment::AddPackageOptions ToOptions(winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions const& options) const;
        winrt::Windows::Management::Deployment::DeploymentOptions ToDeploymentOptions(winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions const& options) const;
        static double PercentageToProgress(uint32_t percentage, const double progressMaxPerItem);
        static bool IsUriEndsWith(winrt::Windows::Foundation::Uri const& packageUri, PCWSTR target);

    private:
        static int StringCompareNoCase(PCWSTR left, PCWSTR right)
        {
            return CompareStringOrdinal(left, -1, right, -1, TRUE) - CSTR_EQUAL;
        }
        static bool StringEqualsNoCase(PCWSTR left, PCWSTR right)
        {
            return StringCompareNoCase(left, right) == 0;
        }
        static int StringCompareNoCase(PCWSTR left, const size_t leftLength, PCWSTR right, const size_t rightLength)
        {
            return CompareStringOrdinal(left, static_cast<int>(leftLength), right, static_cast<int>(rightLength), TRUE) - CSTR_EQUAL;
        }
        static int StringEqualsNoCase(PCWSTR left, const size_t leftLength, PCWSTR right, const size_t rightLength)
        {
            return StringCompareNoCase(left, leftLength, right, rightLength) == 0;
        }

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
