// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include <mrm/build/AIDict.h>
#include "TestHSchema.h"
#include "TestMap.h"
#include "TestPri.h"
#include "TestUtils.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

TestHPri::TestHPri() :
    m_priBuilder(nullptr),
    m_schemas(nullptr),
    m_maps(nullptr),
    m_sections(nullptr),
    m_buffer(nullptr),
    m_bufferSizeInBytes(0),
    m_pri(nullptr),
    m_baselinePri(nullptr),
    m_expectedFinalizeResult(0),
    m_expectedFinalizeReturn(true),
    m_expectedBuildResult(0),
    m_expectedBuildReturn(true)
{}

HRESULT
TestHPri::Init(_In_ CoreProfile* profile)
{
    Release();
    return PriFileBuilder::CreateInstance(profile, &m_priBuilder);
}

HRESULT
TestHPri::InitWithBaseline(_In_ PCWSTR baselineFile, _In_ PCWSTR baselineSchemaName, _In_ CoreProfile* profile)
{
    Release();

    RETURN_IF_FAILED(StandalonePriFile::CreateInstance(0, baselineFile, profile, &m_baselinePri));

    const IHierarchicalSchema* baselineSchema;
    RETURN_IF_FAILED(m_baselinePri->GetSchemaById(baselineSchemaName, &baselineSchema));

    RETURN_IF_FAILED(PriFileBuilder::CreateInstance(baselineSchema, profile, &m_priBuilder));
    return S_OK;
}

void TestHPri::Release()
{
    delete m_pri;

    if (m_buffer != nullptr)
    {
        Def_Free(m_buffer);
    }

    delete m_priBuilder;

    if (m_maps != nullptr)
    {
        for (UINT i = 0; i < m_maps->Count(); i++)
        {
            TestResourceMap* map;
            m_maps->Get(i, &map);
            delete map;
        }
        delete m_maps;
    }

    if (m_schemas != nullptr)
    {
        for (UINT i = 0; i < m_schemas->Count(); i++)
        {
            TestHierarchicalSchema* schema;
            m_schemas->Get(i, &schema);
            delete schema;
        }
        delete m_schemas;
    }

    if (m_sections != nullptr)
    {
        for (UINT i = 0; i < m_sections->Count(); i++)
        {
            TestSection* section;
            m_sections->Get(i, &section);
            delete section;
        }
        delete m_sections;
    }

    delete m_baselinePri;
}

HRESULT
TestHPri::AddMapFromTestVars(_In_ PCWSTR varPrefix, _In_ PCWSTR baselineFolder)
{
    String tmp;

    // load any maps
    TestResourceMap* map = new TestResourceMap();
    if ((map == nullptr) ||
        FAILED(map->InitFromTestVars(
            GetPriSectionBuilder(), &m_testDI, tmp.Format(L"%s", varPrefix), baselineFolder, TestResourceMap::AddAllAsPrimary)))
    {
        delete map;
        Log::Error(tmp.Format(L"Error initializing map \"%s\"", varPrefix));
        return E_FAIL;
    }

    if (m_maps == nullptr)
    {
        RETURN_IF_FAILED(DynamicArray<TestResourceMap*>::CreateInstance(2, &m_maps));
    }

    RETURN_IF_FAILED(m_maps->Add(map));

    return S_OK;
}

