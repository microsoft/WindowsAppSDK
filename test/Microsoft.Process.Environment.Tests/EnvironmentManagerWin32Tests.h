#pragma once

namespace ProjectReunionCppTest
{
    class EnvironmentManagerWin32Tests {
        BEGIN_TEST_CLASS(EnvironmentManagerWin32Tests)
            TEST_CLASS_PROPERTY(L"ActivationContext", L"CppTest.dll.manifest")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs", L"Elevated")
        END_TEST_CLASS()

        TEST_METHOD_SETUP(TestSetup);
        TEST_METHOD(TestGetForProcess);
        TEST_METHOD(TestGetForUser);
        TEST_METHOD(TestGetForMachine);
    };
}
