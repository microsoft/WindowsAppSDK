// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace winrt
{
    using namespace winrt::Microsoft::ProjectReunion::Deployment;
    using namespace winrt::Windows::ApplicationModel;
    using namespace winrt::Windows::Foundation;
}

namespace ProjectReunionCppTest
{
    TEST_CLASS(ProjectReunionDeployment)
    {
    public:

        TEST_METHOD(GetStatusIsOK)
        {
            winrt::PackageVersion minVersion = { 0u, 0u, 0u, 0u };
            auto status = winrt::ProjectReunionDeployment::GetStatus(minVersion);
            Assert::IsTrue(status.IsOK());
            Assert::IsFalse(status.PackageInstallRequired());
            Assert::IsFalse(status.WindowsUpdatesRequired());
        }

        TEST_METHOD(GetPackageLink)
        {
            const wchar_t* linkValue = L"https://aka.ms/projectreunion/install.msixbundle";
            winrt::Uri uri = winrt::ProjectReunionDeployment::GetProjectReunionPackageLink();
            Assert::AreEqual(uri.AbsoluteUri().c_str(), linkValue);
        }

        TEST_METHOD(GetInstallInformationLink)
        {
            const wchar_t* linkValue = L"https://aka.ms/ProjectReunion";
            winrt::Uri uri = winrt::ProjectReunionDeployment::GetProjectReunionInstallInformationLink();
            Assert::AreEqual(uri.AbsoluteUri().c_str(), linkValue);
        }
    };
}
