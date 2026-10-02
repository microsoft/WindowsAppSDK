// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __WINDOWSAPPRUNTIME_TEST_APPMODEL_H
#define __WINDOWSAPPRUNTIME_TEST_APPMODEL_H

#include <appmodel.h>

#include <Verify.h>

namespace Test::AppModel
{
    inline bool IsPackagedProcess()
    {
        UINT32 n{};
        const auto rc = ::GetCurrentPackageFullName(&n, nullptr);
        VERIFY_IS_TRUE((rc == APPMODEL_ERROR_NO_PACKAGE) || (rc == ERROR_INSUFFICIENT_BUFFER));
        return rc == ERROR_INSUFFICIENT_BUFFER;
    }
}

#endif // __WINDOWSAPPRUNTIME_TEST_APPMODEL_H
