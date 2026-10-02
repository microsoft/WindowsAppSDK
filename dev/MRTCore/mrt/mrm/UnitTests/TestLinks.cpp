// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include <mrm/build/AIDict.h>
#include "Helpers.h"
#include "TestLinks.h"
#include "TestUtils.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

TestResourceLinks::TestResourceLinks() : m_build(), m_priBuilder(nullptr), m_schema(nullptr), m_linkBuilder(nullptr), m_links(nullptr) {}

HRESULT
TestResourceLinks::InitFromTestVars(_In_ PriSectionBuilder* priBuilder, _In_ PCWSTR varPrefix)
{
    String tmp;
    String simpleid;

    Release();

    m_priBuilder = priBuilder;

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sSimpleId", varPrefix), simpleid)))
    {
        m_schema = priBuilder->GetSchemaBuilder(simpleid);
        VERIFY(m_schema != nullptr);
    }
    else
    {
        ResourceMapSectionBuilder* mapBuilder;
        VERIFY_SUCCEEDED(priBuilder->GetOrAddPrimaryResourceMapBuilder(&mapBuilder));

        m_schema = mapBuilder->GetSchema();
        VERIFY(m_schema != nullptr);
    }

    VERIFY_SUCCEEDED(ResourceLinkSectionBuilder::CreateInstance(m_schema, &m_linkBuilder));

    if (TryAddLinksFromTestVars(m_linkBuilder, varPrefix))
    {
        return S_OK;
    }
    return E_FAIL;
}

void TestResourceLinks::Release()
{
    delete m_linkBuilder;
    delete m_links;
}

HRESULT
TestResourceLinks::Build() { return m_build.Build(m_linkBuilder); }

HRESULT
TestResourceLinks::CreateReader()
{
    return ResourceLinkSection::CreateInstance(
        nullptr, nullptr, gResourceLinkSectionType, m_build.GetBuffer(), m_build.GetBufferSize(), &m_links);
}

HRESULT
TestResourceLinks::Finalize() { return m_linkBuilder->Finalize(); }

bool TestResourceLinks::TryAddLinksFromTestVars(_In_ IResourceLinkBuilder* linkBuilder, _In_ PCWSTR varPrefix)
{
    TestDataArray<String> links;
    String tmp;

    Log::Comment(tmp.Format(L"[ Adding %sResourceLinks ]", varPrefix));
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sResourceLinks", varPrefix), links)))
    {
        HierarchicalSchemaSectionBuilder* schema = linkBuilder->GetSchema();
        if (schema != nullptr)
        {
            TestStringArray link;

            for (unsigned i = 0; i < links.GetSize(); i++)
            {
                Log::Comment(tmp.Format(L"[ link %d: \"%s\" ]", i, (PCWSTR)links[i]));
                if (!link.InitFromList(links[i]) || ((link.GetNumStrings() < 2) || (link.GetNumStrings() > 3)))
                {
                    Log::Warning(L"  [ Couldn't parse link string ]");
                    continue;
                }

                Atom::Index fromIndex;
                Atom::Index toIndex;

                if (!schema->GetItemNames()->TryGetIndex(link.GetString(0), &fromIndex))
                {
                    Log::Warning(tmp.Format(L"  [ Cannot link from unknown resource \"%s\" ]", link.GetString(0)));
                    continue;
                }

                if (!schema->GetItemNames()->TryGetIndex(link.GetString(1), &toIndex))
                {
                    Log::Warning(tmp.Format(L"  [ Cannot link to unknown resource \"%s\" ]", link.GetString(1)));
                    continue;
                }

                HRESULT hr = linkBuilder->AddResourceLink(link.GetString(0), link.GetString(1));
                bool ok = SUCCEEDED(hr);

                if (link.GetNumStrings() == 3)
                {
                    TestUtils::ValidateReturnAndStatus(ok, link.GetString(2), hr);
                }
                else if (!ok)
                {
                    Log::Warning(
                        tmp.Format(L"  [ Could not add link from \"%s\" to \"%s\" (0x%x) ]", link.GetString(0), link.GetString(1), hr));
                }
            }
        }
        else
        {
            Log::Warning(L"[ Error getting schema for linkBuilder ]");
            return false;
        }
    }

    Log::Comment(tmp.Format(L"[ Done adding %sResourceLinks ]", varPrefix));
    return true;
}

