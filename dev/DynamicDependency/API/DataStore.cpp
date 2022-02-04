// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "DataStore.h"

#include "DynamicDependencyDataStore_h.h"
#include "winrt_msixdynamicdependency.h"

#include <wil/winrt.h>

#include <shlobj.h>

MddCore::PackageDependency MddCore::DataStore::Load(PCWSTR packageDependencyId)
{
    std::filesystem::path relativeFilename{ L"DynamicDependency" };
    relativeFilename /= std::wstring(packageDependencyId) + DataStore::fileExtension;

    auto filename{ GetDataStorePathForUser() };
    filename /= relativeFilename;
    wil::unique_hfile file{ OpenFileIfExists(filename.c_str()) };
    if (!file)
    {
        filename = GetDataStorePathForSystem();
        filename /= relativeFilename;
        file.reset(OpenFileIfExists(filename.c_str()));
        if (!file)
        {
            // Not found
            return PackageDependency();
        }
    }

    LARGE_INTEGER fileSize{};
    THROW_IF_WIN32_BOOL_FALSE(::GetFileSizeEx(file.get(), &fileSize));
    const auto dataSize{ fileSize.QuadPart };
    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), dataSize > INT32_MAX);
    if (dataSize == 0)
    {
        // 0-byte file is invalid. Perhaps power was lost when written but before flushed?
        // 'Fix' it i.e. delete it and report not-found
        file.reset();
        std::filesystem::remove(filename);
        return PackageDependency();
    }

    const auto bufferSize{ static_cast<DWORD>(dataSize) + 1 };
    std::unique_ptr<char[]> bufferUtf8{ std::make_unique<char[]>(bufferSize) };

    DWORD bytesRead{};
    THROW_IF_WIN32_BOOL_FALSE(::ReadFile(file.get(), bufferUtf8.get(), bufferSize, &bytesRead, nullptr));
    file.reset();
    bufferUtf8[bytesRead] = '\0';
    auto json{ bufferUtf8.get() };

    return MddCore::PackageDependency::FromJSON(json);
}

void MddCore::DataStore::Save(
    const MddCore::PackageDependency& packageDependency,
    const MddCreatePackageDependencyOptions options)
{
    // Package depednencies with LifetimeKind.Process are never saved to disk. They live in memory and end with the process
    if (packageDependency.LifetimeKind() == MddPackageDependencyLifetimeKind::Process)
    {
        return;
    }

    auto json{ packageDependency.ToJSONUtf8() };

    auto path{ GetDataStorePath(options) };
    path /= L"DynamicDependency";
    std::filesystem::create_directory(path);

    auto filename{ path / (packageDependency.Id() + DataStore::fileExtension) };

    wil::unique_hfile file{ ::CreateFileW(filename.c_str(), GENERIC_WRITE, FILE_SHARE_DELETE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) };
    if (!file)
    {
        THROW_LAST_ERROR_MSG("%ls", filename.c_str());
    }

    DWORD bytesWritten{};
    THROW_IF_WIN32_BOOL_FALSE_MSG(::WriteFile(file.get(), json.c_str(), static_cast<DWORD>(json.length()), &bytesWritten, nullptr), "%ls", filename.c_str());
}

void MddCore::DataStore::Delete(PCWSTR packageDependencyId)
{
    std::filesystem::path relativeFilename{ L"DynamicDependency" };
    relativeFilename /= std::wstring(packageDependencyId) + DataStore::fileExtension;

    auto filename{ GetDataStorePathForUser() };
    filename /= relativeFilename;
    if (!DeleteFileIfExists(filename.c_str()))
    {
        filename = GetDataStorePathForSystem();
        filename /= relativeFilename;
        DeleteFileIfExists(filename.c_str());
    }
}

bool MddCore::DataStore::DeleteFileIfExists(PCWSTR filename)
{
    if (!::DeleteFileW(filename))
    {
        auto const lastError{ GetLastError() };
        if ((lastError == ERROR_FILE_NOT_FOUND) || (lastError == ERROR_PATH_NOT_FOUND))
        {
            return false;
        }
        THROW_HR_MSG(HRESULT_FROM_WIN32(lastError), "Error %d deleting file %ls", lastError, filename);
    }
    return true;
}

HANDLE MddCore::DataStore::OpenFileIfExists(
    PCWSTR filename)
{
    wil::unique_hfile file{ ::CreateFileW(filename, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr) };
    if (!file)
    {
        const auto lastError{ GetLastError() };
        if ((lastError == ERROR_FILE_NOT_FOUND) || (lastError == ERROR_PATH_NOT_FOUND))
        {
            return nullptr;
        }
        THROW_WIN32_MSG(lastError, "Error %d opening file %ls", lastError, filename);
    }
    return file.release();
}

