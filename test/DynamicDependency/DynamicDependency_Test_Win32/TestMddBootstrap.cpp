// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MddBootstrap.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
    namespace DynamicDependency
    {
        TEST_CLASS(BootstrapTests)
        {
        public:

            TEST_METHOD(Initialize_ClassNotFound)
            {
                const GUID doesNotExist{};
                Assert::AreEqual(REGDB_E_CLASSNOTREG, MddBootstrapInitialize(doesNotExist));
            }

            TEST_METHOD(Initialize)
            {
                const GUID clsid = {};//TODO
                Assert::AreEqual(S_OK, MddBootstrapInitialize(clsid));
            }

            TEST_METHOD(ShutdownWithoutInitialize)
            {
                MddBootstrapShutdown();
                MddBootstrapShutdown();
            }
        };
    }
}
