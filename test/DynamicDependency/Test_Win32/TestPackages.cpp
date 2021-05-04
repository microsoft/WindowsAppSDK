// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TF = ::Test::FileSystem;

namespace Test::Packages
{
    void AddPackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName)
    {
        if (!IsPackageRegistered(packageFullName))
        {
            AddPackageIfNecessary(packageDirName, packageFullName);
        }
    }

    void AddPackage(PCWSTR packageDirName, PCWSTR packageFullName)
    {
        // Build the target package's .msix filename. It's under the Solution's $(OutDir)
        // NOTE: It could live in ...\Something.msix\... or ...\Something\...
        auto solutionOutDirPath = TF::GetSolutionOutDirPath();
        //
        // Look in ...\Something.msix\...
        auto msix(solutionOutDirPath);
        msix /= packageDirName;
        msix += L".msix";
        msix /= packageDirName;
        msix += L".msix";
        if (!std::filesystem::is_regular_file(msix))
        {
            // Look in ...\Something\...
            msix = solutionOutDirPath;
            msix /= packageDirName;
            msix /= packageDirName;
            msix += L".msix";
            Assert::IsTrue(std::filesystem::is_regular_file(msix));
        }
        auto msixUri = winrt::Windows::Foundation::Uri(msix.c_str());

        // Install the package
        winrt::Windows::Management::Deployment::PackageManager packageManager;
        auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
        auto deploymentResult{ packageManager.AddPackageAsync(msixUri, nullptr, options).get() };
        if (FAILED(deploymentResult.ExtendedErrorCode()))
        {
            auto message = wil::str_printf<wil::unique_process_heap_string>(L"AddPackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str());
            Assert::Fail(message.get());
        }
    }

    void RemovePackageIfNecessary(PCWSTR packageFullName)
    {
        if (IsPackageRegistered(packageFullName))
        {
            RemovePackage(packageFullName);
        }
    }

    void RemovePackage(PCWSTR packageFullName)
    {
        winrt::Windows::Management::Deployment::PackageManager packageManager;
        auto deploymentResult{ packageManager.RemovePackageAsync(packageFullName).get() };
        if (!deploymentResult)
        {
            auto message = wil::str_printf<wil::unique_process_heap_string>(L"RemovePackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str());
            Assert::Fail(message.get());
        }
    }

    bool IsPackageRegistered(PCWSTR packageFullName)
    {
        // Check if the package is registered to the current user via GetPackagePath().
        // GetPackagePath() fails if the package isn't registerd to the current user.
        // Simplest and most portable test across the platforms we might run on
        const auto path = GetPackagePath(packageFullName);
        return !path.empty();
    }

    std::wstring GetPackagePath(PCWSTR packageFullName)
    {
        UINT32 pathLength{};
        const auto rc{ GetPackagePathByFullName(packageFullName, &pathLength, nullptr) };
        if (rc == ERROR_NOT_FOUND)
        {
            return std::wstring();
        }

        Assert::AreEqual(ERROR_INSUFFICIENT_BUFFER, rc);
        auto path = wil::make_process_heap_string(nullptr, pathLength);
        Assert::AreEqual(ERROR_SUCCESS, GetPackagePathByFullName(packageFullName, &pathLength, path.get()));
        return std::wstring(path.get());
    }

    std::wstring GetPackagePath(const std::wstring& packageFullName)
    {
        return GetPackagePath(packageFullName.c_str());
    }

    void AddPackage_DynamicDependencyLifetimeManager()
    {
        AddPackage(Test::Packages::DynamicDependencyLifetimeManager::c_PackageDirName, Test::Packages::DynamicDependencyLifetimeManager::c_PackageFullName);
    }

    void RemovePackage_DynamicDependencyLifetimeManager()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::DynamicDependencyLifetimeManager::c_PackageFullName);
    }

    void AddPackage_ProjectReunionFramework()
    {
        AddPackage(Test::Packages::ProjectReunionFramework::c_PackageDirName, Test::Packages::ProjectReunionFramework::c_PackageFullName);
    }

    void RemovePackage_ProjectReunionFramework()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::ProjectReunionFramework::c_PackageFullName);
    }

    void AddPackage_FrameworkMathAdd()
    {
        AddPackage(Test::Packages::FrameworkMathAdd::c_PackageDirName, Test::Packages::FrameworkMathAdd::c_PackageFullName);
    }

    void RemovePackage_FrameworkMathAdd()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::FrameworkMathAdd::c_PackageFullName);
    }

    void AddPackage_FrameworkMathMultiply()
    {
        AddPackage(Test::Packages::FrameworkMathMultiply::c_PackageDirName, Test::Packages::FrameworkMathMultiply::c_PackageFullName);
    }

    void RemovePackage_FrameworkMathMultiply()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::FrameworkMathMultiply::c_PackageFullName);
    }

    void AddPackage_DynamicDependencyDataStore()
    {
        AddPackage(Test::Packages::DynamicDependencyDataStore::c_PackageDirName, Test::Packages::DynamicDependencyDataStore::c_PackageFullName);
    }

    void RemovePackage_DynamicDependencyDataStore()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::DynamicDependencyDataStore::c_PackageFullName);
    }

    std::filesystem::path GetProjectReunionFrameworkMsixPath()
    {
        // Determine the location of ProjectReunion's Framework's msix. See GetSolutionOutDirPath() for more details.
        auto path = TF::GetSolutionOutDirPath();
        path /= L"Microsoft.ProjectReunion.Framework";
        path /= L"Microsoft.ProjectReunion.Framework.msix";
        return path;
    }
}
