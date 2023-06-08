// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "PackagedTests.h"

void PackagedTests::ChannelRequestUsingNullRemoteId()
{
    BaseTestSuite::ChannelRequestUsingNullRemoteId();
}

void PackagedTests::ChannelRequestUsingRemoteId()
{
    BaseTestSuite::ChannelRequestUsingRemoteId();
}

void PackagedTests::ChannelRequestCheckExpirationTime()
{
    BaseTestSuite::ChannelRequestCheckExpirationTime();
}

// Currently failing - https://github.com/microsoft/WindowsAppSDK/issues/2392
void PackagedTests::MultipleChannelClose()
{
    BaseTestSuite::MultipleChannelClose();
}

void PackagedTests::VerifyRegisterAndUnregister()
{
    BaseTestSuite::VerifyRegisterAndUnregister();
}

void PackagedTests::VerifyUnregisterFails()
{
    BaseTestSuite::VerifyUnregisterFails();
}

void PackagedTests::VerifyUnregisterAllFails()
{
    BaseTestSuite::VerifyUnregisterAllFails();
}

void PackagedTests::VerifyRegisterAndUnregisterAll()
{
    BaseTestSuite::VerifyRegisterAndUnregisterAll();
}

void PackagedTests::MultipleRegister()
{
    BaseTestSuite::MultipleRegister();
}

void PackagedTests::VerifyMultipleRegisterAndUnregister()
{
    BaseTestSuite::VerifyMultipleRegisterAndUnregister();
}

void PackagedTests::VerifyMultipleRegisterAndUnregisterAll()
{
    BaseTestSuite::VerifyMultipleRegisterAndUnregisterAll();
}

void PackagedTests::VerifyUnregisterTwice()
{
    BaseTestSuite::VerifyUnregisterTwice();
}

void PackagedTests::VerifyUnregisterAllTwice()
{
    BaseTestSuite::VerifyUnregisterAllTwice();
}

void PackagedTests::VerifyUnregisterAndUnregisterAll()
{
    BaseTestSuite::VerifyUnregisterAndUnregisterAll();
}

void PackagedTests::VerifyForegroundHandlerSucceeds()
{
    BaseTestSuite::VerifyForegroundHandlerSucceeds();
}

void PackagedTests::VerifyForegroundHandlerFails()
{
    BaseTestSuite::VerifyForegroundHandlerFails();
}
