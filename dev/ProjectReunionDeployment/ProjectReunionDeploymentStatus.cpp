// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ProjectReunionDeploymentStatus.h"
#include "Microsoft.Management.Deployment.ProjectReunionDeploymentStatus.g.cpp"

namespace winrt::Microsoft::Management::Deployment::implementation
{
    bool ProjectReunionDeploymentStatus::IsOK()
    {
        return !m_osUpdatesRequired && !m_packageInstallRequired;
    }

    bool ProjectReunionDeploymentStatus::WindowsUpdatesRequired()
    {
        return m_osUpdatesRequired;
    }

    bool ProjectReunionDeploymentStatus::PackageInstallRequired()
    {
        return m_packageInstallRequired;
    }
}
