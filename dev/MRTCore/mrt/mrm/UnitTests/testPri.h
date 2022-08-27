// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "TestSections.h"
#include "TestEnvironment.h"
#include "TestQualifier.h"
#include "TestFileUtils.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

class TestHierarchicalSchema;
class TestResourceMap;

class TestHPri
{
protected:
    PriFileBuilder* m_priBuilder;
    _Field_size_bytes_(m_bufferSizeInBytes) void* m_buffer;
    UINT32 m_bufferSizeInBytes;
    StandalonePriFile* m_pri;

    TestDecisionInfo m_testDI;
    DynamicArray<TestHierarchicalSchema*>* m_schemas;
    DynamicArray<TestResourceMap*>* m_maps;
    DynamicArray<TestSection*>* m_sections;

    TestEnvironment* m_testEnvironment;
    EnvironmentMappingSectionBuilder* m_qualifierMappingBuilder;

    StandalonePriFile* m_baselinePri;

    DEFRESULT m_expectedFinalizeResult;
    bool m_expectedFinalizeReturn;

    DEFRESULT m_expectedBuildResult;
    bool m_expectedBuildReturn;

public:
    TestHPri();

    // Creates a schema from test variables
    HRESULT Init(_In_ CoreProfile* profile);

    HRESULT InitWithBaseline(_In_ PCWSTR baselineFile, _In_ PCWSTR baselineSchemaName, _In_ CoreProfile* profile);

    HRESULT InitFromTestVars(
        _In_ PCWSTR varPrefix,
        _In_opt_ PCWSTR baselineFolder,
        _In_ CoreProfile* profile,
        _Inout_opt_ TestStringArray* mapNamesOut);

    HRESULT InitFromTestVars(_In_ PCWSTR varPrefix, _In_ CoreProfile* profile, _Inout_opt_ TestStringArray* mapNamesOut)
    {
        return InitFromTestVars(varPrefix, nullptr, profile, mapNamesOut);
    }

    HRESULT AddMapFromTestVars(_In_ PCWSTR varPrefix, _In_ PCWSTR baselineFolder);

    ~TestHPri() { Release(); }
    void Release();

    FileBuilder* GetFileBuilder() const { return m_priBuilder; }
    PriFileBuilder* GetPriFileBuilder() const { return m_priBuilder; }
    PriSectionBuilder* GetPriSectionBuilder() const { return m_priBuilder->GetDescriptor(); }
    StandalonePriFile* GetPriFile() const { return m_pri; }

    TestDecisionInfo* GetTestDI() { return &m_testDI; }

    int GetNumSchemas() const { return (m_schemas ? m_schemas->Count() : 0); }

    TestHierarchicalSchema* GetSchema(_In_ int index)
    {
        if (m_schemas == nullptr)
        {
            return nullptr;
        }

        TestHierarchicalSchema* schema = nullptr;
        m_schemas->Get(index, &schema);
        return schema;
    }

    int GetNumResourceMaps() const { return (m_maps ? m_maps->Count() : 0); }

    TestResourceMap* GetResourceMap(_In_ int index)
    {
        if (m_maps == nullptr)
        {
            return nullptr;
        }

        TestResourceMap* map = nullptr;
        m_maps->Get(index, &map);
        return map;
    }

    int GetNumSections() const { return (m_sections ? m_sections->Count() : 0); }

    TestSection* GetSection(_In_ int index)
    {
        if (m_sections == nullptr)
        {
            return nullptr;
        }

        TestSection* section = nullptr;
        m_sections->Get(index, &section);
        return section;
    }

    HRESULT Finalize(_In_ DEFRESULT expectedResult, _In_ bool expectedReturn);

    HRESULT Finalize() { return Finalize(m_expectedFinalizeResult, m_expectedFinalizeReturn); }

    HRESULT Build(_In_ DEFRESULT expectedResult, _In_ bool expectedReturn);

    HRESULT Build() { return Build(m_expectedBuildResult, m_expectedBuildReturn); }

    HRESULT WriteToFile(_In_ PCWSTR path);

    HRESULT CreateReader(_In_ CoreProfile* profile);

    static HRESULT BuildPriFileFromTestVars(
        _In_ PCWSTR varPrefix,
        _In_ PCWSTR fileName,
        _In_opt_ TestHPri* pri,
        _In_ FileBasedTest* test,
        _In_ CoreProfile* profile,
        _Inout_ String& priPathOut,
        _Inout_opt_ TestStringArray* mapNamesOut);

    static HRESULT BuildMultiplePriFilesFromTestVars(
        _In_ PCWSTR varPrefix,
        _In_ FileBasedTest* test,
        _In_ CoreProfile* profile,
        _Inout_ TestStringArray* mapNamesOut);

    static HRESULT GetPriFileMapNamesFromTestVars(_In_ PCWSTR varPrefix, _In_ PCWSTR fileName, _Inout_ TestStringArray* mapNamesOut);

    static HRESULT VerifyAgainstTestVars(
        _In_ const IUnifiedResourceView* pri,
        _In_ PCWSTR fileName,
        _In_ TestDecisionInfo* testDI,
        _In_ PCWSTR varPrefix);
};

} // namespace UnitTests
