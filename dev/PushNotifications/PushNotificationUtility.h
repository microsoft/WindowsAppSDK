// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"

const std::wstring ConvertByteArrayToWideString(unsigned int payloadLength, _In_reads_(payloadLength) byte* payload);
void ProtocolLaunchHelper(unsigned int payloadLength, _In_reads_(payloadLength) byte* payload);

inline HRESULT GetAppUserModelId(wil::unique_cotaskmem_string& appUserModelId)
{
    wchar_t appId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
    UINT32 appIdSize{ ARRAYSIZE(appId) };

    RETURN_IF_FAILED(GetCurrentApplicationUserModelId(&appIdSize, appId));

    appUserModelId = wil::make_unique_string<wil::unique_cotaskmem_string>(appId);

    return S_OK;
}
