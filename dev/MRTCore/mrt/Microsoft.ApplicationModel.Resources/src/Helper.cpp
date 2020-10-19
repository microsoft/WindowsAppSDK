// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

bool IsResourceNotFound(HRESULT hr)
{
    switch (hr)
    {
    case HRESULT_FROM_WIN32(ERROR_NOT_FOUND):
    case HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND):
    case HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND):
    case HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND):
    case HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND):
    case HRESULT_FROM_WIN32(ERROR_MRM_NO_CANDIDATE):
    case HRESULT_FROM_WIN32(ERROR_MRM_NO_MATCH_OR_DEFAULT_CANDIDATE):
        return true;
    }
    return false;
}

HRESULT GetDefaultPriFileForCurentModule(winrt::hstring& filePath)
{
    PWSTR path = nullptr;
    HRESULT hr = MrmGetFilePathFromName(L"resources.pri", &path);
    if (FAILED(hr))
    {
        return hr;
    }

    string_resoure_ptr pathContainter(path);
    filePath = pathContainter.get();

    return S_OK;
}

// $todo: remove
extern "C" LONG WINAPI GetCurrentPackagePath(_Inout_ UINT32* pathLength, _Out_writes_opt_(*pathLength) PWSTR path);

HRESULT GetDefaultPriFileForCurrentPackage(winrt::hstring& filePath)
{
    wchar_t path[MAX_PATH];
    UINT32 length = ARRAYSIZE(path);
    std::unique_ptr<wchar_t[]> allocatedPath;

    LONG ret = GetCurrentPackagePath(&length, path);
    if (ret == ERROR_INSUFFICIENT_BUFFER)
    {
        allocatedPath.reset(new wchar_t[length]);
        ret = GetCurrentPackagePath(&length, allocatedPath.get());
    }

    if (ret != ERROR_SUCCESS)
    {
        return HRESULT_FROM_WIN32(ret);
    }

    winrt::hstring folderPath = allocatedPath ? allocatedPath.get() : path;
    filePath = folderPath + L"\\resources.pri";

    return S_OK;
}

HRESULT GetDefaultPriFile(winrt::hstring& filePath)
{
    // $todo: use IResourceLoaderStatics4 when it's available, and polyfill for downlevel.
    if (FAILED(GetDefaultPriFileForCurrentPackage(filePath)))
    {
        return GetDefaultPriFileForCurentModule(filePath);
    }
    return S_OK;
}