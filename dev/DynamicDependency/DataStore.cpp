// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "DataStore.h"

#include "DynamicDependencyDataStore_h.h"
#include "utf8.h"
#include "winrt_msixdynamicdepednency.h"

#include <wil/winrt.h>

MddCore::PackageDependency MddCore::DataStore::Load(PCWSTR packageDependencyId)
{
    auto path{ GetDataStorePath() };
    path /= L"DynamicDependency";
    auto filename{ path / (std::wstring(packageDependencyId) + DataStore::fileExtension) };

    wil::unique_hfile file{ ::CreateFileW(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr) };
    if (!file)
    {
        const auto lastError{ GetLastError() };
        if ((lastError == ERROR_FILE_NOT_FOUND) || (lastError == ERROR_PATH_NOT_FOUND))
        {
            // Not found
            return PackageDependency();
        }
        THROW_WIN32(lastError);
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
    std::unique_ptr<char[]> bufferUtf8{ new char[bufferSize] };

    DWORD bytesRead{};
    THROW_IF_WIN32_BOOL_FALSE(::ReadFile(file.get(), bufferUtf8.get(), bufferSize, &bytesRead, nullptr));
    file.reset();
    bufferUtf8[bytesRead] = '\0';
    auto json{ bufferUtf8.get() };

    return MddCore::PackageDependency::FromJSON(json);
}

void MddCore::DataStore::Save(const MddCore::PackageDependency& packageDependency)
{
    // Package depednencies with LifetimeKind.Process are never saved to disk. They live in memory and end with the process
    if (packageDependency.LifetimeKind() == MddPackageDependencyLifetimeKind::Process)
    {
        return;
    }

    auto json{ packageDependency.ToJSONUtf8() };

    auto path{ GetDataStorePath() };
    path /= L"DynamicDependency";
    std::filesystem::create_directory(path);

    auto filename{ path / (packageDependency.Id() + DataStore::fileExtension) };

    wil::unique_hfile file{ ::CreateFileW(filename.c_str(), GENERIC_WRITE, FILE_SHARE_DELETE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) };
    if (!file)
    {
        THROW_HR_MSG(HRESULT_FROM_WIN32(GetLastError()), "%ls", filename.c_str());
    }

    DWORD bytesWritten{};
    THROW_IF_WIN32_BOOL_FALSE_MSG(::WriteFile(file.get(), json.c_str(), static_cast<DWORD>(json.length()), &bytesWritten, nullptr), "%ls", filename.c_str());
}

void MddCore::DataStore::Delete(PCWSTR packageDependencyId)
{
    auto path{ GetDataStorePath() };
    path /= packageDependencyId;

    DeleteFileIfExists(path.c_str());;
}

void MddCore::DataStore::DeleteFileIfExists(PCWSTR filename)
{
    if (!::DeleteFileW(filename))
    {
        auto const lastError{ GetLastError() };
        if ((lastError != ERROR_FILE_NOT_FOUND) && (lastError != ERROR_PATH_NOT_FOUND))
        {
            THROW_HR_MSG(HRESULT_FROM_WIN32(lastError), "Error %d deleting file %ls", lastError, filename);
        }
    }
}

std::filesystem::path MddCore::DataStore::GetDataStorePath()
{
    wil::com_ptr<IUnknown> dataStore_iunknown{ wil::CoCreateInstance<DynamicDependencyDataStore, IDynamicDependencyDataStore>(CLSCTX_LOCAL_SERVER) };
    auto dataStore{ dataStore_iunknown.query<IDynamicDependencyDataStore>() };

    wil::com_ptr<IUnknown> applicationData_iunknown;
    THROW_IF_FAILED(dataStore->GetApplicationData(applicationData_iunknown.addressof()));

    auto applicationData{ winrt::convert_from_abi<winrt::Windows::Storage::ApplicationData>(applicationData_iunknown.get()) };

    return std::filesystem::path(applicationData.LocalFolder().Path().c_str());
}
