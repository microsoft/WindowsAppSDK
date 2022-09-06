// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "TypeResolution.h"
#include "catalog.h"

#include <wrl.h>

#define METADATA_FILE_EXTENSION L"winmd"
#define METADATA_FILE_PATH_FORMAT L"%s%s."  METADATA_FILE_EXTENSION
#define METADATA_FILE_SEARCH_FORMAT L"%s%s*."  METADATA_FILE_EXTENSION

namespace UndockedRegFreeWinRT
{
    static const UINT32 g_uiMaxTypeName = 512;
    static wil::unique_process_heap_string g_cachedProcessExeDir;

    BOOL CALLBACK GetProcessExeDirInitOnceCallback(
        _Inout_     PINIT_ONCE,
        _Inout_opt_ PVOID,
        _Out_opt_   PVOID*)
    {
        wil::unique_process_heap_string localExePath;
        HRESULT hr = wil::GetModuleFileNameW(nullptr, localExePath);
        if (FAILED_LOG(hr))
        {
            SetLastError(hr);
            return FALSE;
        }

        // Modify the retrieved string to truncate the actual exe name and leave the containing directory path. This API
        // expects a buffer size including the terminating null, so add 1 to the string length.
        hr = PathCchRemoveFileSpec(localExePath.get(), wcslen(localExePath.get()) + 1);
        if (FAILED_LOG(hr))
        {
            SetLastError(hr);
            return FALSE;
        }

        g_cachedProcessExeDir = std::move(localExePath);
        return TRUE;
    }

    // Returned string is cached globally, and should not be freed by the caller.
    HRESULT GetProcessExeDir(PCWSTR* path)
    {
        *path = nullptr;
        static INIT_ONCE ProcessExeDirInitOnce = INIT_ONCE_STATIC_INIT;

        RETURN_IF_WIN32_BOOL_FALSE(InitOnceExecuteOnce(&ProcessExeDirInitOnce, GetProcessExeDirInitOnceCallback, nullptr, nullptr));

        // The cache has been successfully populated by the InitOnce, so we can just use it directly.
        *path = g_cachedProcessExeDir.get();
        return S_OK;
    }

