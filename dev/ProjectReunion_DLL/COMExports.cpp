// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ExtensionContractHandler.h"
#include "NotificationActivationHandler.h"

std::wstring get_module_path()
{
    std::wstring path(100, L'?');
    uint32_t path_size{};
    DWORD actual_size{};

    do
    {
        // Get the handle of the dll hosting this code, not the executable that has loaded it.
        wil::unique_hmodule moduleHandle;
        THROW_IF_WIN32_BOOL_FALSE(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
            reinterpret_cast<LPCWSTR>(get_module_path), &moduleHandle));

        path_size = static_cast<uint32_t>(path.size());
        actual_size = ::GetModuleFileName(moduleHandle.get(), path.data(), path_size);

        if (actual_size + 1 > path_size)
        {
            path.resize(path_size * 2, L'?');
        }
    } while (actual_size + 1 > path_size);

    path.resize(actual_size);
    return path;
}

std::wstring get_coclass_path(const GUID& iid)
{
    std::wstring path{ LR"(SOFTWARE\Classes\CLSID\{????????-????-????-????-????????????})" };
    ::StringFromGUID2(iid, path.data() + 23, 39);
    return path;
}

void register_coclass(const GUID& iid)
{
    std::wstring key_path{ get_coclass_path(iid) };
    key_path += LR"(\InProcServer32)";
    wil::unique_hkey key;

    THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
        KEY_WRITE, nullptr, key.put(), nullptr));
    ::RegDeleteValue(key.get(), nullptr);

    std::wstring path{ get_module_path() };
    THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
        reinterpret_cast<BYTE const*>(path.c_str()), static_cast<uint32_t>((path.size() + 1)
        * sizeof(wchar_t))));
}

void unregister_coclass(const GUID& iid)
{
    std::wstring key_path{ get_coclass_path(iid) };
    ::RegDeleteTree(HKEY_CURRENT_USER, key_path.c_str());
}

std::wstring get_association_path(PCWSTR assocName)
{
    std::wstring path{ LR"(SOFTWARE\Classes\)" };
    path += assocName;
    return path;
}

void register_protocol(PCWSTR scheme, PCWSTR displayName, const GUID& delegateExecute)
{
    std::wstring key_path{ get_association_path(scheme) };
    wil::unique_hkey key;

    THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
        KEY_WRITE, nullptr, key.put(), nullptr));

    std::wstring defaultValue{ L"URL:" };
    defaultValue += displayName;
    THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
        reinterpret_cast<BYTE const*>(defaultValue.c_str()),
        static_cast<uint32_t>((defaultValue.size() + 1) * sizeof(wchar_t))));

    std::wstring urlProtocolValue{ L"" };
    defaultValue += displayName;
    THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), L"URL Protocol", 0, REG_SZ,
        reinterpret_cast<BYTE const*>(urlProtocolValue.c_str()),
        static_cast<uint32_t>((urlProtocolValue.size() + 1) * sizeof(wchar_t))));

    key_path += LR"(\shell\open\command)";
    THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
        KEY_WRITE, nullptr, key.put(), nullptr));

    std::wstring delegateClsid{ LR"({????????-????-????-????-????????????})" };
    ::StringFromGUID2(delegateExecute, delegateClsid.data(), 39);

    THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), L"DelegateExecute", 0, REG_SZ,
        reinterpret_cast<BYTE const*>(delegateClsid.c_str()),
        static_cast<uint32_t>((delegateClsid.size() + 1) * sizeof(wchar_t))));
}

void unregister_protocol(PCWSTR scheme)
{
    std::wstring key_path{ get_association_path(scheme) };
    ::RegDeleteTree(HKEY_CURRENT_USER, key_path.c_str());
}

HRESULT __stdcall DllGetClassObject(GUID const& clsid, GUID const& iid, void** result)
{
    try
    {
        *result = nullptr;

        if (clsid == __uuidof(ExtensionContractHandlerFactory))
        {
            return winrt::make<ExtensionContractHandlerFactory>()->QueryInterface(iid, result);
        }

        if (clsid == __uuidof(NotificationActivationHandler))
        {
            return winrt::make<NotificationActivationHandler>()->QueryInterface(iid, result);
        }

        return winrt::hresult_class_not_available().to_abi();
    }
    catch (...)
    {
        return winrt::to_hresult();
    }

    return S_OK;
}

HRESULT __stdcall DllRegisterServer() noexcept try
{
    register_coclass(__uuidof(ExtensionContractHandlerFactory));
    register_coclass(__uuidof(NotificationActivationHandler));
    register_protocol(L"ms-ecap", L"Extension Contract Activation Protocol", __uuidof(ExtensionContractHandlerFactory));
    return S_OK;
}
CATCH_RETURN()

HRESULT __stdcall DllUnregisterServer() noexcept try
{
    unregister_coclass(__uuidof(ExtensionContractHandlerFactory));
    unregister_coclass(__uuidof(NotificationActivationHandler));
    return S_OK;
}
CATCH_RETURN()
