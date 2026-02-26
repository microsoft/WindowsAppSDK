// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __APPMODEL_IDENTITY_ISPACKAGEDPROCESS_H
#define __APPMODEL_IDENTITY_ISPACKAGEDPROCESS_H

#include <appmodel.h>

namespace AppModel::Identity
{
inline HRESULT IsPackagedProcess(bool& isPackagedProcess) noexcept
{
    UINT32 n{};
    const auto rc{ ::GetCurrentPackageFullName(&n, nullptr) };
    if ((rc != APPMODEL_ERROR_NO_PACKAGE) && (rc != ERROR_INSUFFICIENT_BUFFER))
    {
        isPackagedProcess = false;
        return HRESULT_FROM_WIN32(rc);
    }
    isPackagedProcess = (rc == ERROR_INSUFFICIENT_BUFFER);
    return S_OK;
}
}

#endif // __APPMODEL_IDENTITY_ISPACKAGEDPROCESS_H
