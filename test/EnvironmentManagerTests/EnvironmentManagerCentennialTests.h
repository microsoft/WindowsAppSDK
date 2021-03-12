#pragma once

namespace ProjectReunionEnvironmentManagerTests
{
    class EnvironmentManagerCentennialTests {
        BEGIN_TEST_CLASS(EnvironmentManagerCentennialTests)
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:Host", L"PackagedCwa")
            TEST_CLASS_PROPERTY(L"UAP:AppXManifest", L"CentennialAppxManifest.pkg.xml")
        END_TEST_CLASS()

        TEST_METHOD(CentennialTestGetForProcess);
        TEST_METHOD(CentennialTestGetForUser);
        TEST_METHOD(CentennialTestGetForMachine);
        TEST_METHOD(CentennialTestGetEnvironmentVariablesForProcess);
        TEST_METHOD(CentennialTestGetEnvironmentVariablesForUser);
        TEST_METHOD(CentennialTestGetEnvironmentVariablesForMachine);
    };

}
