// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

class BaseTestSuite
{
    public:
        // Unit test environment functions
        void ClassSetup();
        void ClassCleanup();
        void MethodCleanup();

        // Base unit tests
        void Test1();
    private:
        bool m_unregisteredFully{ true };
};
