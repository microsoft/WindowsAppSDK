// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace TF = ::Test::FileSystem;

namespace Test::Packages
{
    void AddPackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName)
    {
        if (!IsPackageRegistered(packageFullName))
        {
            AddPackage(packageDirName, packageFullName);
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
            VERIFY_IS_TRUE(std::filesystem::is_regular_file(msix));
        }
        auto msixUri = winrt::Windows::Foundation::Uri(msix.c_str());

        // Install the package
        winrt::Windows::Management::Deployment::PackageManager packageManager;
        auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
        auto deploymentResult{ packageManager.AddPackageAsync(msixUri, nullptr, options).get() };
        if (FAILED(deploymentResult.ExtendedErrorCode()))
        {
            auto message = wil::str_printf<wil::unique_process_heap_string>(L"AddPackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode().value, deploymentResult.ErrorText().c_str());
            VERIFY_FAIL(message.get());
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
            auto message = wil::str_printf<wil::unique_process_heap_string>(L"RemovePackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode().value, deploymentResult.ErrorText().c_str());
            VERIFY_FAIL(message.get());
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

        VERIFY_ARE_EQUAL(ERROR_INSUFFICIENT_BUFFER, rc);
        auto path = wil::make_process_heap_string(nullptr, pathLength);
        VERIFY_ARE_EQUAL(ERROR_SUCCESS, GetPackagePathByFullName(packageFullName, &pathLength, path.get()));
        return std::wstring(path.get());
    }

    std::wstring GetPackagePath(const std::wstring& packageFullName)
    {
        return GetPackagePath(packageFullName.c_str());
    }

    winrt::hstring GetPackagePath(const winrt::hstring& packageFullName)
    {
        return winrt::hstring{ GetPackagePath(packageFullName.c_str()) };
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

    void AddPackageIfNecessary_DynamicDependencyLifetimeManagerGC1000()
    {
        AddPackageIfNecessary(Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageDirName, Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageFullName);
    }

    void AddPackage_DynamicDependencyLifetimeManagerGC1000()
    {
        AddPackage(Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageDirName, Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageFullName);
    }

    void RemovePackage_DynamicDependencyLifetimeManagerGC1000()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageFullName);
    }

    void AddPackageIfNecessary_DynamicDependencyLifetimeManagerGC1010()
    {
        AddPackageIfNecessary(Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageDirName, Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageFullName);
    }

    void AddPackage_DynamicDependencyLifetimeManagerGC1010()
    {
        AddPackage(Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageDirName, Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageFullName);
    }

    void RemovePackage_DynamicDependencyLifetimeManagerGC1010()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageFullName);
    }

    void AddPackage_WindowsAppRuntimeFramework()
    {
        AddPackage(Test::Packages::WindowsAppRuntimeFramework::c_PackageDirName, Test::Packages::WindowsAppRuntimeFramework::c_PackageFullName);
    }

    void RemovePackage_WindowsAppRuntimeFramework()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::WindowsAppRuntimeFramework::c_PackageFullName);
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

    void AddPackage_FrameworkWidgets()
    {
        AddPackage(Test::Packages::FrameworkWidgets::c_PackageDirName, Test::Packages::FrameworkWidgets::c_PackageFullName);
    }

    void RemovePackage_FrameworkWidgets()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::FrameworkWidgets::c_PackageFullName);
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

    std::filesystem::path GetWindowsAppRuntimeFrameworkMsixPath()
    {
        // Determine the location of Windows App SDK's Framework's msix. See GetSolutionOutDirPath() for more details.
        auto path = TF::GetSolutionOutDirPath();
        path /= L"Microsoft.WindowsAppRuntime.Framework";
        path /= L"Microsoft.WindowsAppRuntime.Framework.msix";
        return path;
    }
}
