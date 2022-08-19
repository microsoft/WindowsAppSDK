// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "Helpers.h"
#include "mrm/build/Base.h"

#include "mrm/readers/MrmReaders.h"
#include "mrm/build/MrmBuilders.h"

#include "TestPri.h"
#include "TestMap.h"
#include "TestLinks.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{
class ResourceLinkUnitTests : public WEX::TestClass<ResourceLinkUnitTests>
{
public:
    TEST_CLASS(ResourceLinkUnitTests);

    BEGIN_TEST_METHOD(SimpleBuilderReaderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:ResourceLink.UnitTests.xml#SimpleLinkTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(LargeDataTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:ResourceLink.UnitTests.xml#LargeDataTests")
    END_TEST_METHOD();
};

void ResourceLinkUnitTests::SimpleBuilderReaderTests()
{
    String tmp;

    TestHPri pri;
    TestResourceMap testMap;
    TestResourceLinks testLinks;
    AutoDeletePtr<CoreProfile> profile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&profile));

    Log::Comment(L"[ Setting up test PRI ]");
    if (FAILED(pri.Init(profile)))
    {
        Log::Error(L"[ Couldn't init TestPri ]");
        return;
    }

    AutoDeletePtr<PriSectionBuilder> priBuilder;
    VERIFY_SUCCEEDED(PriSectionBuilder::CreateInstance(pri.GetFileBuilder(), profile, &priBuilder));
    if (FAILED(testMap.InitFromTestVars(priBuilder, nullptr, L"", L"", TestResourceMap::AddAllAsPrimary)))
    {
        Log::Error(L"[ Couldn't load resource map test data ]");
        return;
    }

    //    HierarchicalSchemaSectionBuilder* schemaBuilder = testMap.GetSchemaBuilder();

    if (FAILED(testLinks.InitFromTestVars(priBuilder, L"Test")))
    {
        Log::Error(L"[ Couldn't load resource link test data ]");
    }

    if (FAILED(testMap.Finalize()))
    {
        Log::Error(L"[ Couldn't finalize schema and/or map ]");
        return;
    }

    if (FAILED(testLinks.Finalize()))
    {
        Log::Error(L"[ Couldn't finalize links section ]");
        return;
    }

    // Now build the link section.  In the real world the map would be built as part of the
    // package, but we're a test case.
    VERIFY_SUCCEEDED(testLinks.Build());

    // Now we have to read the compiled links back into something we can use...
    if (FAILED(testLinks.CreateReader()))
    {
        Log::Error(L"Couldn't read back resource links section");
    }

    TestResourceLinks::VerifyAgainstTestVars(testLinks.GetResourceLinks(), L"Test");
}

static PCWSTR pPossibleContrastValues[] = {L"standard", L"high", L"black", L"white"};

static PCWSTR pPossibleScaleValues[] = {L"100", L"140", L"180", L"80"};