std::filesystem::path MddCore::DataStore::GetDataStorePath(const MddCreatePackageDependencyOptions options)
{
    if (WI_IsFlagSet(options, MddCreatePackageDependencyOptions::ScopeIsSystem))
    {
        return GetDataStorePathForSystem();
    }
    else
    {
        return GetDataStorePathForUser();
    }
}

std::filesystem::path MddCore::DataStore::GetDataStorePathForSystem()
{
    wil::unique_cotaskmem_ptr<WCHAR[]> folderPath;
    THROW_IF_FAILED(SHGetKnownFolderPath(FOLDERID_ProgramData, 0, nullptr, wil::out_param(folderPath)));

    std::filesystem::path path{ folderPath.get() };
    path /= L"Microsoft";
    return path;
}

std::filesystem::path MddCore::DataStore::GetDataStorePathForUser()
{
    // AppContainer processes MUST use the PackagedCOM data store.
    // MediumIL can go either way so we'll favor ApplicationDataManager as the more efficient option.
    // Elevated CANNOT use PackagedCOM so MUST use AppliccationDataManager.
    if (wil::get_token_is_app_container())
    {
        return GetDataStorePathForUserViaCOMDataStore();
    }
    else
    {
        return GetDataStorePathForUserViaApplicationDataManager();
    }
}

std::filesystem::path MddCore::DataStore::GetDataStorePathForUserViaCOMDataStore()
{
    wil::com_ptr<IDynamicDependencyDataStore> dataStore{ wil::CoCreateInstance<DynamicDependencyDataStore, IDynamicDependencyDataStore>(CLSCTX_LOCAL_SERVER) };

    wil::com_ptr<IUnknown> applicationData_iunknown;
    THROW_IF_FAILED(dataStore->GetApplicationData(applicationData_iunknown.addressof()));

    auto applicationData{ winrt::convert_from_abi<winrt::Windows::Storage::ApplicationData>(applicationData_iunknown.get()) };

    return std::filesystem::path(applicationData.LocalFolder().Path().c_str());
}

std::filesystem::path MddCore::DataStore::GetDataStorePathForUserViaApplicationDataManager()
{
    static winrt::hstring mainPackageFamilyName{ GetWindowsAppRuntimeMainPackageFamilyName().c_str() };
    auto applicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(mainPackageFamilyName) };

    return std::filesystem::path(applicationData.LocalFolder().Path().c_str());
}

std::wstring MddCore::DataStore::GetWindowsAppRuntimeMainPackageFamilyName()
{
    const UINT32 flags{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    uint32_t packageInfosCount{};
    const PACKAGE_INFO* packageInfos{};
    wil::unique_cotaskmem_ptr<BYTE[]> buffer;
    THROW_IF_FAILED(::AppModel::PackageGraph::GetCurrentPackageGraph(flags, packageInfosCount, packageInfos, buffer));
    for (uint32_t index=0; index < packageInfosCount; ++index)
    {
        // Check the PublisherId
        const auto& packageInfo{ packageInfos[index] };
        const auto& packageId{ packageInfo.packageId };
        const auto packagePublisherId{ packageId.publisherId };
        PCWSTR c_windowsAppRuntimePublisherId{ L"8wekyb3d8bbwe" };
        if (CompareStringOrdinal(packagePublisherId, -1, c_windowsAppRuntimePublisherId, -1, TRUE) != CSTR_EQUAL)
        {
            continue;
        }

        // Framework package's name in the package graph is Microsoft.WindowsAppRuntime.Main.<major>.<minor>
        const auto packageName{ packageId.name };
        const auto packageNameLength{ wcslen(packageName) };
        PCWSTR c_windowsAppRuntimeNamePrefix{ L"Microsoft.WindowsAppRuntime." };
        const auto c_windowsAppRuntimeNamePrefixLength{ ARRAYSIZE(L"Microsoft.WindowsAppRuntime.") - 1 };
        if (packageNameLength < c_windowsAppRuntimeNamePrefixLength)
        {
            continue;
        }
        if (CompareStringOrdinal(packageName, c_windowsAppRuntimeNamePrefixLength, c_windowsAppRuntimeNamePrefix, c_windowsAppRuntimeNamePrefixLength, TRUE) != CSTR_EQUAL)
        {
            continue;
        }
        PCWSTR packageNameSuffix{ packageName + packageNameLength };

        // Gotcha!
        WCHAR mainPackageFamilyName[PACKAGE_FAMILY_NAME_MAX_LENGTH + 1]{};
        wsprintf(mainPackageFamilyName, L"MicrosoftCorporationII.WindowsAppRuntime.Main.1.0_8wekyb3d8bbwe", packageNameSuffix);
        return std::wstring(mainPackageFamilyName);
    }

    // Didn't find the Windows App SDK framework package in the package graph. Can't determine the package identity!
    THROW_HR(MDD_E_WINDOWSAPPRUNTIME_NOT_IN_PACKAGE_GRAPH);
}