    HRESULT FindTypeInMetaDataFile(
        _In_ IMetaDataDispenserEx* pMetaDataDispenser,
        _In_ PCWSTR pszFullName,
        _In_ PCWSTR pszCandidateFilePath,
        _In_ TYPE_RESOLUTION_OPTIONS resolutionOptions,
        _COM_Outptr_opt_result_maybenull_ IMetaDataImport2** ppMetaDataImport,
        _Out_opt_ mdTypeDef* pmdTypeDef)
    {
        HRESULT hr = S_OK;
        Microsoft::WRL::ComPtr<IMetaDataImport2> spMetaDataImport;
        MetaDataImportersLRUCache* pMetaDataImporterCache = MetaDataImportersLRUCache::GetMetaDataImportersLRUCacheInstance();
        if (pMetaDataImporterCache != nullptr)
        {
            hr = pMetaDataImporterCache->GetMetaDataImporter(
                pMetaDataDispenser,
                pszCandidateFilePath,
                &spMetaDataImport);
        }
        else
        {
            hr = E_OUTOFMEMORY;
        }

        if (SUCCEEDED(hr))
        {
            const size_t cFullName = wcslen(pszFullName);
            wchar_t pszRetrievedName[g_uiMaxTypeName];
            HCORENUM hEnum = nullptr;
            mdTypeDef rgTypeDefs[32];
            ULONG cTypeDefs;
            DWORD dwTypeDefProps;
            hr = RO_E_METADATA_NAME_NOT_FOUND;

            if (TRO_RESOLVE_TYPE & resolutionOptions)
            {
                hr = spMetaDataImport->FindTypeDefByName(pszFullName, mdTokenNil, &rgTypeDefs[0]);
                if (SUCCEEDED(hr))
                {
                    //  Check to confirm that the type we just found is a
                    //  winrt type.  If it is, we're good, otherwise we
                    //  want to fail with RO_E_INVALID_METADATA_FILE.
                    hr = spMetaDataImport->GetTypeDefProps(rgTypeDefs[0], nullptr, 0, nullptr, &dwTypeDefProps, nullptr);
                    if (SUCCEEDED(hr))
                    {
                        //  If we found the type but it's not a winrt type,
                        //  it's an error.
                        //
                        //  If the type is public, than the metadata file
                        //  is corrupt (all public types in a winrt file
                        //  must be tdWindowsRuntime).  If the type is
                        //  private, then we just want to report that the
                        //  type wasn't found.
                        if (!IsTdWindowsRuntime(dwTypeDefProps))
                        {
                            if (IsTdPublic(dwTypeDefProps))
                            {
                                hr = RO_E_INVALID_METADATA_FILE;
                            }
                            else
                            {
                                hr = RO_E_METADATA_NAME_NOT_FOUND;
                            }
                        }
                    }
                    else
                    {
                        hr = RO_E_INVALID_METADATA_FILE;
                    }
                    if (SUCCEEDED(hr))
                    {
                        if (pmdTypeDef != nullptr)
                        {
                            *pmdTypeDef = rgTypeDefs[0];
                        }
                        if (ppMetaDataImport != nullptr)
                        {
                            *ppMetaDataImport = spMetaDataImport.Detach();
                        }
                    }
                }
                else if (hr == CLDB_E_RECORD_NOTFOUND)
                {
                    hr = RO_E_METADATA_NAME_NOT_FOUND;
                }
            }

            if ((hr == RO_E_METADATA_NAME_NOT_FOUND) &&
                (TRO_RESOLVE_NAMESPACE & resolutionOptions))
            {
                // Check whether the name is a namespace rather than a type.
                do
                {
                    hr = spMetaDataImport->EnumTypeDefs(
                        &hEnum,
                        rgTypeDefs,
                        ARRAYSIZE(rgTypeDefs),
                        &cTypeDefs);

                    if (hr == S_OK)
                    {
                        for (UINT32 iTokenIndex = 0; iTokenIndex < cTypeDefs; ++iTokenIndex)
                        {
                            hr = spMetaDataImport->GetTypeDefProps(
                                rgTypeDefs[iTokenIndex],
                                pszRetrievedName,
                                ARRAYSIZE(pszRetrievedName),
                                nullptr,
                                &dwTypeDefProps,
                                nullptr);

                            if (FAILED(hr))
                            {
                                break;
                            }

                            hr = RO_E_METADATA_NAME_NOT_FOUND;

                            // Only consider windows runtime types when
                            // trying to determine if the name is a
                            // namespace.
                            if (IsTdWindowsRuntime(dwTypeDefProps) && (wcslen(pszRetrievedName) > cFullName))
                            {
                                if ((wcsncmp(pszRetrievedName, pszFullName, cFullName) == 0) &&
                                    (pszRetrievedName[cFullName] == L'.'))
                                {
                                    hr = RO_E_METADATA_NAME_IS_NAMESPACE;
                                    break;
                                }
                            }
                        }
                    }
                } while (hr == RO_E_METADATA_NAME_NOT_FOUND);

                // There were no more tokens to enumerate, but the type was still not found.
                if (hr == S_FALSE)
                {
                    hr = RO_E_METADATA_NAME_NOT_FOUND;
                }

                if (hEnum != nullptr)
                {
                    spMetaDataImport->CloseEnum(hEnum);
                    hEnum = nullptr;
                }
            }
        }
        return hr;
    }