static PCWSTR pPossibleLanguageValues[] = {L"ar-SA",       L"be-BY",      L"bg-BG",      L"ca-ES",      L"ca-es-valencia",
                                           L"chr-cher-us", L"cs-CZ",      L"da-DK",      L"de-DE",      L"el-GR",
                                           L"en-GB",       L"en-US",      L"es-ES",      L"et-EE",      L"fi-FI",
                                           L"fr-FR",       L"gd-GB",      L"he-IL",      L"hi-IN",      L"hr-HR",
                                           L"hu-HU",       L"it-IT",      L"ja-JP",      L"kn-IN",      L"ko-KR",
                                           L"ku-arab-IQ",  L"lt-LT",      L"lv-LV",      L"nb-NO",      L"nl-NL",
                                           L"pa-arab-PK",  L"pl-PL",      L"pt-BR",      L"pt-PT",      L"quc-Latn-GT",
                                           L"ro-RO",       L"ru-RU",      L"rw-RW",      L"sd-arab-PK", L"sk-SK",
                                           L"sl-SI",       L"sr-cyrl-CS", L"sr-latn-CS", L"sv-SE",      L"te-IN",
                                           L"tg-cyrl-tj",  L"th-TH",      L"ti-ET",      L"tr-TR",      L"ug-CN",
                                           L"uk-UA",       L"wo-SN",      L"zh-CN",      L"zh-hk",      L"zh-tw",
                                           L"ar",          L"be",         L"bg",         L"ca",         L"chr",
                                           L"cs",          L"da",         L"de",         L"el",         L"en",
                                           L"es",          L"et",         L"fi",         L"fr",         L"gd",
                                           L"he",          L"hi",         L"hr",         L"hu",         L"it",
                                           L"ja",          L"kn",         L"ko",         L"lt",         L"lv",
                                           L"nb",          L"nl",         L"pl",         L"pt",         L"quc",
                                           L"ro",          L"ru",         L"rw",         L"sk",         L"sl",
                                           L"sr-cyrl",     L"nv",         L"te",         L"th",         L"ti",
                                           L"tr",          L"ug",         L"uk",         L"wo",         L"zh"};

static bool BuildQualifierSet(
    _Inout_ DecisionInfoBuilder* pDI,
    _Inout_ DecisionInfoQualifierSetBuilder* pQSB,
    _In_ bool bUseDefaults,
    _In_opt_ const MrmBcQualifier* pQ1 = nullptr,
    _In_opt_ const MrmBcQualifier* pQ2 = nullptr,
    _In_opt_ const MrmBcQualifier* pQ3 = nullptr)
{
    String tmp;
    int numQualifiers = 0;
    MrmBcQualifier qualifiers[3];

    if (pQ1 != NULL)
    {
        qualifiers[numQualifiers++] = *pQ1;
    }
    if (pQ2 != NULL)
    {
        qualifiers[numQualifiers++] = *pQ2;
    }
    if (pQ3 != NULL)
    {
        qualifiers[numQualifiers++] = *pQ3;
    }

    pQSB->Reset();

    if (numQualifiers > 0)
    {
        Log::Comment(L"[ Building Qualifier set: ]");
        for (int i = 0; i < numQualifiers; i++)
        {
            Log::Comment(tmp.Format(
                L"[     %s = %s (%d, %lg) ]",
                qualifiers[i].QualifierName,
                qualifiers[i].QualifierValue,
                qualifiers[i].Priority,
                qualifiers[i].FallbackScore));
        }

        HRESULT hr = pQSB->AddQualifiers(numQualifiers, &qualifiers[0], bUseDefaults);
        if (FAILED(hr))
        {
            Log::Error(tmp.Format(L"[ Failed to add qualifiers to QualifierSetBuilder (0x%x) ]", hr));
            return false;
        }
    }
    else
    {
        Log::Comment(L"[ Empty qualifier set ]");
    }

    HRESULT hr = pDI->GetOrAddQualifierSet(pQSB, nullptr, NULL);
    if (FAILED(hr))
    {
        Log::Error(tmp.Format(L"[ Failed to add qualifier set to decision info (0x%x) ]", hr));
        return false;
    }
    Log::Comment(L"[ Added qualifier set ]");
    return true;
}

