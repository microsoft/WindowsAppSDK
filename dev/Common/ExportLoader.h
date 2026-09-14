// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(__EXPORTLOADER_H)
#define __EXPORTLOADER_H

namespace ExportLoader
{
inline HRESULT Load(PCWSTR moduleName, _Out_ HMODULE* module)
{
    auto hmodule{ ::LoadLibraryExW(moduleName, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32) };
    if (!hmodule)
    {
        const auto rc{ GetLastError() };
        RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(rc), rc != ERROR_MOD_NOT_FOUND, "%ls", moduleName);
        RETURN_HR(E_NOTIMPL);
    }
    *module = hmodule;
    return S_OK;
}

inline HMODULE Load(PCWSTR moduleName)
{
    auto hmodule{ ::LoadLibraryExW(moduleName, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32) };
    if (!hmodule)
    {
        const auto rc{ GetLastError() };
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(rc), rc != ERROR_MOD_NOT_FOUND, "%ls", moduleName);
        THROW_HR(E_NOTIMPL);
    }
    return hmodule;
}

template <typename T>
inline HRESULT GetFunctionIfExists(HMODULE module, PCSTR functionName, _Out_ T* function)
{
    auto fn{ reinterpret_cast<T>(::GetProcAddress(module, functionName)) };
    if (!fn)
    {
        const auto rc{ GetLastError() };
        RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(rc), rc != ERROR_PROC_NOT_FOUND, "%hs", functionName);
    }
    *function = fn;
    return S_OK;
}

template <typename T>
inline T GetFunctionIfExists(HMODULE module, PCSTR functionName)
{
    auto function{ reinterpret_cast<T>(::GetProcAddress(module, functionName)) };
    if (!function)
    {
        const auto rc{ GetLastError() };
        if (rc == ERROR_PROC_NOT_FOUND)
        {
            return nullptr;
        }
        THROW_WIN32_MSG(rc, "%hs", functionName);
    }
    return function;
}

template <typename T>
inline T GetFunction(HMODULE module, PCSTR functionName)
{
    auto function{ GetFunctionIfExists<T>(module, functionName) };
    THROW_HR_IF_NULL_MSG(E_NOTIMPL, function, "%hs", functionName);
    return function;
}
}

#endif // defined(__EXPORTLOADER_H)
