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

// Taken from Platform.h/.cpp
typedef bool(WINAPI* IsWellFormedTagFunc)(PCWSTR);
HMODULE g_bcp47 = (HMODULE)(-1);

HMODULE LoadBcp47ModuleFrom(_In_ PCWSTR moduleName)
{
    HMODULE module = LoadLibraryExW(moduleName, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (module != nullptr)
    {
        // All BCP47 APIs we are interested are always exported from the same dll together. So we just pick anyone for probe.
        IsWellFormedTagFunc func = (IsWellFormedTagFunc)(GetProcAddress(module, "IsWellFormedTag"));
        if (func != nullptr)
        {
            return module;
        }
        FreeLibrary(module);
    }

    return nullptr;
}

HMODULE LoadBcp47Module()
{
    HMODULE module = LoadBcp47ModuleFrom(L"bcp47mrm.dll");
    if (module == nullptr)
    {
        // In downlevel OS, the API is exposed by bcp47langs.dll.
        module = LoadBcp47ModuleFrom(L"bcp47langs.dll");
    }

    return module;
}

void InitializeBcp47Module()
{
    HMODULE comparand = (HMODULE)(-1);
    if (InterlockedCompareExchangePointer(reinterpret_cast<PVOID*>(&g_bcp47), comparand, comparand) == comparand)
    {
        HMODULE module = LoadBcp47Module();
        InterlockedExchangePointer(reinterpret_cast<PVOID*>(&g_bcp47), module);
    }
}

BOOLEAN _DefIsWellFormedTag(_In_ PCWSTR tag)
{
    // Before new SDK is released, we need to use LoadLibrary/GetProcAddress
    InitializeBcp47Module();

    if (g_bcp47 == nullptr)
    {
        // Didn't find an implementation. Just return TRUE.
        return TRUE;
    }

    IsWellFormedTagFunc func = (IsWellFormedTagFunc)(GetProcAddress(g_bcp47, "IsWellFormedTag"));
    if (func != nullptr)
    {
        return func(tag);
    }

    // Should not reach here.
    return TRUE;
}