HRESULT
TestHPri::InitFromTestVars(
    _In_ PCWSTR varPrefix,
    _In_opt_ PCWSTR baselineFolder,
    _In_ CoreProfile* profile,
    _Inout_opt_ TestStringArray* mapNamesOut)
{
    String tmp;

    String baselineList;
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_BaselineSchema", varPrefix), baselineList)))
    {
        TestStringArray baseline;
        if (baselineFolder == nullptr)
        {
            Log::Error(tmp.Format(L"Test data for \"%s\" specifies baseline but test supplies no folder", varPrefix));
            return E_FAIL;
        }
        else if (!baseline.InitFromList((PCWSTR)baselineList) || (baseline.GetNumStrings() != 2))
        {
            Log::Error(tmp.Format(L"Malformed baseline \"%s\" for \"%s\"", (PCWSTR)baselineList, varPrefix));
            return E_FAIL;
        }

        StringResult str;
        RETURN_IF_FAILED(str.Init(baselineFolder));
        RETURN_IF_FAILED(str.ConcatPathElement(tmp.Format(L"%s.pri", baseline.GetString(0))));

        Log::Comment(tmp.Format(L"[ %s_BaselineSchema: File=%s, Schema=%s ]", varPrefix, str.GetRef(), baseline.GetString(1)));
        RETURN_IF_FAILED(InitWithBaseline(str.GetRef(), baseline.GetString(1), profile));
    }
    else if (FAILED(Init(profile)))
    {
        Log::Error(L"Error initializing Test PRI");
        return E_FAIL;
    }
    else
    {
        Log::Comment(L"[ No baseline ]");
    }

    String environmentName;
    if (FAILED(TestData::TryGetValue(tmp.Format(L"%sEnvironmentName", varPrefix), environmentName)))
    {
        Log::Comment(L"[ Using default environment ]");
    }
    else
    {
        Log::Comment(tmp.Format(L"[ Looking for Test Environment %s ]", reinterpret_cast<PCWSTR>(environmentName.GetBuffer())));
        RETURN_IF_FAILED(
            TestEnvironment::CreateInstance(environmentName, m_priBuilder->GetDescriptor()->GetAtoms(), nullptr, &m_testEnvironment));

        RETURN_IF_FAILED(EnvironmentMappingSectionBuilder::CreateInstance(
            m_testEnvironment, m_priBuilder->GetDescriptor()->GetEnvironment()->GetDefaultEnvironment(), &m_qualifierMappingBuilder));

        RETURN_IF_FAILED(m_priBuilder->AddSection(m_qualifierMappingBuilder));
    }

    Log::Comment(L"[ Loading Test Decision Info ]");
    if (FAILED(m_testDI.InitDataFromTestVars(varPrefix)))
    {
        Log::Error(L"Error initializing Test Decision Info");
    }

    String mapNameList;
    TestStringArray mapNamesLocal;
    TestStringArray* mapNames = ((mapNamesOut == nullptr) ? &mapNamesLocal : mapNamesOut);
    if (FAILED(TestData::TryGetValue(tmp.Format(L"%sMapNames", varPrefix), mapNameList)) ||
        !mapNames->InitFromList((PCWSTR)mapNameList))
    {
        Log::Comment(tmp.Format(L"[ Couldn't get %sMapNames - assuming one map with no prefix ]", varPrefix));
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %d %sMapNames: %s ]", mapNames->GetNumStrings(), varPrefix, (PCWSTR)mapNameList));
    }

    // Add any maps defined by our test data
    if (mapNames->GetNumStrings() > 0)
    {
        for (int i = 0; i < mapNames->GetNumStrings(); i++)
        {
            PCWSTR mapName = mapNames->GetString(i);
            Log::Comment(tmp.Format(L"[ Adding map: %s%s ]", varPrefix, mapName));
            RETURN_IF_FAILED(AddMapFromTestVars(tmp.Format(L"%s%s", varPrefix, mapName), baselineFolder));
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ Adding map: %s ]", varPrefix));
        RETURN_IF_FAILED(AddMapFromTestVars(varPrefix, baselineFolder));
    }

    String extraSectionNamesString;
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_OtherSectionNames", varPrefix), extraSectionNamesString)))
    {
        String extraSectionTypesString;
        TestStringArray extraSectionNames;
        TestStringArray extraSectionTypes;

        if (!extraSectionNames.InitFromList(extraSectionNamesString) ||
            (FAILED(TestData::TryGetValue(tmp.Format(L"%s_OtherSectionTypes", varPrefix), extraSectionTypesString))) ||
            !extraSectionTypes.InitFromList(extraSectionTypesString) ||
            (extraSectionNames.GetNumStrings() != extraSectionTypes.GetNumStrings()))
        {
            Log::Error(tmp.Format(L"%s: OtherSectionNames exists but OtherSectionTypes is missing or inconsistent", varPrefix));
            return E_FAIL;
        }

        for (int i = 0; i < extraSectionNames.GetNumStrings(); i++)
        {
            Log::Comment(tmp.Format(L"[ Adding section %s of type %s ]", extraSectionNames.GetString(i), extraSectionTypes.GetString(i)));
            if (DefString_IEqual(extraSectionTypes.GetString(i), TestDataItemsSection::DataItemsSectionTypeName))
            {
                TestDataItemsSection* section = new TestDataItemsSection();
                if (section != nullptr)
                {
                    RETURN_HR_IF(
                        E_FAIL,
                        !section->InitFromTestVars(
                            GetFileBuilder(), tmp.Format(L"%s_%s", varPrefix, extraSectionNames.GetString(i)), true));
                }

                if (m_sections == nullptr)
                {
                    RETURN_IF_FAILED(DynamicArray<TestSection*>::CreateInstance(4, &m_sections));
                }

                RETURN_IF_FAILED(m_sections->Add(section));
            }
            else
            {
                Log::Warning(
                    tmp.Format(L"Unknown section type %s for section %s", extraSectionTypes.GetString(i), extraSectionNames.GetString(i)));
            }
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ no other sections for %s ]", varPrefix));
    }

    TestUtils::TryGetExpectedResult(
        tmp.Format(L"%sExpectedFinalizeResult", varPrefix), &m_expectedFinalizeResult, &m_expectedFinalizeReturn);
    TestUtils::TryGetExpectedResult(tmp.Format(L"%sExpectedBuildResult", varPrefix), &m_expectedBuildResult, &m_expectedBuildReturn);

    return S_OK;
}

