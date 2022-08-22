// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"
#include "UnpackagedTests.h"

void UnpackagedTests::ChannelRequestUsingNullRemoteId()
{
    BaseTestSuite::ChannelRequestUsingNullRemoteId();
}

void UnpackagedTests::ChannelRequestUsingRemoteId()
{
    BaseTestSuite::ChannelRequestUsingRemoteId();
}

// Currently failing - https://github.com/microsoft/WindowsAppSDK/issues/2392
void UnpackagedTests::MultipleChannelClose()
{
    BaseTestSuite::MultipleChannelClose();
}

void UnpackagedTests::VerifyRegisterAndUnregister()
{
    BaseTestSuite::VerifyRegisterAndUnregister();
}

void UnpackagedTests::VerifyUnregisterFails()
{
    BaseTestSuite::VerifyUnregisterFails();
}

void UnpackagedTests::VerifyUnregisterAllFails()
{
    BaseTestSuite::VerifyUnregisterAllFails();
}

void UnpackagedTests::VerifyRegisterAndUnregisterAll()
{
    BaseTestSuite::VerifyRegisterAndUnregisterAll();
}

void UnpackagedTests::MultipleRegister()
{
    BaseTestSuite::MultipleRegister();
}

void UnpackagedTests::VerifyMultipleRegisterAndUnregister()
{
    BaseTestSuite::VerifyMultipleRegisterAndUnregister();
}

void UnpackagedTests::VerifyMultipleRegisterAndUnregisterAll()
{
    BaseTestSuite::VerifyMultipleRegisterAndUnregisterAll();
}

void UnpackagedTests::VerifyUnregisterTwice()
{
    BaseTestSuite::VerifyUnregisterTwice();
}

void UnpackagedTests::VerifyUnregisterAllTwice()
{
    BaseTestSuite::VerifyUnregisterAllTwice();
}

void UnpackagedTests::VerifyUnregisterAndUnregisterAll()
{
    BaseTestSuite::VerifyUnregisterAndUnregisterAll();
}

void UnpackagedTests::VerifyForegroundHandlerSucceeds()
{
    BaseTestSuite::VerifyForegroundHandlerSucceeds();
}

void UnpackagedTests::VerifyForegroundHandlerFails()
{
    BaseTestSuite::VerifyForegroundHandlerFails();
}
