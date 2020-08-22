// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "M.AM.DD.PackageDependency.h"
#include "Microsoft.ApplicationModel.DynamicDependency.PackageDependency.g.cpp"

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    Microsoft::ApplicationModel::DynamicDependency::PackageDependency PackageDependency::GetFromId(hstring const& id)
    {
        throw hresult_not_implemented();
    }
    Microsoft::ApplicationModel::DynamicDependency::PackageDependency PackageDependency::Create(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion)
    {
        throw hresult_not_implemented();
    }
    Microsoft::ApplicationModel::DynamicDependency::PackageDependency PackageDependency::Create(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion, Microsoft::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options)
    {
        throw hresult_not_implemented();
    }
    Microsoft::ApplicationModel::DynamicDependency::PackageDependency PackageDependency::CreateForUser(Windows::System::User const& user, hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion, Microsoft::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options)
    {
        throw hresult_not_implemented();
    }
    Microsoft::ApplicationModel::DynamicDependency::PackageDependency PackageDependency::CreateForSystem(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion, Microsoft::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options)
    {
        throw hresult_not_implemented();
    }
    hstring PackageDependency::Id()
    {
        throw hresult_not_implemented();
    }
    void PackageDependency::Delete()
    {
        throw hresult_not_implemented();
    }
    Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContext PackageDependency::Add()
    {
        throw hresult_not_implemented();
    }
    Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContext PackageDependency::Add(Microsoft::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options)
    {
        throw hresult_not_implemented();
    }
}
