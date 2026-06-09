// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __APPMODEL_IDENTITY_ISPACKAGEDPROCESS_H
#define __APPMODEL_IDENTITY_ISPACKAGEDPROCESS_H

#include <appmodel.h>

namespace AppModel::Identity
{
inline HRESULT IsPackagedProcess_nothrow(bool& isPackagedProcess) noexcept
{
    isPackagedProcess = false;
    UINT32 n{};
    const auto rc{ ::GetCurrentPackageFullName(&n, nullptr) };
    RETURN_HR_IF(HRESULT_FROM_WIN32(rc), (rc != APPMODEL_ERROR_NO_PACKAGE) && (rc != ERROR_INSUFFICIENT_BUFFER));
    isPackagedProcess = (rc == ERROR_INSUFFICIENT_BUFFER);
    return S_OK;
}

inline bool IsPackagedProcess()
{
    UINT32 n{};
    const auto rc{ ::GetCurrentPackageFullName(&n, nullptr) };
    THROW_HR_IF_MSG(HRESULT_FROM_WIN32(rc), (rc != APPMODEL_ERROR_NO_PACKAGE) && (rc != ERROR_INSUFFICIENT_BUFFER), "GetCurrentPackageFullName rc=%d", rc);
    return rc == ERROR_INSUFFICIENT_BUFFER;
}
}

#endif // __APPMODEL_IDENTITY_ISPACKAGEDPROCESS_H
