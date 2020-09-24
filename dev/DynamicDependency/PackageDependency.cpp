// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

#include "PackageDependency.h"

void MddCore::PackageDependency::GenerateId()
{
    GUID id{};
    THROW_IF_FAILED(CoCreateGuid(&id));
    const size_t idAsStringLength = ARRAYSIZE(L"{33221100-5544-7766-8899-aabbccddeeff}") - 1;
    WCHAR idAsString[idAsStringLength + 1]{};
    FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), StringFromGUID2(id, idAsString, idAsStringLength + 1) != idAsStringLength + 1);
    m_packageDependencyId.assign(idAsString);
}