static bool GenerateQualifierSets(_Inout_ PriSectionBuilder* pPriBuilder, _Inout_ DecisionInfoBuilder* pDI, _In_ int nSetsWanted)
{
    String tmp;

    AutoDeletePtr<DecisionInfoQualifierSetBuilder> pQSB;
    VERIFY_SUCCEEDED(pPriBuilder->GetQualifierSetBuilder(&pQSB));
    if (pQSB == nullptr)
    {
        Log::Error(tmp.Format(L"[ Failed to create QualifierSetBuilder ]"));
        return false;
    }

    bool allBuilt = false;
    int nSetsBuilt = 0;

    Log::Comment(tmp.Format(L"[ Adding %d qualifier sets ]", nSetsWanted));

    // first generate a qualifier set for each possible scale
    for (int iScale = 0; (iScale < ARRAYSIZE(pPossibleScaleValues)) && (!allBuilt); iScale++)
    {
        MrmBcQualifier scaleQualifier = {CoreEnvironment::Qualifier_Scale, pPossibleScaleValues[iScale], 500, 0.0};

        if (BuildQualifierSet(pDI, pQSB, true, &scaleQualifier))
        {
            if (nSetsBuilt++ >= nSetsWanted)
            {
                allBuilt = true;
                break;
            }
            VERIFY(pDI->GetNumQualifierSets() == nSetsBuilt + 1);
        }
        else
        {
            Log::Error(tmp.Format(L"[ Failed to build qualifier set %d ]", nSetsBuilt));
            return false;
        }
    }

    // next generate a qualifier set for each possible contrast
    for (int iContrast = 0; (iContrast < ARRAYSIZE(pPossibleContrastValues)) && (!allBuilt); iContrast++)
    {
        MrmBcQualifier contrastQualifier = {CoreEnvironment::Qualifier_Contrast, pPossibleContrastValues[iContrast], 700, 0.0};

        if (BuildQualifierSet(pDI, pQSB, true, &contrastQualifier))
        {
            if (nSetsBuilt++ >= nSetsWanted)
            {
                allBuilt = true;
                break;
            }
            VERIFY(pDI->GetNumQualifierSets() == nSetsBuilt + 1);
        }
        else
        {
            Log::Error(tmp.Format(L"[ Failed to build qualifier set %d ]", nSetsBuilt));
            return false;
        }
    }

    // now for each combination of scale and contrast
    for (int iScale = 0; (iScale < ARRAYSIZE(pPossibleScaleValues)) && (!allBuilt); iScale++)
    {
        MrmBcQualifier scaleQualifier = {CoreEnvironment::Qualifier_Scale, pPossibleScaleValues[iScale], 500, 0.0};

        for (int iContrast = 0; (iContrast < ARRAYSIZE(pPossibleContrastValues)) && (!allBuilt); iContrast++)
        {
            MrmBcQualifier contrastQualifier = {CoreEnvironment::Qualifier_Contrast, pPossibleContrastValues[iContrast], 700, 0.0};

            if (BuildQualifierSet(pDI, pQSB, true, &scaleQualifier, &contrastQualifier))
            {
                if (nSetsBuilt++ >= nSetsWanted)
                {
                    allBuilt = true;
                    break;
                }
                VERIFY(pDI->GetNumQualifierSets() == nSetsBuilt + 1);
            }
            else
            {
                Log::Error(tmp.Format(L"[ Failed to build qualifier set %d ]", nSetsBuilt));
                return false;
            }
        }
    }

    // Now for each language
    for (int iLang = 0; (iLang < ARRAYSIZE(pPossibleLanguageValues)) && (!allBuilt); iLang++)
    {
        MrmBcQualifier langQualifier = {CoreEnvironment::Qualifier_Language, pPossibleLanguageValues[iLang], 900, 0.0};

        if (BuildQualifierSet(pDI, pQSB, true, &langQualifier))
        {
            if (nSetsBuilt++ >= nSetsWanted)
            {
                allBuilt = true;
                break;
            }
            VERIFY(pDI->GetNumQualifierSets() == nSetsBuilt + 1);
        }
        else
        {
            Log::Error(tmp.Format(L"[ Failed to build qualifier set %d ]", nSetsBuilt));
            return false;
        }
    }

    // And finally, for each combination of language and scale
    for (int iLang = 0; (iLang < ARRAYSIZE(pPossibleLanguageValues)) && (!allBuilt); iLang++)
    {
        MrmBcQualifier langQualifier = {CoreEnvironment::Qualifier_Language, pPossibleLanguageValues[iLang], 900, 0.0};

        for (int iScale = 0; (iScale < ARRAYSIZE(pPossibleScaleValues)) && (!allBuilt); iScale++)
        {
            MrmBcQualifier scaleQualifier = {CoreEnvironment::Qualifier_Scale, pPossibleScaleValues[iScale], 500, 0.0};

            if (BuildQualifierSet(pDI, pQSB, true, &langQualifier, &scaleQualifier))
            {
                if (nSetsBuilt++ >= nSetsWanted)
                {
                    allBuilt = true;
                    break;
                }
                VERIFY(pDI->GetNumQualifierSets() == nSetsBuilt + 1);
            }
            else
            {
                Log::Error(tmp.Format(L"[ Failed to build qualifier set %d ]", nSetsBuilt));
                return false;
            }
        }
    }

    if (!allBuilt)
    {
        Log::Error(tmp.Format(L"[ Don't have enough data to create %d qualifier sets (%d created) ]", nSetsWanted, nSetsBuilt));
        return false;
    }
    return true;
}

