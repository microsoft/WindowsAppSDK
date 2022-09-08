// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Helpers.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

class TestResourceLinks
{
protected:
    BuildHelper m_build;
    PriSectionBuilder* m_priBuilder;
    HierarchicalSchemaSectionBuilder* m_schema;
    ResourceLinkSectionBuilder* m_linkBuilder;
    ResourceLinkSection* m_links;

public:
    TestResourceLinks();

    HRESULT InitFromTestVars(_In_ PriSectionBuilder* priBuilder, _In_ PCWSTR varPrefix);

    ~TestResourceLinks() { Release(); }
    void Release();

    ResourceLinkSectionBuilder* GetResourceLinksBuilder() const { return m_linkBuilder; }
    ResourceLinkSection* GetResourceLinks() const { return m_links; }

    HRESULT Finalize();

    HRESULT Build();

    HRESULT CreateReader();

    static HRESULT VerifyAgainstTestVars(_In_ IResourceLinks* links, _In_ PCWSTR varPrefix);

    static bool TryAddLinksFromTestVars(_In_ IResourceLinkBuilder* linkBuilder, _In_ PCWSTR varPrefix);
};

} // namespace UnitTests
