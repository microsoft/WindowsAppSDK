// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

namespace winrt::Microsoft::ProjectReunion::implementation
{
#define MS_PROTOCOL_ARG_STR L"ms-protocol"
#define MS_FILE_ARG_STR L"ms-file"

    std::wstring GetFullIdentityString();
    bool HasIdentity();
    std::wstring GetModulePath();
    std::wstring CreateAssocKeyPath(PCWSTR assocName);
    void RegisterProtocol(PCWSTR scheme, PCWSTR displayName, _In_opt_ const GUID* delegateExecute = nullptr);
    void UnregisterProtocol(PCWSTR scheme);
}
