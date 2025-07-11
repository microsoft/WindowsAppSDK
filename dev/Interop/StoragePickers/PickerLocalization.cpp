// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// NOTE: Localization logic is intentionally separated from PickerCommon.cpp to avoid
// MRT Core dependencies in unit tests. Once unit tests are refactored to use component
// packages instead of mocked packages, this can be moved into CaptureParameters method.

#include "pch.h"
#include "PickerLocalization.h"
#include <winrt\base.h>
#include <winrt\Microsoft.Windows.ApplicationModel.Resources.h>
#include <iostream>

// find framework package related code from https://github.com/microsoft/microsoft-ui-xaml/blob/main/src/controls/dev/ResourceHelper/ResourceAccessor.cpp
// and https://github.com/microsoft/microsoft-ui-xaml/blob/main/src/controls/dev/dll/SharedHelpers.cpp

namespace {
    constexpr wchar_t c_reunionPackageNamePrefix[] = L"Microsoft.WindowsAppRuntime";
    constexpr int c_reunionPackageNamePrefixLength = ARRAYSIZE(c_reunionPackageNamePrefix) - 1;

    // Tries to retrieve the current package graph. Will return true if a package graph exists
    // and is non-empty, else false.
    bool TryGetCurrentPackageGraph(
        const std::uint32_t flags,
        std::uint32_t& packageCount,
        const PACKAGE_INFO*& packageGraph,
        std::unique_ptr<BYTE[]>& buffer)
    {
        std::uint32_t bufferLength{};
        LONG rc{ ::GetCurrentPackageInfo(flags, &bufferLength, nullptr, nullptr) };
        if ((rc == APPMODEL_ERROR_NO_PACKAGE) || (rc == ERROR_SUCCESS))
        {
            // No/empty package graph
            return false;
        }
        else if (rc != ERROR_INSUFFICIENT_BUFFER)
        {
            if (FAILED(HRESULT_FROM_WIN32(rc)))
            {
                return false;
            }
        }

        buffer = std::make_unique<BYTE[]>(bufferLength);
        if (SUCCEEDED(HRESULT_FROM_WIN32(::GetCurrentPackageInfo(flags, &bufferLength, buffer.get(), &packageCount))))
        {
            packageGraph = reinterpret_cast<PACKAGE_INFO*>(buffer.get());
            return true;
        }

        return false;
    }

    bool IsInFrameworkPackageImpl(winrt::hstring& frameworkInstallLocation)
    {
        // We could be running in an app that is using WinUI "In-App" (i.e. the WinUI dlls are deployed as part of the app). 
        // Or we could be running in the Project Reunion Framework Package that an app takes a dependency on.
        // We determine if we are in a Framework Package by looking at the App's package dependencies. If the app has a Project Reunion dependency
        // then we must be running in a Framework Package.
        const UINT32 c_filter{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
        std::uint32_t packageCount{};
        const PACKAGE_INFO* packageGraph{};
        std::unique_ptr<BYTE[]> packageBuffer;
        std::cout << "calling is in framework package" << std::endl;
        if (TryGetCurrentPackageGraph(c_filter, packageCount, packageGraph, packageBuffer))
        {
            if (packageGraph)
            {
                for (std::uint32_t index = 0; index < packageCount; index++)
                {
                    const PACKAGE_INFO& packageInfo{ packageGraph[index] };

                    // We use FamilyName here and not DisplayName because DisplayName is a localized string, but FamilyName is a stable identifier.
                    auto packageFamilyName = packageInfo.packageFamilyName;
                    int nameLength{ static_cast<int>(wcslen(packageFamilyName)) };

                    if (nameLength < c_reunionPackageNamePrefixLength)
                    {
                        continue;
                    }

                    if (
                       CompareStringOrdinal(
                           packageFamilyName,
                           c_reunionPackageNamePrefixLength,
                           c_reunionPackageNamePrefix,
                           c_reunionPackageNamePrefixLength,
                           TRUE) == CSTR_EQUAL)
                    {
                        frameworkInstallLocation = winrt::hstring(packageInfo.path);
                        std::cout << "calling is in framework package result true" << std::endl;
                        return true;
                    }
                }
            }
        }
        std::cout << "calling is in framework package result false" << std::endl;
        return false;
    }
}




bool PickerLocalization::IsInFrameworkPackage(winrt::hstring& frameworkPackageInstallLocation)
{
    static winrt::hstring s_frameworkInstallLocation;
    static bool isInFrameworkPackage = IsInFrameworkPackageImpl(s_frameworkInstallLocation);    
    frameworkPackageInstallLocation = s_frameworkInstallLocation;
    return isInFrameworkPackage;
}


const winrt::hstring priFileName = L"Microsoft.WindowsAppRuntime.pri";
winrt::hstring GetPriFilePath()
{
    HMODULE hModule = nullptr;
    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        reinterpret_cast<LPCWSTR>(&GetPriFilePath), &hModule))
    {
        wchar_t path[MAX_PATH];
        if (GetModuleFileNameW(hModule, path, MAX_PATH) > 0)
        {
            // Use std::filesystem to get the parent directory
            std::filesystem::path dllPath(path);
            std::filesystem::path parentDir = dllPath.parent_path();
            // Combine parentDir with Microsoft.WindowsAppRuntime.pri
            auto priFilePath = parentDir / std::wstring{ priFileName };
            auto pathHstring = winrt::hstring{ parentDir.wstring() };
            auto priFilePathHstring = winrt::hstring{ priFilePath.wstring() };
            std::wcout << L"Parent directory: " << pathHstring.c_str() << std::endl;
            std::wcout << L"PRI file path: " << priFilePathHstring.c_str() << std::endl;
            return priFilePathHstring;
        }
    }
    return priFileName;
}

namespace PickerLocalization {
    
    winrt::hstring GetStoragePickersLocalizationText(winrt::hstring key, winrt::hstring fallback)
    {
            //winrt::hstring frameworkInstallLocation{};
            //auto priPath = IsInFrameworkPackage(frameworkInstallLocation)
            //    ? (frameworkInstallLocation + L"\\" + priFileName)
            //    : priFileName;
        static winrt::hstring priPath = GetPriFilePath();
        std::wcout << L"PRI PATH FROM DLL PATH INFER" << priPath.c_str() << std::endl;
        auto manager = winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager(priPath);
        return manager.MainResourceMap().GetValue(key).ValueAsString();
    }
}