    HRESULT FindTypeInDirectory(
        _In_ IMetaDataDispenserEx* pMetaDataDispenser,
        _In_ PCWSTR pszFullName,
        _In_ PCWSTR pszDirectoryPath,
        _Out_opt_ HSTRING* phstrMetaDataFilePath,
        _COM_Outptr_opt_result_maybenull_ IMetaDataImport2** ppMetaDataImport,
        _Out_opt_ mdTypeDef* pmdTypeDef)
    {
        wchar_t szCandidateFileName[MAX_PATH + 1]{};
        HRESULT hr{ StringCchCopy(szCandidateFileName, ARRAYSIZE(szCandidateFileName), pszFullName) };
        if (SUCCEEDED(hr))
        {
            // To resolve type SomeNamespace.B.C, first check if SomeNamespace.B.C is a type or
            // a namespace in the metadata files in the directory in this order:
            // 1. SomeNamespace.B.C.WinMD
            // 2. SomeNamespace.B.WinMD
            // 3. SomeNamespace.WinMD
            wchar_t szCandidateFilePath[MAX_PATH + 1]{};
            PWSTR pszLastDot{};
            do
            {
                pszLastDot = nullptr;

                hr = StringCchPrintfExW(szCandidateFilePath, ARRAYSIZE(szCandidateFilePath),
                                        nullptr, nullptr, 0, METADATA_FILE_PATH_FORMAT,
                                        pszDirectoryPath, szCandidateFileName);
                if (SUCCEEDED(hr))
                {
                    hr = FindTypeInMetaDataFile(pMetaDataDispenser, pszFullName, szCandidateFilePath,
                                                TRO_RESOLVE_TYPE_AND_NAMESPACE, ppMetaDataImport, pmdTypeDef);
                    if (SUCCEEDED(hr))
                    {
                        if (phstrMetaDataFilePath != nullptr)
                        {
                            hr = WindowsCreateString(szCandidateFilePath,
                                                     static_cast<UINT32>(wcslen(szCandidateFilePath)),
                                                     phstrMetaDataFilePath);
                        }
                        break;
                    }
                }

                hr = RO_E_METADATA_NAME_NOT_FOUND;
                pszLastDot = wcsrchr(szCandidateFileName, '.');
                if (pszLastDot != nullptr)
                {
                    *pszLastDot = '\0';
                }
            } while (pszLastDot != nullptr);

            // If name was not found when searching in the "upward direction", then
            // the name might be a namespace name in a down-level file.
            if (hr == RO_E_METADATA_NAME_NOT_FOUND)
            {
                wchar_t szFilePathSearchTemplate[MAX_PATH + 1]{};
                hr = StringCchPrintfExW(szFilePathSearchTemplate, ARRAYSIZE(szFilePathSearchTemplate), nullptr,
                                        nullptr, 0, METADATA_FILE_SEARCH_FORMAT, pszDirectoryPath, pszFullName);
                if (SUCCEEDED(hr))
                {
                    // Search in all files in the directory whose name begin with the input string.
                    WIN32_FIND_DATA fd{};
                    HANDLE hFindFile{ FindFirstFile(szFilePathSearchTemplate, &fd) };
                    if (hFindFile != INVALID_HANDLE_VALUE)
                    {
                        do
                        {
                            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                            {
                                continue;
                            }

                            PWSTR pszFilePathPart{ szCandidateFilePath };
                            size_t cchRemaining{ ARRAYSIZE(szCandidateFilePath) };
                            hr = StringCchCopyExW(pszFilePathPart, cchRemaining, pszDirectoryPath,
                                                  &pszFilePathPart, &cchRemaining, 0);
                            if (SUCCEEDED(hr))
                            {
                                hr = StringCchCopyExW(pszFilePathPart, cchRemaining, fd.cFileName,
                                                      &pszFilePathPart, &cchRemaining, 0);
                                if (SUCCEEDED(hr))
                                {
                                    hr = FindTypeInMetaDataFile(pMetaDataDispenser, pszFullName, szCandidateFilePath,
                                                                TRO_RESOLVE_NAMESPACE, ppMetaDataImport, pmdTypeDef);
                                    if (hr == S_OK)
                                    {
                                        hr = E_UNEXPECTED;
                                        break;
                                    }
                                    else if (hr == RO_E_METADATA_NAME_IS_NAMESPACE)
                                    {
                                        break;
                                    }
                                }
                            }
                        } while (FindNextFile(hFindFile, &fd));

                        FindClose(hFindFile);
                    }
                    else
                    {
                        hr = RO_E_METADATA_NAME_NOT_FOUND;
                    }
                }
            }
        }

        if (hr == STRSAFE_E_INSUFFICIENT_BUFFER)
        {
            return RO_E_METADATA_NAME_NOT_FOUND;
        }
        RETURN_HR(hr);
    }

