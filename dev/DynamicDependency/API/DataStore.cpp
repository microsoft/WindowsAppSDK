// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "DataStore.h"

#include "DynamicDependencyDataStore_h.h"
#include "winrt_WindowsAppRuntime.h"

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
    const auto& mainPackageFamilyName{ GetWindowsAppRuntimeMainPackageFamilyName() };
    try
    {
        static winrt::hstring mainPackageFamilyNameAsHString{ mainPackageFamilyName.c_str() };
        winrt::Windows::Storage::ApplicationData applicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(mainPackageFamilyNameAsHString) };
        return std::filesystem::path(applicationData.LocalFolder().Path().c_str());
    }
    catch (winrt::hresult_error& e)
    {
        if (e.code() == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
        {
            // If the Main package isn't registered for the caller there'll be no ApplicationData
            // available but we get ERROR_FILE_NOT_FOUND. This may be technically correct but it's
            // routinely misleading as that's the very (most) common NotFound error for Registry
            // APIs. Worse, it'll cause us to throw it as an exception but our higher level
            // machine handles 'NotFound' as ERROR_NOT_FOUND so this would just further confuse
            // folks (and our higher level logic before it even makes it to the caller!). So we'll
            // trap the ERROR_FILE_NOT_FOUND case and map it to our more expected ERROR_NOT_FOUND
            // (and log something so callers can understand).
            THROW_HR_MSG(MDD_E_WINDOWSAPPRUNTIME_DATASTORE_NOT_FOUND, "PackageFamily:%ls", mainPackageFamilyName.c_str());
        }
        throw;
    }
}

std::wstring MddCore::DataStore::GetWindowsAppRuntimeMainPackageFamilyName()
{
    return ::WindowsAppRuntime::VersionInfo::Main::GetPackageFamilyName();
}