HRESULT
TestHPri::Finalize(_In_ DEFRESULT expectedResult, _In_ bool expectedReturn)
{
    if (m_buffer != nullptr)
    {
        Def_Free(m_buffer);
        m_buffer = nullptr;
        m_bufferSizeInBytes = 0;
    }

    HRESULT hr = GetFileBuilder()->FinalizeAllSections();
    bool finalizeReturn = SUCCEEDED(hr);

    VERIFY_ARE_EQUAL(expectedResult, hr);
    VERIFY_ARE_EQUAL(expectedReturn, finalizeReturn);

    return S_OK;
}

HRESULT
TestHPri::Build(_In_ DEFRESULT expectedResult, _In_ bool expectedReturn)
{
    if (m_buffer != nullptr)
    {
        Def_Free(m_buffer);
        m_buffer = nullptr;
        m_bufferSizeInBytes = 0;
    }

    HRESULT hr = GetFileBuilder()->GenerateFileContents(&m_buffer, &m_bufferSizeInBytes);
    bool buildReturn = SUCCEEDED(hr);

    VERIFY_ARE_EQUAL(expectedResult, hr);
    VERIFY_ARE_EQUAL(expectedReturn, buildReturn);

    return S_OK;
}

HRESULT
TestHPri::WriteToFile(_In_ PCWSTR path) { return GetFileBuilder()->WriteToFile(path); }

HRESULT
TestHPri::CreateReader(_In_ CoreProfile* profile)
{
    delete m_pri;

    // if it isn't already built, we'll try to build it
    if ((m_buffer == nullptr) && FAILED(Build()))
    {
        return E_FAIL;
    }

    RETURN_IF_FAILED(StandalonePriFile::CreateInstance(0, static_cast<BYTE*>(m_buffer), m_bufferSizeInBytes, profile, &m_pri));
    return S_OK;
}

HRESULT
TestHPri::BuildPriFileFromTestVars(
    _In_ PCWSTR varPrefix,
    _In_ PCWSTR fileName,
    _In_opt_ TestHPri* pri,
    _In_ FileBasedTest* test,
    _In_ CoreProfile* profile,
    _Inout_ String& priPathOut,
    _Inout_opt_ TestStringArray* mapNamesOut)
{
    TestHPri localPri;
    String tmp;

    if (test->GetOutputLongFilePath(tmp.Format(L"%s.pri", fileName), priPathOut) == nullptr)
    {
        Log::Error(tmp.Format(L"Unable to get output file path for \"%s.pri\"", fileName));
        return E_FAIL;
    }

    // Use a local TestPRi unless our caller supplies one
    if (pri == nullptr)
    {
        pri = &localPri;
    }

    Log::Comment(L"[ BuildPriFile: %s ]", (PCWSTR)priPathOut);
    RETURN_IF_FAILED(pri->InitFromTestVars(tmp.Format(L"%s%s", varPrefix, fileName), test->GetTestOutputPath(), profile, mapNamesOut));

    RETURN_IF_FAILED(pri->WriteToFile((PCWSTR)priPathOut));

    return S_OK;
}