static bool GenerateCandidates(
    _Inout_ ResourceMapSectionBuilder* pMapBuilder,
    _In_ int numResources,
    _In_ int numCandidatesPerResource,
    _In_ PCWSTR pNameFormat,
    _In_ PCWSTR pValueFormat)
{
    HRESULT hr = S_OK;
    String tmp;

    Log::Comment(tmp.Format(L"[ Adding %d named resources with %d candidates each ]", numResources, numCandidatesPerResource));

    WCHAR resBuf[20];
    WCHAR valueBuf[20];

    for (int iResource = 0; iResource < numResources; iResource++)
    {
        hr = StringCchPrintf(resBuf, ARRAYSIZE(resBuf), pNameFormat, (iResource / 100), (iResource % 100));
        if (FAILED(hr))
        {
            Log::Error(tmp.Format(L"[ Couldn't create resource name (0x%x) ]", hr));
            return false;
        }

        // throttle logging based on number of resources to be generated
        if ((numResources < 100) || ((numResources < 1000) && ((iResource % 10) == 0)) || ((iResource % 100) == 0))
        {
            Log::Comment(tmp.Format(L"[ Adding \"%s\" ]", resBuf));
        }

        for (int iCandidate = 0; iCandidate < numCandidatesPerResource; iCandidate++)
        {
            hr = StringCchPrintf(valueBuf, ARRAYSIZE(valueBuf), pValueFormat, resBuf, iCandidate);
            if (FAILED(hr))
            {
                Log::Error(tmp.Format(L"[ Couldn't create resource value (0x%x) ]", hr));
                return false;
            }

            hr = pMapBuilder->AddCandidateWithInternalString(resBuf, MrmEnvironment::ResourceValueType_Utf16String, valueBuf, iCandidate);
            if (FAILED(hr))
            {
                Log::Error(tmp.Format(L"[ Couldn't add candidate %d for %s (value=%s, status=0x%x) ]", iCandidate, resBuf, valueBuf, hr));
            }
        }
    }

    return true;
}

