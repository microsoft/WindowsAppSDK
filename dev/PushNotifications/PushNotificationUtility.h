// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"

const std::wstring ConvertByteArrayToWideString(unsigned int payloadLength, _In_reads_(payloadLength) byte* payload);
void ProtocolLaunchHelper(unsigned int payloadLength, _In_reads_(payloadLength) byte* payload);
wil::unique_cotaskmem_string GetAppUserModelId();