    HRESULT FindTypeInDirectoryWithNormalization(
        _In_ IMetaDataDispenserEx* pMetaDataDispenser,
        _In_ PCWSTR pszFullName,
        _In_ PCWSTR pszDirectoryPath,
        _Out_opt_ HSTRING* phstrMetaDataFilePath,
        _COM_Outptr_opt_result_maybenull_ IMetaDataImport2** ppMetaDataImport,
        _Out_opt_ mdTypeDef* pmdTypeDef)
    {
        wchar_t pszPackagePath[MAX_PATH + 1]{};
        PWSTR pszPackagePathWritePtr{ pszPackagePath };
        size_t cchPackagePathRemaining{ ARRAYSIZE(pszPackagePath) };
        RETURN_IF_FAILED(StringCchCopyExW(pszPackagePath, ARRAYSIZE(pszPackagePath),
            pszDirectoryPath, &pszPackagePathWritePtr, &cchPackagePathRemaining, 0));

        // If the path is not terminated by a backslash, then append one.
        if (pszPackagePath[ARRAYSIZE(pszPackagePath) - cchPackagePathRemaining - 1] != L'\\')
        {
            RETURN_IF_FAILED(StringCchCopyExW(pszPackagePathWritePtr, cchPackagePathRemaining,
                L"\\", &pszPackagePathWritePtr, &cchPackagePathRemaining, 0));
        }

        RETURN_IF_FAILED(FindTypeInDirectory(pMetaDataDispenser, pszFullName,
                pszPackagePath, phstrMetaDataFilePath, ppMetaDataImport, pmdTypeDef));

        return S_OK;
    }

    HRESULT ResolveThirdPartyType(
        _In_ IMetaDataDispenserEx* pMetaDataDispenser,
        _In_ PCWSTR pszFullName,
        _Out_opt_ HSTRING* phstrMetaDataFilePath,
        _COM_Outptr_opt_result_maybenull_ IMetaDataImport2** ppMetaDataImport,
        _Out_opt_ mdTypeDef* pmdTypeDef)
    {
        // Walk the package graph looking for the requested metadata
        const uint32_t filter{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_IS_IN_RELATED_SET | PACKAGE_FILTER_DYNAMIC | PACKAGE_FILTER_STATIC };
        uint32_t bufferLength{};
        uint32_t packagesCount{};
        bool processHasStaticPackageGraph{};
        const HRESULT hr{ HRESULT_FROM_WIN32(GetCurrentPackageInfo(filter, &bufferLength, nullptr, &packagesCount)) };
        if (hr == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
        {
            // The process has a package graph. Walk it looking for the requested metadata
            auto buffer{ wil::make_unique_nothrow<BYTE[]>(bufferLength) };
            RETURN_IF_NULL_ALLOC(buffer);
            RETURN_IF_WIN32_ERROR(GetCurrentPackageInfo(filter, &bufferLength, buffer.get(), &packagesCount));
            const auto packageInfos{ reinterpret_cast<PACKAGE_INFO*>(buffer.get()) };
            for (uint32_t index=0; index < packagesCount; ++index)
            {
                const auto& packageInfo{ packageInfos[index] };
                HRESULT hrFindType{ FindTypeInDirectoryWithNormalization(pMetaDataDispenser, pszFullName,
                                packageInfo.path, phstrMetaDataFilePath, ppMetaDataImport, pmdTypeDef) };
                if (SUCCEEDED(hrFindType))
                {
                    return hrFindType;
                }

                // Keep track if we find any Static entries in the package graph
                if (WI_IsFlagSet(packageInfo.flags, PACKAGE_PROPERTY_STATIC))
                {
                    processHasStaticPackageGraph = true;
                }
            }
        }

        // Not found in the package graph.

        // Unpackaged apps may have metadata next to their executable.
        //
        // Packaged apps have metadata in their root directory which is
        // in the package graph and thus already checked.
        //
        // NOTE: Only packaged apps have Static entries in their package graph.
        //       Unpackaged apps have no Static entries in their package graph.
        if (!processHasStaticPackageGraph)
        {
            PCWSTR exeDir{};  // Never freed; owned by process global.
            RETURN_IF_FAILED(GetProcessExeDir(&exeDir));
            const HRESULT hrFindType{ FindTypeInDirectoryWithNormalization(
                pMetaDataDispenser, pszFullName, exeDir,
                phstrMetaDataFilePath, ppMetaDataImport, pmdTypeDef) };
            if (hrFindType == RO_E_METADATA_NAME_NOT_FOUND)
            {
                // For compatibility purposes, if we fail to find the type in the unpackaged location, we should return
                // HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE) instead of a "not found" error. This preserves the
                // behavior that existed before unpackaged type resolution was implemented.
                return HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE);
            }
            RETURN_HR(hrFindType);
        }

        // Not found
        return RO_E_METADATA_NAME_NOT_FOUND;
    }

