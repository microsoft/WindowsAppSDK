// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __PROJECTREUNION_TEST_PACKAGE_H
#define __PROJECTREUNION_TEST_PACKAGE_H

#include <appmodel.h>

namespace Test::AppModel
{
    bool IsPackagedProcess()
    {
        UINT32 n{};
        return ::GetCurrentPackageFullName(&n, nullptr) == APPMODEL_ERROR_NO_PACKAGE;;
    }
}

#endif // __PROJECTREUNION_TEST_PACKAGE_H
