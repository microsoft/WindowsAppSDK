// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "frameworkudk\ResourceManager.h"

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

HRESULT CheckFile(LPCWSTR filename)
{
    DWORD attributes = GetFileAttributes(filename);
    if (attributes == INVALID_FILE_ATTRIBUTES)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    if (attributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    }

    return S_OK;
}

HRESULT GetDefaultPriFileForCurentModule(bool isPackaged, winrt::hstring& filePath)
{
    PWSTR path = nullptr;
    HRESULT hr = MrmGetFilePathFromName(isPackaged ? L"resources.pri" : nullptr, &path);
    if (FAILED(hr))
    {
        return hr;
    }

    string_resoure_ptr pathContainter(path);
    filePath = pathContainter.get();

    return S_OK;
}

HRESULT GetDefaultPriFileForCurrentPackage(winrt::hstring& filePath)
{
    wchar_t* resourceFile = nullptr;
    HRESULT hr = ResourceManager_GetDefaultResourcePathForPackageFullName(nullptr, &resourceFile);
    if (FAILED(hr))
    {
        return hr;
    }

    std::unique_ptr<wchar_t, decltype(&LocalFree)> resourceFilePtr(resourceFile, LocalFree);

    hr = CheckFile(resourceFile);
    if (FAILED(hr))
    {
        return hr;
    }

    filePath = resourceFile;

    return S_OK;
}

HRESULT GetDefaultPriFile(winrt::hstring& filePath)
{
    HRESULT hr = GetDefaultPriFileForCurrentPackage(filePath);
    if (SUCCEEDED(hr))
    {
        return S_OK;
    }

    // GetDefaultPriFileForCurrentPackage will not handle the new case where
    // resources.pri is in the parent folder. 
    bool isPackaged = (hr != HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
    return GetDefaultPriFileForCurentModule(isPackaged, filePath);
}