    //
    // MetaDataImportersLRUCache implementation
    //
    INIT_ONCE MetaDataImportersLRUCache::s_initOnce = INIT_ONCE_STATIC_INIT;
    MetaDataImportersLRUCache* MetaDataImportersLRUCache::s_pMetaDataImportersLRUCacheInstance = nullptr;

    MetaDataImportersLRUCache* MetaDataImportersLRUCache::GetMetaDataImportersLRUCacheInstance()
    {
        BOOL fInitializationSucceeded = InitOnceExecuteOnce(
            &s_initOnce,
            ConstructLRUCacheIfNecessary,
            nullptr,
            nullptr);

        UNREFERENCED_PARAMETER(fInitializationSucceeded);

        return s_pMetaDataImportersLRUCacheInstance;
    }

    // Called via InitOnceExecuteOnce.
    BOOL CALLBACK MetaDataImportersLRUCache::ConstructLRUCacheIfNecessary(
        PINIT_ONCE /*initOnce*/,
        PVOID /*parameter*/,
        PVOID* /*context*/)
    {
        HRESULT hr = S_OK;

        if (s_pMetaDataImportersLRUCacheInstance == nullptr)
        {
            s_pMetaDataImportersLRUCacheInstance = new MetaDataImportersLRUCache();

            if (s_pMetaDataImportersLRUCacheInstance == nullptr)
            {
                hr = E_OUTOFMEMORY;
            }
        }

        return SUCCEEDED(hr);
    }

    HRESULT MetaDataImportersLRUCache::GetMetaDataImporter(
        _In_ IMetaDataDispenserEx* pMetaDataDispenser,
        _In_ PCWSTR pszCandidateFilePath,
        _Outptr_opt_ IMetaDataImport2** ppMetaDataImporter)
    {
        if (ppMetaDataImporter == nullptr)
        {
            return ERROR_BAD_ARGUMENTS;
        }

        HRESULT hr = S_OK;
        *ppMetaDataImporter = nullptr;

        EnterCriticalSection(&_csCacheLock);

        if (IsFilePathCached(pszCandidateFilePath))
        {
            // Get metadata importer from cache.
            *ppMetaDataImporter = _metadataImportersMap[pszCandidateFilePath];
            IMetaDataImport2* value = *ppMetaDataImporter;
            if (value != nullptr)
            {
                value->AddRef();
            }
        }
        else
        {
            // Importer was not found in cache.
            hr = GetNewMetaDataImporter(
                pMetaDataDispenser,
                pszCandidateFilePath,
                ppMetaDataImporter);
        }

        LeaveCriticalSection(&_csCacheLock);

        return hr;
    }

