// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace Test::KozaniRemoteManagerTests
{
    class KozaniRemoteManagerTests
    {
    public:
        BEGIN_TEST_CLASS(KozaniRemoteManagerTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::Cleanup();
            return true;
        }

        // TODO Replace this with your own tests
        TEST_METHOD(JustDoIt)
        {
        }
    };
}