HRESULT
TestHPri::BuildMultiplePriFilesFromTestVars(
    _In_ PCWSTR varPrefix,
    _In_ FileBasedTest* test,
    _In_ CoreProfile* profile,
    _Inout_ TestStringArray* mapNamesOut)
{
    String tmp;

    String fileNamesString;
    if (FAILED(TestData::TryGetValue(tmp.Format(L"%sFileNames", varPrefix), fileNamesString)) ||
        !mapNamesOut->InitFromList(fileNamesString))
    {
        Log::Comment(tmp.Format(L"[ Unable to get file names from %sFileNames, assuming one file with no prefix ]", varPrefix));
        mapNamesOut->InitFromList(L"");
    }

    Log::Comment(tmp.Format(L"[ %sFileNames: %s ]", varPrefix, (PCWSTR)fileNamesString));
    for (int i = 0; i < mapNamesOut->GetNumStrings(); i++)
    {
        String priPath;
        Log::Comment(tmp.Format(L"[ Building %s ]", mapNamesOut->GetString(i)));
        RETURN_IF_FAILED(BuildPriFileFromTestVars(varPrefix, mapNamesOut->GetString(i), nullptr, test, profile, priPath, nullptr));
    }
    return S_OK;
}

HRESULT
TestHPri::GetPriFileMapNamesFromTestVars(_In_ PCWSTR varPrefix, _In_ PCWSTR fileName, _Inout_ TestStringArray* mapNamesOut)
{
    String tmp;
    String mapVarNamesList;
    TestStringArray mapVarNames;

    if (FAILED(TestData::TryGetValue(tmp.Format(L"%s%sMapNames", varPrefix, fileName), mapVarNamesList)) ||
        !mapVarNames.InitFromList((PCWSTR)mapVarNamesList))
    {
        Log::Comment(tmp.Format(L"[ Couldn't get %s%sMapNames, assuming one map with no prefix ]", varPrefix, fileName));
    }

    bool ok = true;
    String* initStrings = nullptr;
    int numStrings = 0;
    if (mapVarNames.GetNumStrings() > 0)
    {
        numStrings = mapVarNames.GetNumStrings();
        initStrings = new String[numStrings];
        for (int i = 0; ok && (i < numStrings); i++)
        {
            if (FAILED(TestData::TryGetValue(tmp.Format(L"%s%s%sSimpleId", varPrefix, fileName, mapVarNames.GetString(i)), initStrings[i])))
            {
                Log::Warning(tmp.Format(L"[ Couldn't get %s%s%sSimpleId ]", varPrefix, fileName, mapVarNames.GetString(i)));
                ok = false;
            }
        }
    }
    else
    {
        numStrings = 1;
        initStrings = new String[1];

        if (FAILED(TestData::TryGetValue(tmp.Format(L"%s%sSimpleId", varPrefix, fileName), initStrings[0])))
        {
            Log::Warning(tmp.Format(L"[ Couldn't get %s%sSimpleId ]", varPrefix, fileName));
            ok = false;
        }
    }

    ok = ok && mapNamesOut->InitFromArray(initStrings, numStrings);

    delete[] initStrings;

    return ok ? S_OK : E_FAIL;
}

HRESULT
TestHPri::VerifyAgainstTestVars(
    _In_ const IUnifiedResourceView* view,
    _In_ PCWSTR fileName,
    _In_ TestDecisionInfo* testDI,
    _In_ PCWSTR varPrefix)
{
    String tmp;
    TestStringArray mapNames;

    RETURN_IF_FAILED(GetPriFileMapNamesFromTestVars(varPrefix, fileName, &mapNames));

    for (int i = 0; i < mapNames.GetNumStrings(); i++)
    {
        PCWSTR mapName = mapNames.GetString(i);

        Log::Comment(tmp.Format(L"[ map %d: %s ]", i, mapName));
        const IResourceMapBase* map;
        RETURN_IF_FAILED(view->GetResourceMapById(mapName, &map));

        RETURN_IF_FAILED(TestResourceMap::VerifyAllAgainstTestVars(map, testDI, view->GetUnifiedEnvironment(), varPrefix));
    }
    return S_OK;
}

} // namespace UnitTests