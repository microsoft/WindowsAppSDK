// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __APPMODEL_IDENTITY_H
#define __APPMODEL_IDENTITY_H

#include <appmodel.h>

namespace AppModel::Identity
{
    inline bool IsPackagedProcess()
    {
        UINT32 n{};
        const auto rc{ ::GetCurrentPackageFullName(&n, nullptr) };
        (void) LOG_HR_IF_MSG(HRESULT_FROM_WIN32(rc), (rc != APPMODEL_ERROR_NO_PACKAGE) && (rc != ERROR_INSUFFICIENT_BUFFER), "GetCurrentPackageFullName rc=%d", rc);
        return rc == ERROR_INSUFFICIENT_BUFFER;
    }
}

#endif // __APPMODEL_IDENTITY_H
