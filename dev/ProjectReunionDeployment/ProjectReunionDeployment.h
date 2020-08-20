// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Management.Deployment.ProjectReunionDeployment.g.h"

#define PROJECT_REUNION_INSTALL_INFORMATION_URI L"https://aka.ms/ProjectReunion"
#define PROJECT_REUNION_PACKAGE_INSTALL_URI L"https://aka.ms/projectreunion/install.msixbundle"

namespace winrt::Microsoft::Management::Deployment::implementation
{
    struct ProjectReunionDeployment
    {
        ProjectReunionDeployment() = default;
        static Microsoft::Management::Deployment::ProjectReunionDeploymentStatus GetStatus(Windows::ApplicationModel::PackageVersion const& packageVersion);
        static Windows::Foundation::Uri GetProjectReunionPackageLink();
        static Windows::Foundation::Uri GetProjectReunionInstallInformationLink();
    };
}

namespace winrt::Microsoft::Management::Deployment::factory_implementation
{
    struct ProjectReunionDeployment : ProjectReunionDeploymentT<ProjectReunionDeployment, implementation::ProjectReunionDeployment>
    {
    };
}
