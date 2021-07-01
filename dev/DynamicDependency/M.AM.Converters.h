// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace Microsoft::ApplicationModel::DynamicDependency
{
    inline winrt::Windows::ApplicationModel::PackageVersion ToVersion(PACKAGE_VERSION const& from)
    {
        winrt::Windows::ApplicationModel::PackageVersion to{};
        to.Major = from.Major;
        to.Minor = from.Minor;
        to.Build = from.Build;
        to.Revision = from.Revision;
        return to;
    }

    inline PACKAGE_VERSION ToVersion(winrt::Windows::ApplicationModel::PackageVersion const& from)
    {
        PACKAGE_VERSION to{};
        to.Major = from.Major;
        to.Minor = from.Minor;
        to.Build = from.Build;
        to.Revision = from.Revision;
        return to;
    }

    inline MddPackageDependencyProcessorArchitectures ToArchitectures(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures const& architectures)
    {
        static_assert(static_cast<int32_t>(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::None) == static_cast<int32_t>(MddPackageDependencyProcessorArchitectures::None), "WinRT/MddPackageDependencyProcessorArchitectures::None mismatch");
        static_assert(static_cast<int32_t>(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Neutral) == static_cast<int32_t>(MddPackageDependencyProcessorArchitectures::Neutral), "WinRT/MddPackageDependencyProcessorArchitectures::Neutral mismatch");
        static_assert(static_cast<int32_t>(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86) == static_cast<int32_t>(MddPackageDependencyProcessorArchitectures::X86), "WinRT/MddPackageDependencyProcessorArchitectures::X86 mismatch");
        static_assert(static_cast<int32_t>(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X64) == static_cast<int32_t>(MddPackageDependencyProcessorArchitectures::X64), "WinRT/MddPackageDependencyProcessorArchitectures::X64 mismatch");
        static_assert(static_cast<int32_t>(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm) == static_cast<int32_t>(MddPackageDependencyProcessorArchitectures::Arm), "WinRT/MddPackageDependencyProcessorArchitectures::Arm mismatch");
        static_assert(static_cast<int32_t>(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm64) == static_cast<int32_t>(MddPackageDependencyProcessorArchitectures::Arm64), "WinRT/MddPackageDependencyProcessorArchitectures::Arm64 mismatch");
        static_assert(static_cast<int32_t>(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86OnArm64) == static_cast<int32_t>(MddPackageDependencyProcessorArchitectures::X86OnArm64), "WinRT/MddPackageDependencyProcessorArchitectures::X86OnArm64 mismatch");
        return static_cast<MddPackageDependencyProcessorArchitectures>(architectures);
    }

    inline MddPackageDependencyLifetimeKind ToLifetimeKind(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind const& lifetimeArtifactKind)
    {
        static_assert(static_cast<int32_t>(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process) == static_cast<int32_t>(MddPackageDependencyLifetimeKind::Process), "WinRT/MddPackageDependencyLifetimeKind::Process mismatch");
        static_assert(static_cast<int32_t>(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::FilePath) == static_cast<int32_t>(MddPackageDependencyLifetimeKind::FilePath), "WinRT/MddPackageDependencyLifetimeKind::FilePath mismatch");
        static_assert(static_cast<int32_t>(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::RegistryKey) == static_cast<int32_t>(MddPackageDependencyLifetimeKind::RegistryKey), "WinRT/MddPackageDependencyLifetimeKind::ReistryKey mismatch");
        return static_cast<MddPackageDependencyLifetimeKind>(lifetimeArtifactKind);
    }

    inline MddCreatePackageDependencyOptions ToCreateOptions(winrt::Microsoft::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options, MddCreatePackageDependencyOptions const& defaultValue = MddCreatePackageDependencyOptions::None)
    {
        auto mddOptions{ defaultValue };
        if (!options.VerifyDependencyResolution())
        {
            WI_SetFlag(mddOptions, MddCreatePackageDependencyOptions::DoNotVerifyDependencyResolution);
        }
        return mddOptions;
    }

    inline MddAddPackageDependencyOptions ToAddOptions(winrt::Microsoft::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options)
    {
        auto mddOptions{ MddAddPackageDependencyOptions::None };
        if (options.PrependIfRankCollision())
        {
            WI_SetFlag(mddOptions, MddAddPackageDependencyOptions::PrependIfRankCollision);
        }
        return mddOptions;
    }

    inline winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContextId ToContextId(MDD_PACKAGEDEPENDENCY_CONTEXT context)
    {
        return winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContextId{ static_cast<uint64_t>(reinterpret_cast<INT_PTR>(context)) };
    }

    inline MDD_PACKAGEDEPENDENCY_CONTEXT ToContext(winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContextId contextId)
    {
        return reinterpret_cast<MDD_PACKAGEDEPENDENCY_CONTEXT>(static_cast<INT_PTR>(contextId.Id));
    }
}
