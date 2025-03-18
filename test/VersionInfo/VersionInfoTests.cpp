﻿// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace Test::VersionInfo
{
    class VersionInfoTests
    {
    public:
        BEGIN_TEST_CLASS(VersionInfoTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
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

        TEST_METHOD(VersionInfo_Release)
        {
            try
            {
                auto release{ winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::ReleaseInfo::AsString() };
                VERIFY_FAIL(L"Success is not expected without Microsoft.WindowsAppRuntime.Insights.Resource.dll");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND), e.code());
            }
        }

        TEST_METHOD(VersionInfo_Runtime)
        {
            try
            {
                auto runtime{ winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeInfo::AsString() };
                VERIFY_FAIL(L"Success is not expected without Microsoft.WindowsAppRuntime.Insights.Resource.dll");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND), e.code());
            }
        }
    };
}
