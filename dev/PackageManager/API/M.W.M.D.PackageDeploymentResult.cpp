// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentResult.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentResult.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageDeploymentResult::PackageDeploymentResult(
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus status,
        winrt::guid const& activityId) :
        m_status(status),
        m_activityId(activityId)
    {
    }

    PackageDeploymentResult::PackageDeploymentResult(
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus status,
        winrt::guid const& activityId,
        winrt::hresult const& error,
        winrt::hresult const& extendedError,
        winrt::hstring const& errorText) :
        m_status(status),
        m_error(error),
        m_extendedError(extendedError),
        m_errorText(errorText),
        m_activityId(activityId)
    {
    }

    winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus PackageDeploymentResult::Status()
    {
        return m_status;
    }
    winrt::hresult PackageDeploymentResult::Error()
    {
        return m_error;
    }
    winrt::hresult PackageDeploymentResult::ExtendedError()
    {
        return m_extendedError;
    }
    winrt::hstring PackageDeploymentResult::ErrorText()
    {
        return m_errorText;
    }
    winrt::guid PackageDeploymentResult::ActivityId()
    {
        return m_activityId;
    }
}
