// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <appmodel.h>

#include <MsixDynamicDependency.h>

#include <wil/resource.h>
#include <wil_msixdynamicdependency.h>

namespace MddCore
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
        m_addDllDirectoryCookie(std::move(other.m_addDllDirectoryCookie))
    {
    }

    PackageGraphNode& operator=(PackageGraphNode&& other)
    {
        if (this != &other)
        {
            Reset();
            m_packageInfoReference = std::move(other.m_packageInfoReference);
            m_context = std::move(other.m_context);
            m_addDllDirectoryCookie = std::move(other.m_addDllDirectoryCookie);
        }
        return *this;
    }

    void Reset()
    {
        m_packageInfoReference.reset();
        m_context.reset();
        m_addDllDirectoryCookie.reset();
    }

private:
    wil::unique_package_info_reference m_packageInfoReference;
    wil::unique_package_dependency_context m_context;
    wil::unique_dll_directory_cookie m_addDllDirectoryCookie;
};
}
