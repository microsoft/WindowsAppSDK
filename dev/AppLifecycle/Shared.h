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
    void RegisterFileExtension(const std::wstring& extension);
    void UnregisterFileExtension(const std::wstring& extension);
    void RegisterFileHandler(const std::wstring& extension, const std::wstring& verb, _In_opt_ const GUID* delegateExecute = nullptr);
    void UnregisterFileHandler(const std::wstring& extension);
    void RegisterProtocol(const std::wstring& scheme, const std::wstring& displayName, _In_opt_ const GUID* delegateExecute = nullptr);
    void UnregisterProtocol(const std::wstring& scheme);
}
