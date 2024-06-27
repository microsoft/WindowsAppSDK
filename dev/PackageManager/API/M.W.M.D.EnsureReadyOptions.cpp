// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

#include "M.W.M.D.EnsureReadyOptions.h"
#include "Microsoft.Windows.Management.Deployment.EnsureReadyOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions EnsureReadyOptions::AddPackageOptions()
    {
        return m_addPackageOptions;
    }
    bool EnsureReadyOptions::RegisterNewerIfAvailable()
    {
        return m_registerNewerIfAvailable;
    }
    void EnsureReadyOptions::RegisterNewerIfAvailable(bool value)
    {
        m_registerNewerIfAvailable = value;
    }
}
