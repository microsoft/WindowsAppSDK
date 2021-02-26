// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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

HRESULT GetDefaultPriFileForCurrentPackage(winrt::hstring& filePath)
{
    wchar_t* resourceFile = nullptr;
    HRESULT hr = ResourceManager_GetDefaultResourcePathForPackageFullName(nullptr, &resourceFile);
    if (FAILED(hr))
    {
        return hr;
    }

    std::unique_ptr<wchar_t, decltype(&LocalFree)> resourceFilePtr(resourceFile, LocalFree);

    filePath = resourceFile;

    return S_OK;
}

HRESULT GetDefaultPriFile(winrt::hstring& filePath)
{
    if (FAILED(GetDefaultPriFileForCurrentPackage(filePath)))
    {
        return GetDefaultPriFileForCurentModule(filePath);
    }
    return S_OK;
}
