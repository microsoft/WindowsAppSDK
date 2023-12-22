// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

#include "M.W.M.D.ProvisionPackageOptions.h"
#include "Microsoft.Windows.Management.Deployment.ProvisionPackageOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    bool ProvisionPackageOptions::IsOptionalPackageFamilyNamesSupported()
    {
        // Requires Windows >= 10.0.22000.0 (aka Win11 21H2)
        return WindowsVersion::IsWindows11_21H2OrGreater();
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> ProvisionPackageOptions::OptionalPackageFamilyNames()
    {
        if (!m_optionalPackageFamilyNames)
        {
            m_optionalPackageFamilyNames = winrt::single_threaded_vector<hstring>();
        }
        return m_optionalPackageFamilyNames;
    }
    bool ProvisionPackageOptions::IsProjectionOrderPackageFamilyNamesSupported()
    {
        // Requires Windows >= 10.0.22000.0 (aka Win11 21H2)
        return WindowsVersion::IsWindows11_21H2OrGreater();
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> ProvisionPackageOptions::ProjectionOrderPackageFamilyNames()
    {
        if (!m_projectionOrderPackageFamilyNames)
        {
            m_projectionOrderPackageFamilyNames = winrt::single_threaded_vector<hstring>();
        }
        return m_projectionOrderPackageFamilyNames;
    }
}
