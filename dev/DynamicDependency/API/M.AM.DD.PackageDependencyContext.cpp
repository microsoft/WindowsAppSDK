// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.AM.DD.PackageDependencyContext.h"
#include "Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContext.g.cpp"

#include <M.AM.Converters.h>

namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::implementation
{
    PackageDependencyContext::PackageDependencyContext(Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId const& contextId) :
        m_contextId(contextId)
    {
    }
    PackageDependencyContext::PackageDependencyContext(MDD_PACKAGEDEPENDENCY_CONTEXT context) :
        m_contextId(::Microsoft::Windows::ApplicationModel::DynamicDependency::ToContextId(context))
    {
    }
    winrt::PackageDependencyContextId PackageDependencyContext::ContextId()
    {
        return m_contextId;
    }

    hstring PackageDependencyContext::PackageDependencyId()
    {
        wil::unique_process_heap_string id;
        winrt::check_hresult(MddGetIdForPackageDependencyContext(::Microsoft::Windows::ApplicationModel::DynamicDependency::ToContext(m_contextId), wil::out_param(id)));
        return winrt::hstring(id.get());
    }

    hstring PackageDependencyContext::PackageFullName()
    {
        auto id{ PackageDependencyId() };
        wil::unique_process_heap_string packageFullName;
        winrt::check_hresult(MddGetResolvedPackageFullNameForPackageDependency(id.c_str(), wil::out_param(packageFullName)));
        return winrt::hstring(packageFullName.get());
    }

    void PackageDependencyContext::Remove()
    {
        MddRemovePackageDependency(::Microsoft::Windows::ApplicationModel::DynamicDependency::ToContext(m_contextId));
    }
}
