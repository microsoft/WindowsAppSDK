// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

namespace winrt::Microsoft::ProjectReunion::implementation
{

    static const std::wstring c_protocolArgumentString = L"ms-protocol"; //L"ms-protocol"

    std::wstring GetFullIdentityString();
    bool HasIdentity();
    std::wstring GetModulePath();
    std::wstring CreateAssocKeyPath(PCWSTR assocName);
    void RegisterProtocol(PCWSTR scheme, PCWSTR displayName, _In_opt_ const GUID* delegateExecute = nullptr);
    void UnregisterProtocol(PCWSTR scheme);
}