    HRESULT MetaDataImportersLRUCache::GetNewMetaDataImporter(
        _In_ IMetaDataDispenserEx* pMetaDataDispenser,
        _In_ PCWSTR pszCandidateFilePath,
        _Outptr_opt_ IMetaDataImport2** ppMetaDataImporter)
    {
        if (ppMetaDataImporter == nullptr)
        {
            return ERROR_BAD_ARGUMENTS;
        }

        HRESULT hr;

        hr = pMetaDataDispenser->OpenScope(
            pszCandidateFilePath,
            ofReadOnly,
            IID_IMetaDataImport2,
            reinterpret_cast<IUnknown**>(ppMetaDataImporter));

        if (SUCCEEDED(hr))
        {
           _metadataImportersMap.emplace(
                pszCandidateFilePath,
                *ppMetaDataImporter);
           IMetaDataImport2* value = *ppMetaDataImporter;
           if (value != nullptr)
           {
               value->AddRef();
           }
        }

        if (SUCCEEDED(hr))
        {
            hr = AddNewFilePathToList(pszCandidateFilePath);
        }

        return hr;
    }

    HRESULT MetaDataImportersLRUCache::AddNewFilePathToList(PCWSTR pszFilePath)
    {
        HRESULT hr = RemoveLeastRecentlyUsedItemIfListIsFull();

        if (SUCCEEDED(hr))
        {
            // Make room for new element.
            for (int i = g_dwMetaDataImportersLRUCacheSize - 2; i >= 0; i--)
            {
                _arFilePaths[i + 1] = _arFilePaths[i];
            }

            _arFilePaths[0] = AllocateAndCopyString(pszFilePath);

            if (_arFilePaths[0] == nullptr)
            {
                hr = E_OUTOFMEMORY;
            }
        }

        return hr;
    }

    bool MetaDataImportersLRUCache::IsFilePathCached(PCWSTR pszFilePath)
    {
        int filePathIndex = GetFilePathIndex(pszFilePath);

        if (filePathIndex != -1)
        {
            MoveElementToFrontOfList(filePathIndex);
            return true;
        }
        else
        {
            return false;
        }
    }

    int MetaDataImportersLRUCache::GetFilePathIndex(PCWSTR pszFilePath)
    {
        int filePathIndex = -1;

        for (int i = 0; (i < g_dwMetaDataImportersLRUCacheSize) && (_arFilePaths[i] != nullptr); i++)
        {
            if (wcscmp(pszFilePath, _arFilePaths[i]) == 0)
            {
                filePathIndex = i;
                break;
            }
        }

        return filePathIndex;
    }

    void MetaDataImportersLRUCache::MoveElementToFrontOfList(int elementIndex)
    {
        PWSTR pszFoundFilePath = _arFilePaths[elementIndex];

        for (int i = elementIndex - 1; i >= 0; i--)
        {
            _arFilePaths[i + 1] = _arFilePaths[i];
        }

        _arFilePaths[0] = pszFoundFilePath;
    }

    HRESULT MetaDataImportersLRUCache::RemoveLeastRecentlyUsedItemIfListIsFull()
    {
        HRESULT hr = S_OK;
        PWSTR pszLastFilePathInList = _arFilePaths[g_dwMetaDataImportersLRUCacheSize - 1];

        if (pszLastFilePathInList != nullptr)
        {
            IMetaDataImport2* value = _metadataImportersMap[pszLastFilePathInList];
            if (value != nullptr)
            {
                value->Release();
                value = nullptr;
            }
            if (!_metadataImportersMap.erase(pszLastFilePathInList))
            {
                hr = E_UNEXPECTED;
            }

            delete[] pszLastFilePathInList;
            _arFilePaths[g_dwMetaDataImportersLRUCacheSize - 1] = nullptr;
        }

        return hr;
    }
}