HRESULT
TestResourceLinks::VerifyAgainstTestVars(_In_ IResourceLinks* links, _In_ PCWSTR varPrefix)
{
    TestDataArray<String> specs;
    String tmp;
    String specString;
    int expectedCount;

    Log::Comment(tmp.Format(L"[ Verifying links for \"%s\" ]", varPrefix));

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumInternalLinks", varPrefix), expectedCount)))
    {
        Log::Comment(tmp.Format(L"[ %sExpectedNumInternalLinks = %d  ]", varPrefix, expectedCount));
        VERIFY_ARE_EQUAL(links->GetNumInternalLinks(), expectedCount);
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumInternalLinks not defined ]", varPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedInternalLinks", varPrefix), specString)))
    {
        TestStringArray spec;
        if (spec.InitFromList(specString))
        {
            int expectedIndex;

            Log::Comment(tmp.Format(L"[ Found %d %sExpectedInternalLinks ]", (int)spec.GetNumStrings(), varPrefix));
            for (int i = 0; i < spec.GetNumStrings(); i++)
            {
                if (spec.TryGetStringAsInt(i, &expectedIndex))
                {
                    UINT32 gotIndex;
                    VERIFY_SUCCEEDED(links->GetInternalResourceLink(i, nullptr, &gotIndex));
                    VERIFY_ARE_EQUAL(static_cast<UINT32>(expectedIndex), gotIndex);
                }
                else
                {
                    Log::Warning(tmp.Format(L"[ Malformed expected internal link info \"%s\" - must be integer]", (PCWSTR)specString));
                }
            }
        }
        else
        {
            Log::Warning(tmp.Format(L"[ Error parsing spec \"%s\" in %sExpectedInternalLinks ]", (PCWSTR)specString, varPrefix));
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %sExpectedInternalLinks not defined ]", varPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumLinksById", varPrefix), expectedCount)))
    {
        Log::Comment(tmp.Format(L"[ %sExpectedNumLinksById = %d  ]", varPrefix, expectedCount));
        VERIFY_ARE_EQUAL(links->GetNumLinksByResourceIndex(), expectedCount);
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumLinksById not defined ]", varPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedLinkById", varPrefix), specs)))
    {
        Log::Comment(tmp.Format(L"[ Found %d %sExpectedLinksById ]", (int)specs.GetSize(), varPrefix));
        for (unsigned i = 0; i < specs.GetSize(); i++)
        {
            TestStringArray spec;
            int linkIndex;

            Log::Comment(tmp.Format(L"[     %d: %s ]", i, (PCWSTR)specs[i]));
            if (spec.InitFromList(specs[i]) && spec.TryGetStringAsInt(0, &linkIndex))
            {
                PCWSTR linkType = spec.GetString(1);

                if (DefString_IEqual(linkType, L"internal"))
                {
                    int expectedLinkFromResourceIndex;
                    int expectedLinkToResourceIndex;
                    UINT32 gotLinkFromResourceIndex;
                    UINT32 gotLinkToResourceIndex;
                    const IHierarchicalSchema* gotSchema;

                    if (spec.TryGetStringAsInt(2, &expectedLinkFromResourceIndex) &&
                        spec.TryGetStringAsInt(3, &expectedLinkToResourceIndex))
                    {
                        VERIFY_SUCCEEDED(
                            links->GetResourceLinkById(linkIndex, &gotLinkFromResourceIndex, &gotSchema, &gotLinkToResourceIndex));
                        VERIFY_ARE_EQUAL(static_cast<UINT32>(expectedLinkFromResourceIndex), gotLinkFromResourceIndex);
                        VERIFY_ARE_EQUAL(static_cast<UINT32>(expectedLinkToResourceIndex), gotLinkToResourceIndex);
                        VERIFY_ARE_EQUAL(links->GetSchema(), gotSchema);

                        VERIFY(links->TryGetResourceLinkForResourceIndex(expectedLinkFromResourceIndex, nullptr, &gotLinkToResourceIndex));
                        VERIFY_ARE_EQUAL(static_cast<UINT32>(expectedLinkToResourceIndex), gotLinkToResourceIndex);
                    }
                    else
                    {
                        Log::Warning(tmp.Format(L"[ Malformed expected internal link info \"%s\" - must be 2 integers]", (PCWSTR)specs[i]));
                    }
                }
                else
                {
                    Log::Warning(tmp.Format(L"[ Unknown link type \"%s\" ignored ]", linkType));
                    continue;
                }
            }
            else
            {
                Log::Warning(tmp.Format(L"[ Error parsing spec \"%s\" in %sExpectedInternalLinks ]", (PCWSTR)specString, varPrefix));
            }
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %sExpectedLinksById not defined ]", varPrefix));
    }

    return S_OK;
}

} // namespace UnitTests
