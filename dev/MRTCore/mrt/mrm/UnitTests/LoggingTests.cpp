// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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