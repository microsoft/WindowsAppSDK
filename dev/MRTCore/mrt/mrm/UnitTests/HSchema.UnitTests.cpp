// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "mrm/build/AIDict.h"
#include "Helpers.h"
#include "TestHSchema.h"
#include "TestPri.h"
#include "TestUtils.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{
class HierarchicalSchemaUnitTests : public WEX::TestClass<HierarchicalSchemaUnitTests>
{
    TEST_CLASS(HierarchicalSchemaUnitTests);

    BEGIN_TEST_METHOD(SimpleBuildTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:HSchema.UnitTests.xml#SimpleBuildTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(VersionCompatibilityTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:HSchema.UnitTests.xml#VersionCompatibilityTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(SchemaReferenceTest)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:HSchema.UnitTests.xml#SimpleBuildTests")
    END_TEST_METHOD();
};

void HierarchicalSchemaUnitTests::SimpleBuildTests()
{
    String tmp;
    TestHPri pri;
    TestHierarchicalSchema testSchema;

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    if (FAILED(pri.Init(pProfile)))
    {
        Log::Error(L"[ Test setup: couldn't set up PRI ]");
        return;
    }

    AutoDeletePtr<PriSectionBuilder> pHPriBuilder;
    VERIFY_SUCCEEDED(PriSectionBuilder::CreateInstance(pri.GetFileBuilder(), pProfile, &pHPriBuilder));
    if (pHPriBuilder == NULL)
    {
        Log::Error(L"[ Couldn't create PriSectionBuilder ]");
        return;
    }

    if (FAILED(testSchema.Init(pHPriBuilder, L"")))
    {
        Log::Error(L"Error creating schema from test data.");
        return;
    }

    // Okay, we're ready to try building it.  First build the rest of the package resources.
    if (FAILED(pri.Build()))
    {
        Log::Error(L"Error building PRI");
        return;
    }

    // Now build the schema.  In the real world the schema would be built as part of the
    // package, but we're a test case.
    VERIFY_SUCCEEDED(testSchema.Build());

    // read back the package resources
    if (FAILED(pri.CreateReader(pProfile)))
    {
        Log::Error(L"Error creating PRI reader");
    }

    // ...to read back the schema we just built:
    DEFFILE_SECTION_TYPEID sectionType = testSchema.GetSchemaBuilder()->GetSectionType();
    VERIFY_SUCCEEDED(testSchema.CreateReader(sectionType));

    // Now verify that it contains what we expect it to
    TestHierarchicalSchema::TryVerifyVersion(testSchema.GetSchema(), L"");
    TestHierarchicalSchema::TryVerifyScopes(testSchema.GetSchema(), L"");
    TestHierarchicalSchema::TryVerifyItems(testSchema.GetSchema(), L"");
}

void HierarchicalSchemaUnitTests::VersionCompatibilityTests()
{
    String tmp;
    TestHPri pri1;
    TestHierarchicalSchema schema1;
    TestHPri pri2;
    TestHierarchicalSchema schema2;

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    if (FAILED(pri1.Init(pProfile)))
    {
        Log::Error(L"Couldn't initialize PRI 1");
    }

    AutoDeletePtr<PriSectionBuilder> pHPri1;
    VERIFY_SUCCEEDED(PriSectionBuilder::CreateInstance(pri1.GetFileBuilder(), pProfile, &pHPri1));
    if (pHPri1 == NULL)
    {
        Log::Error(L"[ Couldn't create PriSectionBuilder ]");
        return;
    }

    if (FAILED(schema1.Init(pHPri1, L"S1_")))
    {
        Log::Error(L"Error creating schema 1 from test data.");
        return;
    }

    // Okay, we're ready to build the first schema.  First build the rest of the package resources.
    if (FAILED(pri1.Build()))
    {
        Log::Error(L"Couldn't build first PRI");
    }

    // Now build the schema.  In the real world the schema would be built as part of the
    // package, but we're a test case.
    VERIFY_SUCCEEDED(schema1.Build());

    // Now we have to read the package resources back into something we can use...
    if (FAILED(pri1.CreateReader(pProfile)))
    {
        Log::Error(L"Couldn't read back first PRI");
    }

    // ...to read back the schema we just built:
    DEFFILE_SECTION_TYPEID sectionType = schema1.GetSchemaBuilder()->GetSectionType();
    VERIFY_SUCCEEDED(schema1.CreateReader(sectionType));

    // Now lets build our second schema.
    if (FAILED(pri2.Init(pProfile)))
    {
        Log::Error(L"Couldn't initialize second PRI");
    }

    AutoDeletePtr<PriSectionBuilder> pHPri2;
    VERIFY_SUCCEEDED(PriSectionBuilder::CreateInstance(pri2.GetFileBuilder(), pProfile, &pHPri2));
    if (pHPri2 == NULL)
    {
        Log::Error(L"[ Couldn't create PriSectionBuilder ]");
        return;
    }

    if (FAILED(schema2.Init(pHPri2, L"S2_")))
    {
        Log::Error(L"Error creating schema 2 from test data.");
        return;
    }

    // Okay, we're ready to build the second schema.  First build the rest of the package resources.
    if (FAILED(pri2.Build()))
    {
        Log::Error(L"Couldn't build second PRI");
    }

    // Now build the schema.  In the real world the schema would be built as part of the
    // package, but we're a test case.
    VERIFY_SUCCEEDED(schema2.Build());

    // Now we have to read the package resources back into something we can use...
    if (FAILED(pri2.CreateReader(pProfile)))
    {
        Log::Error(L"Couldn't read back second PRI");
    }

    // ...to read back the schema we just built:
    sectionType = schema2.GetSchemaBuilder()->GetSectionType();
    VERIFY_SUCCEEDED(schema2.CreateReader(sectionType));

    // We have a new schema.  Now let's see what we're supposed to compare
    TestHierarchicalSchema::TryVerifyCompatibility(schema1.GetSchema(), schema2.GetSchema(), L"");
}

void HierarchicalSchemaUnitTests::SchemaReferenceTest()
{
    static const UINT16 majorVersion = 3;
    static const PWSTR uniqueName = L"UniqueName";

    AutoDeletePtr<CoreProfile> profile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&profile));

    TestHPri testHPri;
    if (FAILED(testHPri.Init(profile)))
    {
        Log::Error(L"Couldn't initialize the PRI");
        return;
    }

    AutoDeletePtr<PriSectionBuilder> priSectionBuilder;
    VERIFY_SUCCEEDED(PriSectionBuilder::CreateInstance(testHPri.GetFileBuilder(), profile, &priSectionBuilder));
    if (priSectionBuilder == nullptr)
    {
        Log::Error(L"Couldn't create PriSectionBuilder");
        return;
    }

    AutoDeletePtr<HierarchicalSchemaSectionBuilder> schemaBuilder;
    VERIFY_SUCCEEDED(
        HierarchicalSchemaSectionBuilder::CreateInstance(priSectionBuilder, L"DisplayName", uniqueName, majorVersion, &schemaBuilder));
    VERIFY(schemaBuilder != nullptr);

    if (!TestHierarchicalSchema::TryAddItemsFromTestVars(priSectionBuilder, schemaBuilder, L""))
    {
        Log::Comment(L"No collections or items added");
    }

    // Okay, we're ready to try building  new schema.  First build the rest of the package resources.
    if (FAILED(testHPri.Build()))
    {
        Log::Error(L"Couldn't build the PRI");
    }

    // Now build the schema.
    BuildHelper buildHelper;
    VERIFY_SUCCEEDED(buildHelper.Build(schemaBuilder));

    // Now we have to read the package resources back into something we can use...
    if (FAILED(testHPri.CreateReader(profile)))
    {
        Log::Error(L"Couldn't read back the PRI");
    }

    // ...to read back the schema we just built:
    DEFFILE_SECTION_TYPEID sectionType = schemaBuilder->GetSectionType();
    VERIFY_ARE_EQUAL(sectionType.ullType[0], gHierarchicalSchemaExSectionType.ullType[0]);
    VERIFY_ARE_EQUAL(sectionType.ullType[1], gHierarchicalSchemaExSectionType.ullType[1]);

    AutoDeletePtr<HierarchicalSchema> schema;
    VERIFY_SUCCEEDED(HierarchicalSchema::CreateInstance(sectionType, buildHelper.GetBuffer(), buildHelper.GetBufferSize(), &schema));
    VERIFY(schema != nullptr);

    VERIFY_ARE_EQUAL(schema->GetMajorVersion(), majorVersion);
    TestHierarchicalSchema::TryVerifyScopes(schema, L"");
    TestHierarchicalSchema::TryVerifyItems(schema, L"");

    VERIFY_IS_TRUE(wcscmp(schema->GetUniqueId(), uniqueName) == 0);

    // Now create a schema reference for the schema.
    AutoDeletePtr<HierarchicalSchemaReferenceSectionBuilder> schemaRefBuilder;
    VERIFY_SUCCEEDED(HierarchicalSchemaReferenceSectionBuilder::CreateInstance(schema, &schemaRefBuilder));

    BuildHelper referenceBuildHelper;
    VERIFY_SUCCEEDED(referenceBuildHelper.Build(schemaRefBuilder));

    DEFFILE_SECTION_TYPEID sectionRefType = schemaRefBuilder->GetSectionType();
    VERIFY_ARE_EQUAL(sectionRefType.ullType[0], gHierarchicalSchemaSectionReferenceType.ullType[0]);
    VERIFY_ARE_EQUAL(sectionRefType.ullType[1], gHierarchicalSchemaSectionReferenceType.ullType[1]);

    AutoDeletePtr<HierarchicalSchemaReference> schemaRef;
    VERIFY_SUCCEEDED(
        HierarchicalSchemaReference::CreateInstance(referenceBuildHelper.GetBuffer(), referenceBuildHelper.GetBufferSize(), &schemaRef));
    VERIFY(schemaRef != nullptr);

    VERIFY_ARE_EQUAL(schemaRef->GetMajorVersion(), majorVersion);
    VERIFY_IS_TRUE(wcscmp(schemaRef->GetUniqueId(), uniqueName) == 0);

    VERIFY_ARE_EQUAL(schemaRef->GetMinorVersion(), schema->GetMinorVersion());
    VERIFY_ARE_EQUAL(schemaRef->GetMajorVersion(), schema->GetMajorVersion());
}

} // namespace UnitTests
