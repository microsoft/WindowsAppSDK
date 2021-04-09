// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "TestSetupAndTeardownHelper.h"

namespace ProjectReunionEnvironmentWriterTests
{
    class EnvironmentWriterCentennialTests {
        BEGIN_TEST_CLASS(EnvironmentWriterCentennialTests)
            //TEST_CLASS_PROPERTY(L"RunAs", L"{UAP,RestrictedUser,ElevatedUser,InteractiveUser}")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:Host", L"PackagedCwa")
            TEST_CLASS_PROPERTY(L"UAP:AppXManifest", L"CentennialAppxManifest.pkg.xml")
            END_TEST_CLASS()

        TEST_METHOD(CentennialTestGetForProcess);
        TEST_METHOD(CentennialTestGetForUser);
        TEST_METHOD(CentennialTestGetForMachine);
        TEST_METHOD(CentennialTestSetEnvironmentVariableForProcess);
        TEST_METHOD(CentennialTestSetEnvironmentVariableForUser);
        TEST_METHOD(CentennialTestSetEnvironmentVariableForMachine);
        TEST_METHOD(CentennialTestAppendToPathForProcess);
        TEST_METHOD(CentennialTestAppendToPathForUser);
        TEST_METHOD(CentennialTestAppendToPathForMachine);
        TEST_METHOD(CentennialTestRemoveFromPathForProcess);
        TEST_METHOD(CentennialTestRemoveFromPathForUser);
        TEST_METHOD(CentennialTestRemoveFromPathForMachine);
    };

}
