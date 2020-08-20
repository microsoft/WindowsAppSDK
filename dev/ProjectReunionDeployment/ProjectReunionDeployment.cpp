// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ProjectReunionDeployment.h"
#include "ProjectReunionDeploymentStatus.h"
#include "Microsoft.Management.Deployment.ProjectReunionDeployment.g.cpp"

namespace winrt::Microsoft::Management::Deployment::implementation
{
    Microsoft::Management::Deployment::ProjectReunionDeploymentStatus ProjectReunionDeployment::GetStatus(Windows::ApplicationModel::PackageVersion const& packageVersion)
    {
        //return winrt::make<winrt::Microsoft::Management::Deployment::ProjectReunionDeploymentStatus>(false, false);
        throw hresult_not_implemented();
    }

    Windows::Foundation::Uri ProjectReunionDeployment::GetProjectReunionPackageLink()
    {
        return Windows::Foundation::Uri(PROJECT_REUNION_INSTALL_INFORMATION_URI);
    }

    Windows::Foundation::Uri ProjectReunionDeployment::GetProjectReunionInstallInformationLink()
    {
        return Windows::Foundation::Uri(PROJECT_REUNION_PACKAGE_INSTALL_URI);
    }
}
