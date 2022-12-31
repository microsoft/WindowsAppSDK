// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.PackageFamilyIdentity.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct PackageFamilyIdentity : PackageFamilyIdentityT<PackageFamilyIdentity>
    {
        PackageFamilyIdentity() = default;
        PackageFamilyIdentity(hstring const& name, hstring const& publisherId);

        hstring Name();
        void Name(hstring const& value);
        hstring PublisherId();
        void PublisherId(hstring const& value);

    private:
        hstring m_name;
        hstring m_publisherId;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct PackageFamilyIdentity : PackageFamilyIdentityT<PackageFamilyIdentity, implementation::PackageFamilyIdentity>
    {
    };
}