void ResourceLinkUnitTests::LargeDataTests()
{
    String tmp;

    TestHPri pri;
    TestResourceLinks testLinks;
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    Log::Comment(L"[ Setting up test PRI ]");
    if (FAILED(pri.Init(pProfile)))
    {
        Log::Error(L"[ Couldn't init TestPri ]");
        return;
    }

    PriSectionBuilder* pPriBuilder = pri.GetPriFileBuilder()->GetDescriptor();

    HierarchicalSchemaSectionBuilder* pSchemaBuilder;
    VERIFY_SUCCEEDED(
        HierarchicalSchemaSectionBuilder::CreateInstance(pPriBuilder, L"ManyCandidates", L"ManyCandidates", 1, &pSchemaBuilder));
    if (pSchemaBuilder == nullptr)
    {
        Log::Error(tmp.Format(L"[ Failed to create schema ]"));
        return;
    }

    int index;
    HRESULT hr = pPriBuilder->AddSchemaBuilder(pSchemaBuilder, true, &index);
    if (FAILED(hr) || (index < 0))
    {
        delete pSchemaBuilder;
        Log::Error(tmp.Format(L"[ Failed to add schema builder (0x%x) ]", hr));
        return;
    }

    DecisionInfoBuilder* pDI = pPriBuilder->GetDecisionInfoBuilder();
    if (pDI == nullptr)
    {
        Log::Error(tmp.Format(L"[ Failed to get DecisionInfoBuilder ]"));
        return;
    }

    int numResources = -1;
    int numCandidatesPerResource = -1;
    String resNameFormat = L"Scope%d/Res%02d";
    String resValueFormat = L"%s-%d";

    if (FAILED(TestData::TryGetValue(L"NumResources", numResources)))
    {
        Log::Error(L"[ NumResources not defined ]");
        return;
    }

    if (FAILED(TestData::TryGetValue(L"NumCandidatesPerResource", numCandidatesPerResource)))
    {
        Log::Error(L"[ NumCandidatesPerResource not defined ]");
        return;
    }

    if (FAILED(TestData::TryGetValue(L"ResourceNameFormat", resNameFormat)))
    {
        Log::Warning(L"[ ResourceNameFormat not defined. Using default ]");
    }

    if (FAILED(TestData::TryGetValue(L"ResourceValueFormat", resValueFormat)))
    {
        Log::Warning(L"[ ResourceValueFormat not defined.  Using deafult ]");
    }

    GenerateQualifierSets(pPriBuilder, pDI, numCandidatesPerResource);

    ResourceMapSectionBuilder* pMapBuilder;
    VERIFY_SUCCEEDED(pPriBuilder->GetOrAddPrimaryResourceMapBuilder(&pMapBuilder));
    if (pMapBuilder == nullptr)
    {
        Log::Error(tmp.Format(L"[ Failed to add map builder ]"));
        return;
    }

    SYSTEMTIME start;
    SYSTEMTIME checkpoint;
    SYSTEMTIME elapsed;

    GetSystemTime(&start);
    Log::Comment(tmp.Format(
        L"[ Start generating candidates at: %02d:%02d:%02d.%03d ]", start.wHour, start.wMinute, start.wSecond, start.wMilliseconds));
    GenerateCandidates(pMapBuilder, numResources, numCandidatesPerResource, (PCWSTR)resNameFormat, (PCWSTR)resValueFormat);

    GetSystemTime(&checkpoint);
    ComputeElapsedTime(start, checkpoint, &elapsed);
    Log::Comment(tmp.Format(
        L"[ Done generating candidates at: %02d:%02d:%02d.%03d (elapsed: %02d:%02d:%02d:%03d) ]",
        checkpoint.wHour,
        checkpoint.wMinute,
        checkpoint.wSecond,
        checkpoint.wMilliseconds,
        elapsed.wHour,
        elapsed.wMinute,
        elapsed.wSecond,
        elapsed.wMilliseconds));

    if (FAILED(testLinks.InitFromTestVars(pPriBuilder, L"Test")))
    {
        Log::Error(L"[ Couldn't load resource link test data ]");
        return;
    }

    if (FAILED(testLinks.Finalize()))
    {
        Log::Error(L"[ Couldn't finalize links section ]");
        return;
    }

    // Now build the link section.  In the real world the map would be built as part of the
    // package, but we're a test case.
    VERIFY_SUCCEEDED(testLinks.Build());

    // Now we have to read the compiled links back into something we can use...
    if (FAILED(testLinks.CreateReader()))
    {
        Log::Error(L"Couldn't read back resource links section");
    }

    TestResourceLinks::VerifyAgainstTestVars(testLinks.GetResourceLinks(), L"Test");
}

} // namespace UnitTests
