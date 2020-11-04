// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    static const std::wstring c_protocolArgumentString = L"ms-protocol";
    static const std::wstring c_fileArgumentString = L"ms-file";

    std::wstring GetFullIdentityString();
    bool HasIdentity();
    std::wstring GetModulePath();
    std::wstring CreateAssocKeyPath(const std::wstring& assocName);
    std::wstring GenerateProgIdName();
    void RegisterProgId(const std::wstring& progId, const std::wstring& displayName, bool isProtocol = false);
    void UnregisterProgId(const std::wstring& progId);
    void RegisterVerb(const std::wstring& progId, const std::wstring& verb, const std::wstring& command, _In_opt_ const GUID* delegateExecute = nullptr);
    void UnregisterVerb(const std::wstring& progId, const std::wstring& verb);
    void RegisterFileExtension(const std::wstring& extension);
    void UnregisterFileExtension(const std::wstring& extension);
    void RegisterProgidAsHandler(const std::wstring& extension, const std::wstring& progId);
    void UnregisterProgidAsHandler(const std::wstring& extension, const std::wstring& progId);
}
