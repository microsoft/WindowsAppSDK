// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    static const std::wstring c_protocolArgumentString = L"ms-protocol";
    static const std::wstring c_fileArgumentString = L"ms-file";

    enum AssociationType
    {
        File,
        Protocol
    };

    bool IsFileExtension(const std::wstring& extension);
    std::wstring GetFullIdentityString();
    bool HasIdentity();
    std::wstring GetModulePath();
    std::wstring ComputeProgId(AssociationType type);
    std::wstring CreateAssocKeyPath(const std::wstring& assoc);
    wil::unique_hkey CreateAssocKey(const std::wstring& assoc, REGSAM samDesired = KEY_WRITE);
    wil::unique_hkey OpenAssocKey(const std::wstring& assoc, REGSAM samDesired = KEY_READ);
    void DeleteAssocKey(const std::wstring& assoc);
    wil::unique_hkey RegisterProgId(const std::wstring& progId, const std::wstring& displayName);
    void UnregisterProgId(const std::wstring& progId);
    std::wstring CreateApplicationKeyPath(const std::wstring& progId);
    wil::unique_hkey CreateApplicationKey(const std::wstring& progId, REGSAM samDesired = KEY_WRITE);
    wil::unique_hkey OpenApplicationKey(const std::wstring& progId, REGSAM samDesired = KEY_READ);
    void RegisterApplication(const std::wstring& progId);
    void UnregisterApplication(const std::wstring& progId);
    void RegisterVerb(const std::wstring& progId, const std::wstring& verb, const std::wstring& command, _In_opt_ const GUID* delegateExecute = nullptr);
    void UnregisterVerb(const std::wstring& progId, const std::wstring& verb);
    void RegisterProtocol(const std::wstring& scheme, const std::wstring& displayName);
    void UnregisterProtocol(const std::wstring& scheme);
    void RegisterFileExtension(const std::wstring& extension);
    void UnregisterFileExtension(const std::wstring& extension);
    void RegisterAssociationHandler(const std::wstring& association, AssociationType type, const std::wstring& handlerProgId);
    void UnregisterAssociationHandler(const std::wstring& association, AssociationType type, const std::wstring& handlerProgId);
}
