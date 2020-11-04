// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "Shared.h"

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    std::wstring GetFullIdentityString()
    {
        std::wstring identityString;
        WCHAR idNameBuffer[PACKAGE_FULL_NAME_MAX_LENGTH+1];
        UINT32 idNameBufferLen = ARRAYSIZE(idNameBuffer);
        if (::GetCurrentPackageFullName(&idNameBufferLen, idNameBuffer) == ERROR_SUCCESS)
        {
            identityString = idNameBuffer;
        }

        return identityString;
    }

    bool HasIdentity()
    {
        return !(GetFullIdentityString()).empty();
    }

    std::wstring GetModulePath()
    {
        std::wstring path(100, L'?');
        uint32_t path_size{};
        DWORD actual_size{};

        do
        {
            path_size = static_cast<uint32_t>(path.size());
            actual_size = ::GetModuleFileName(nullptr, path.data(), path_size);

            if (actual_size + 1 > path_size)
            {
                path.resize(path_size * 2, L'?');
            }
        } while (actual_size + 1 > path_size);

        path.resize(actual_size);
        return path;
    }

    std::wstring CreateAssocKeyPath(const std::wstring& assocName)
    {
        std::wstring path{ LR"(SOFTWARE\Classes\)" };
        path += assocName;
        return path;
    }

    // Generate a stable progId.
    std::wstring GenerateProgIdName()
    {
        // TODO: Generate progIds based on the path of the executable and possibly more data.
        return std::wstring(L"ScoDarGenerated1");
    }

    void RegisterProgId(const std::wstring& progId, const std::wstring& displayName, bool isProtocol)
    {
        auto key_path = CreateAssocKeyPath(progId);
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
            KEY_WRITE, nullptr, key.put(), nullptr));

        std::wstring defaultValue;
        if (isProtocol)
        {
            std::wstring urlProtocolValue{ L"" };
            THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), L"URL Protocol", 0, REG_SZ,
                reinterpret_cast<BYTE const*>(urlProtocolValue.c_str()),
                static_cast<uint32_t>((urlProtocolValue.size() + 1) * sizeof(wchar_t))));

            defaultValue += L"URL:";
        }

        defaultValue += displayName;
        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
            reinterpret_cast<BYTE const*>(defaultValue.c_str()),
            static_cast<uint32_t>((defaultValue.size() + 1) * sizeof(wchar_t))));
    }

    void UnregisterProgId(const std::wstring& progId)
    {
        auto key_path = CreateAssocKeyPath(progId);
        ::RegDeleteTree(HKEY_CURRENT_USER, key_path.c_str());
    }

    void RegisterVerb(const std::wstring& progId, const std::wstring& verb, const std::wstring& command, _In_opt_ const GUID* delegateExecute)
    {
        auto key_path = CreateAssocKeyPath(progId) + LR"(\shell\)" + verb + LR"(\command)";
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
            KEY_WRITE, nullptr, key.put(), nullptr));

        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
            reinterpret_cast<BYTE const*>(command.c_str()),
            static_cast<uint32_t>((command.size() + 1) * sizeof(wchar_t))));

        if (delegateExecute)
        {
            std::wstring delegateClsid{ LR"({????????-????-????-????-????????????})" };
            ::StringFromGUID2(*delegateExecute, delegateClsid.data(), 39);

            THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), L"DelegateExecute", 0, REG_SZ,
                reinterpret_cast<BYTE const*>(delegateClsid.c_str()),
                static_cast<uint32_t>((delegateClsid.size() + 1) * sizeof(wchar_t))));
        }
    }

    void UnregisterVerb(const std::wstring& progId, const std::wstring& verb)
    {
        auto key_path = CreateAssocKeyPath(progId) + LR"(\shell\)" + verb + LR"(\command)";
        ::RegDeleteTree(HKEY_CURRENT_USER, key_path.c_str());
    }

    void RegisterFileExtension(const std::wstring& extension)
    {
        if (extension.at(0) != L'.')
        {
            throw winrt::hresult_invalid_argument();
        }

        auto key_path = CreateAssocKeyPath(extension.c_str());
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
            KEY_WRITE, nullptr, key.put(), nullptr));
    }

    void UnregisterFileExtension(const std::wstring& extension)
    {
        if (extension.at(0) != L'.')
        {
            throw winrt::hresult_invalid_argument();
        }

        // TODO: Make sure we only remove if no handlers exist.
        auto openWithProgidsIsEmpty = false;
        if (openWithProgidsIsEmpty)
        {
            auto key_path = CreateAssocKeyPath(extension.c_str());
            ::RegDeleteTree(HKEY_CURRENT_USER, key_path.c_str());
        }
    }

    void RegisterProgidAsHandler(const std::wstring& extension, const std::wstring& progId)
    {
        // TODO: Fail if the extension doesn't already exist.

        // Link the progId as a handler for the extension.
        auto handlers_list_path = CreateAssocKeyPath(extension.c_str()) + LR"(\OpenWithProgids)";
        wil::unique_hkey handlers_list_key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, handlers_list_path.c_str(), 0, nullptr,
            0, KEY_WRITE, nullptr, handlers_list_key.put(), nullptr));

        THROW_IF_WIN32_ERROR(::RegSetValueEx(handlers_list_key.get(), progId.c_str(), 0, REG_SZ,
            nullptr, 0));
    }

    void UnregisterProgidAsHandler(const std::wstring& extension, const std::wstring& progId)
    {
        if (extension.at(0) != L'.')
        {
            throw winrt::hresult_invalid_argument();
        }

        auto handlers_list_path = CreateAssocKeyPath(extension.c_str()) + LR"(\OpenWithProgids)";
        wil::unique_hkey handlers_list_key;


        THROW_IF_WIN32_ERROR(::RegOpenKeyEx(HKEY_CURRENT_USER, handlers_list_path.c_str(), 0,
            KEY_WRITE, handlers_list_key.put()));

        THROW_IF_WIN32_ERROR(::RegDeleteValue(handlers_list_key.get(), progId.c_str()));

        // TODO: Make sure we only remove if no handlers exist.
        auto openWithProgidsIsEmpty = false;
        if (openWithProgidsIsEmpty)
        {
            ::RegDeleteTree(HKEY_CURRENT_USER, handlers_list_path.c_str());
        }
    }
}
