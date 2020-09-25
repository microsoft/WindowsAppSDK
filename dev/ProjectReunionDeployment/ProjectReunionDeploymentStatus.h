// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Deployment.ProjectReunionDeploymentStatus.g.h"

namespace winrt::Microsoft::ProjectReunion::Deployment::implementation
{
    struct ProjectReunionDeploymentStatus : ProjectReunionDeploymentStatusT<ProjectReunionDeploymentStatus>
    {
        ProjectReunionDeploymentStatus(bool osUpdatesRequired, bool packageInstallRequired) :
            m_osUpdatesRequired(osUpdatesRequired),
            m_packageInstallRequired(packageInstallRequired)
        {
        };

        bool IsOK();
        bool WindowsUpdatesRequired();
        bool PackageInstallRequired();

    private:
        bool m_osUpdatesRequired = false;
        bool m_packageInstallRequired = false;
    };
}

