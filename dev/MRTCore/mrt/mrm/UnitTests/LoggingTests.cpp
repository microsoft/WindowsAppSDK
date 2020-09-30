// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <windows.h>
#include <mrm/common/mrmtracelogging.h>
#include <WexTestClass.h>

namespace UnitTests
{

class LoggingTests : public WEX::TestClass<LoggingTests>
{
    TEST_CLASS(LoggingTests);

    TEST_METHOD(LogInMemory);
};

void LoggingTests::LogInMemory()
{
    for (int i = 0; i < 30; i++)
    {
        LOG_ERROR_IN_MEMORY(0, 0, nullptr, nullptr);
        LOG_ERROR_IN_MEMORY(0x80070002 + i, 100 + i, nullptr, nullptr);
        LOG_ERROR_IN_MEMORY(0x80070002 + i, 100 + i, "d:\\os\\src\\mrm\\starwar.cpp", nullptr);
        LOG_ERROR_IN_MEMORY(0x80070002 + i, 100 + i, "d:\\os\\src\\mrm\\starwar.cpp", L"sorry, your test failed");
        LOG_ERROR_IN_MEMORY(0x80070002 + i, 100 + i, nullptr, L"MRT rocks");
    }
}
} // namespace UnitTests