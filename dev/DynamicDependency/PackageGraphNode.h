// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <appmodel.h>

#include <MsixDynamicDependency.h>

#include <wil/resource.h>
#include <wil_msixdynamicdependency.h>

namespace Microsoft::ApplicationModel::DynamicDepedency
{
class PackageGraphNode
{
public:
    PackageGraphNode() = default;

    ~PackageGraphNode()
    {
        Reset();
    }

    PackageGraphNode(PackageGraphNode&& other) :
        m_packageInfoReference(std::move(other.m_packageInfoReference)),
        m_context(std::move(other.m_context)),
        m_addDllDirectoryCookie(other.m_addDllDirectoryCookie)
    {
        other.m_addDllDirectoryCookie = 0;
    }

    PackageGraphNode& operator=(PackageGraphNode&& other)
    {
        if (this != &other)
        {
            Reset();
            m_packageInfoReference = std::move(other.m_packageInfoReference);
            m_context = std::move(other.m_context);
            m_addDllDirectoryCookie = other.m_addDllDirectoryCookie;

            other.m_addDllDirectoryCookie = 0;
        }
        return *this;
    }

    void Reset()
    {
        m_packageInfoReference.reset();

        m_context.reset();

        if (m_addDllDirectoryCookie != 0)
        {
            (void)LOG_IF_WIN32_BOOL_FALSE(RemoveDllDirectory(m_addDllDirectoryCookie));
            m_addDllDirectoryCookie = 0;
        }
    }

private:
    wil::unique_package_info_reference m_packageInfoReference;
    wil::unique_package_dependency_context m_context;
    DLL_DIRECTORY_COOKIE m_addDllDirectoryCookie{};
};
}
