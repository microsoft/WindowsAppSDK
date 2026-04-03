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
    hr = GetDefaultPriFileForCurentModule(isPackaged, filePath);
    if (SUCCEEDED(hr))
    {
        return S_OK;
    }

    // Sparse-packaged apps have package identity (via AddPackageByUriAsync) but
    // deploy resources as loose files next to the executable rather than through
    // the package system. Because they have identity, the packaged code path above
    // passes "resources.pri" to MrmGetFilePathFromName — which only searches for
    // that exact filename. However, sparse apps may use a custom PRI name matching
    // their module name (e.g., "MyApp.pri" via ProjectPriFileName).
    //
    // The package system cannot resolve the app's original PRI filename for sparse
    // apps, so we fall back to the unpackaged discovery path which passes nullptr
    // to MrmGetFilePathFromName. This triggers a broader search that includes both
    // "resources.pri" and "[modulename].pri" (derived via PathCchRenameExtension
    // from the process executable name).
    //
    // This only runs for apps with identity where "resources.pri" was not found —
    // fully packaged apps and unpackaged apps are unaffected.
    // If this fallback also fails, return the original HRESULT so callers that
    // check for a specific error (e.g., ERROR_FILE_NOT_FOUND) are not broken.
    // See: https://github.com/microsoft/microsoft-ui-xaml/issues/10856
    if (isPackaged)
    {
        HRESULT hrFallback = GetDefaultPriFileForCurentModule(false, filePath);
        if (SUCCEEDED(hrFallback))
        {
            return S_OK;
        }
    }

    return hr;
}
