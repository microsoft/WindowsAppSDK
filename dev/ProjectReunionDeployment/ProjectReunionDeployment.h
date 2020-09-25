// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Deployment.ProjectReunionDeployment.g.h"

#define PROJECT_REUNION_INSTALL_INFORMATION_URI L"https://aka.ms/ProjectReunion"
#define PROJECT_REUNION_PACKAGE_INSTALL_URI L"https://aka.ms/projectreunion/install.msixbundle"
#define PROJECT_REUNION_OS_UPDATE_REGISTRY_PATH L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AppModel\\ProjectReunion\\Updates"

namespace winrt::Microsoft::ProjectReunion::Deployment::implementation
{
    struct ProjectReunionDeployment
    {
        ProjectReunionDeployment() = default;
        static Microsoft::ProjectReunion::Deployment::ProjectReunionDeploymentStatus GetStatus(Windows::ApplicationModel::PackageVersion const& packageVersion);
        static winrt::Windows::Foundation::Uri GetProjectReunionPackageLink();
        static winrt::Windows::Foundation::Uri GetProjectReunionInstallInformationLink();

    private:
        static bool GetIsOSUpdatesRequired();
    };
}

namespace winrt::Microsoft::ProjectReunion::Deployment::factory_implementation
{
    struct ProjectReunionDeployment : ProjectReunionDeploymentT<ProjectReunionDeployment, implementation::ProjectReunionDeployment>
    {
    };
}
