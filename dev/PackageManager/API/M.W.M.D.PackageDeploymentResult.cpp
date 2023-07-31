// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentResult.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentResult.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageDeploymentResult::PackageDeploymentResult(winrt::guid const& activityId) :
        m_activityId(activityId)
    {
    }

    winrt::guid PackageDeploymentResult::ActivityId()
    {
        return m_activityId;
    }
}
