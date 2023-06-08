// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace Test::Common
{
    class SecurityUserTests_User
    {
    public:
        BEGIN_TEST_CLASS(SecurityUserTests_User)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_METHOD(IsLocalSystem)
        {
            VERIFY_IS_FALSE(::Security::User::IsLocalSystem());
        }
    };

    class SecurityUserTests_System
    {
    public:
        BEGIN_TEST_CLASS(SecurityUserTests_System)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"System")
        END_TEST_CLASS()

        TEST_METHOD(IsLocalSystem)
        {
            VERIFY_IS_TRUE(::Security::User::IsLocalSystem());
        }
    };
}
