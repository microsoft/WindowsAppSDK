// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __PROJECTREUNION_TEST_TAEF_H
#define __PROJECTREUNION_TEST_TAEF_H

namespace Test::TAEF
{
    inline std::filesystem::path GetDeploymentDir()
    {
        WEX::Common::String testDeploymentDir;
        WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", testDeploymentDir);
        return static_cast<PCWSTR>(testDeploymentDir);
    }
}

#endif // __PROJECTREUNION_TEST_TAEF_H
