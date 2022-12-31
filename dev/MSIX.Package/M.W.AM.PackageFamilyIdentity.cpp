// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.PackageFamilyIdentity.h"

#include "Microsoft.Windows.ApplicationModel.PackageFamilyIdentity.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    PackageFamilyIdentity::PackageFamilyIdentity(hstring const& name, hstring const& publisherId) :
        m_name(name), m_publisherId(publisherId)
    {
    }
    hstring PackageFamilyIdentity::Name()
    {
        return m_name;
    }
    void PackageFamilyIdentity::Name(hstring const& value)
    {
        m_name = value;
    }
    hstring PackageFamilyIdentity::PublisherId()
    {
        return m_publisherId;
    }
    void PackageFamilyIdentity::PublisherId(hstring const& value)
    {
        m_publisherId = value;
    }
}
