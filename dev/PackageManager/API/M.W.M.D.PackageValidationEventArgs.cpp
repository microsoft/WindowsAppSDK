// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.M.D.PackageValidationEventArgs.h"
#include "Microsoft.Windows.Management.Deployment.PackageValidationEventArgs.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageValidationEventArgs::PackageValidationEventArgs(winrt::Windows::Foundation::Uri const& packageUri, winrt::Windows::Foundation::IInspectable const& appxObject)
    {
        m_packageUri = packageUri;
        m_appxObject = appxObject;
    }

    winrt::Windows::Foundation::Uri PackageValidationEventArgs::PackageUri()
    {
        return m_packageUri;
    }
    winrt::Windows::Foundation::IInspectable PackageValidationEventArgs::AppxPackagingObject()
    {
        return m_appxObject;
    }

    bool PackageValidationEventArgs::Cancel()
    {
        return m_cancel;
    }
    void PackageValidationEventArgs::Cancel(bool value)
    {
        m_cancel = value;
    }
}
