// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "Association.h"

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    bool IsFileExtension(const std::wstring& extension)
    {
        return (extension.at(0) == L'.');
    }

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

    // Compute a stable progId.
    std::wstring ComputeProgId()
    {
        // TODO: Compute progIds based on the path of the executable and possibly more data.
        return std::wstring(L"ScoDarGenerated1");
    }

    std::wstring CreateAssocKeyPath(const std::wstring& assoc)
    {
        std::wstring path{ LR"(SOFTWARE\Classes\)" };
        path += assoc;
        return path;
    }

    wil::unique_hkey CreateAssocKey(const std::wstring& assoc, REGSAM samDesired)
    {
        auto path = CreateAssocKeyPath(assoc.c_str());
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, path.c_str(), 0, nullptr, 0,
            samDesired, nullptr, key.put(), nullptr));
        return key;
    }

    wil::unique_hkey OpenAssocKey(const std::wstring& assoc, REGSAM samDesired)
    {
        auto path = CreateAssocKeyPath(assoc.c_str());
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegOpenKeyEx(HKEY_CURRENT_USER, path.c_str(), 0, samDesired,
            key.put()));
        return key;
    }

    bool AssocExists(const std::wstring& assoc)
    {
        auto path = CreateAssocKeyPath(assoc.c_str());
        wil::unique_hkey key;
        if (SUCCEEDED(::RegOpenKeyEx(HKEY_CURRENT_USER, path.c_str(), 0, KEY_READ,
            key.put())))
        {
            return true;
        }
        return false;
    }

    bool AssocValueExists(const std::wstring& assoc, const std::wstring& value)
    {
        auto path = CreateAssocKeyPath(assoc.c_str());
        wil::unique_hkey key;
        if (SUCCEEDED(::RegOpenKeyEx(HKEY_CURRENT_USER, path.c_str(), 0, KEY_READ,
            key.put())))
        {
            if (SUCCEEDED(::RegQueryValueEx(key.get(), value.c_str(), 0, nullptr, nullptr, nullptr)))
            {
                return true;
            }
        }
        return false;
    }

    void DeleteAssocKey(const std::wstring& assoc)
    {
        auto path = CreateAssocKeyPath(assoc);
        ::RegDeleteTree(HKEY_CURRENT_USER, path.c_str());
    }

    wil::unique_hkey RegisterProgId(const std::wstring& progId, const std::wstring& displayName)
    {
        auto key = CreateAssocKey(progId, KEY_WRITE);
        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
            reinterpret_cast<BYTE const*>(displayName.c_str()),
            static_cast<uint32_t>((displayName.size() + 1) * sizeof(wchar_t))));
        return key;
    }

    void UnregisterProgId(const std::wstring& progId)
    {
        DeleteAssocKey(progId);
    }

    void RegisterApplication(const std::wstring& progId)
    {
        RegisterProgId(progId, L"");

        wil::unique_hkey registeredAppsKey;
        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, LR"(SOFTWARE\RegisteredApplications\)",
            0, nullptr, 0, KEY_WRITE, nullptr, registeredAppsKey.put(), nullptr));

        // TODO: Turn this into a helper for the RegisterProgidAsHandler usage
        std::wstring capabilitiesKeyPath = LR"(Software\Microsoft\ReunionApplications\)" + progId + LR"(\Capabilties)";
        wil::unique_hkey capabilitiesKey;
        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, capabilitiesKeyPath.c_str(),
            0, nullptr, 0, KEY_WRITE, nullptr, capabilitiesKey.put(), nullptr));

        THROW_IF_WIN32_ERROR(::RegSetValueEx(registeredAppsKey.get(), progId.c_str(), 0, REG_SZ,
            reinterpret_cast<BYTE const*>(capabilitiesKeyPath.c_str()),
            static_cast<uint32_t>((capabilitiesKeyPath.size() + 1) * sizeof(wchar_t))));
    }

    // TODO: Do we really want to support this?  When would it be safe to call?
    void UnregisterApplication(const std::wstring& progId)
    {
        std::wstring capabilitiesKeyPath = LR"(Software\Microsoft\ReunionApplications\)" + progId + LR"(\Capabilties)";
        ::RegDeleteTree(HKEY_CURRENT_USER, capabilitiesKeyPath.c_str());

        wil::unique_hkey registeredAppsKey;
        if (SUCCEEDED(::RegOpenKeyEx(HKEY_CURRENT_USER, LR"(SOFTWARE\RegisteredApplications\)",
            0, KEY_WRITE, registeredAppsKey.put())))
        {
            ::RegDeleteValue(registeredAppsKey.get(), progId.c_str());
        }

        UnregisterProgId(progId);
    }

    void RegisterVerb(const std::wstring& progId, const std::wstring& verb, const std::wstring& command,
        _In_opt_ const GUID* delegateExecute)
    {
        auto assocKey = OpenAssocKey(progId, KEY_WRITE);
        auto key_path = LR"(\shell\)" + verb + LR"(\command)";
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(assocKey.get(), key_path.c_str(), 0, nullptr, 0,
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

    void RegisterProtocol(const std::wstring& scheme, const std::wstring& displayName)
    {
        const std::wstring c_urlProtocolValueName = L"URL Protocol";

        if (AssocExists(scheme) && AssocValueExists(scheme, c_urlProtocolValueName))
        {
            // Protocol already exists.
            return;
        }

        if (AssocExists(scheme))
        {
            // ProgId exists, but isn't a protocol.
            throw std::invalid_argument("scheme");
        }

        auto key = RegisterProgId(scheme, displayName);            
        std::wstring defaultValue = L"URL:" + displayName;
        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
            reinterpret_cast<BYTE const*>(defaultValue.c_str()),
            static_cast<uint32_t>((defaultValue.size() + 1) * sizeof(wchar_t))));
        
        std::wstring emptyValue{ L"" };
        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), c_urlProtocolValueName.c_str(), 0,
            REG_SZ, reinterpret_cast<BYTE const*>(emptyValue.c_str()),
            static_cast<uint32_t>((emptyValue.size() + 1) * sizeof(wchar_t))));
    }

    // TODO: Do we really want to support this?  When would it be safe to call?
    void UnregisterProtocol(const std::wstring& scheme)
    {
        DeleteAssocKey(scheme);
    }

    void RegisterFileExtension(const std::wstring& extension)
    {
        if (!IsFileExtension(extension))
        {
            throw winrt::hresult_invalid_argument();
        }

        CreateAssocKey(extension, KEY_WRITE);
    }

    void UnregisterFileExtension(const std::wstring& extension)
    {
        if (!IsFileExtension(extension))
        {
            throw winrt::hresult_invalid_argument();
        }

        // TODO: Make sure we only remove if no handlers exist.
        auto openWithProgidsIsEmpty = false;
        if (openWithProgidsIsEmpty)
        {
            DeleteAssocKey(extension);
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
        if (!IsFileExtension(extension))
        {
            throw winrt::hresult_invalid_argument();
        }

        auto handlers_list_path = CreateAssocKeyPath(extension.c_str()) + LR"(\OpenWithProgids)";
        wil::unique_hkey handlers_list_key;

        if (SUCCEEDED(::RegOpenKeyEx(HKEY_CURRENT_USER, handlers_list_path.c_str(), 0, KEY_WRITE,
            handlers_list_key.put())))
        {
            ::RegDeleteValue(handlers_list_key.get(), progId.c_str());
        }

        // TODO: Make sure we only remove if no handlers exist.
        auto openWithProgidsIsEmpty = false;
        if (openWithProgidsIsEmpty)
        {
            ::RegDeleteTree(HKEY_CURRENT_USER, handlers_list_path.c_str());
        }
    }
}
