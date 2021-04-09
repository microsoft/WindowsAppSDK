// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "TestSetupAndTeardownHelper.h"

namespace ProjectReunionEnvironmentWriterTests
{
    class EnvironmentWriterUWPTests {
        BEGIN_TEST_CLASS(EnvironmentWriterUWPTests)
            //TEST_CLASS_PROPERTY(L"RunAs", L"{UAP,Restricted}")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppXManifest", L"AppxManifest.pkg.xml")
            END_TEST_CLASS()

        TEST_METHOD(UWPTestGetForProcess);
        TEST_METHOD(UWPTestGetForUser);
        TEST_METHOD(UWPTestGetForMachine);
        TEST_METHOD(UWPTestSetEnvironmentVariableForProcess);
        TEST_METHOD(UWPTestSetEnvironmentVariableForUser);
        TEST_METHOD(UWPTestSetEnvironmentVariableForMachine);
        TEST_METHOD(UWPTestAppendToPathForProcess);
        TEST_METHOD(UWPTestAppendToPathForUser);
        TEST_METHOD(UWPTestAppendToPathForMachine);
        TEST_METHOD(UWPTestRemoveFromPathForProcess);
        TEST_METHOD(UWPTestRemoveFromPathForUser);
        TEST_METHOD(UWPTestRemoveFromPathForMachine);
    };
}
