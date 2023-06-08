// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "mrm/build/AIDict.h"
#include "Helpers.h"
#include "TestEnvironment.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{
HRESULT ComputeWindowsEnvironmentVersionInfo(
    _In_ const IEnvironment* pEnvironment,
    _In_ int majorVersion,
    _In_ int minorVersion,
    _Outptr_ IEnvironmentVersionInfo** result)
{
    *result = nullptr;
    const ENVIRONMENT_DESCRIPTION* pEnvironmentDescription = pEnvironment->GetEnvironmentDescription();

    const MRMFILE_ENVIRONMENT_VERSION_INFO* pDesiredVersionInfo = nullptr;
    RETURN_IF_FAILED(
        MrmEnvironment::FindInfoForVersion(pEnvironmentDescription, majorVersion, minorVersion, &pDesiredVersionInfo, nullptr, nullptr));

    return EnvironmentVersionInfo::ComputeNew(pEnvironment, pDesiredVersionInfo, (EnvironmentVersionInfo**)result);
}

class EnvironmentVersionUnitTests : public WEX::TestClass<EnvironmentVersionUnitTests>
{
public:
    TEST_CLASS(EnvironmentVersionUnitTests);

    BEGIN_TEST_METHOD(VersionCompatibilityTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:Environment.UnitTests.xml#VersionCompatibilityTests")
    END_TEST_METHOD()

    TEST_METHOD(KnownEnvironmentTests);

protected:
    void EnvironmentInitializerTests(const ENVIRONMENT_INITIALIZER* initializer);
};

class EnvironmentReferenceUnitTests : public WEX::TestClass<EnvironmentReferenceUnitTests>
{
public:
    TEST_CLASS(EnvironmentReferenceUnitTests);

    TEST_METHOD(NewFromEnvironmentTest);
};

void EnvironmentVersionUnitTests::VersionCompatibilityTests()
{
    bool shouldBeIdentical;
    bool shouldBeCompatible;

    if (FAILED(TestData::TryGetValue(L"ShouldBeIdentical", shouldBeIdentical)) ||
        FAILED(TestData::TryGetValue(L"ShouldBeCompatible", shouldBeCompatible)))
    {
        Log::Error(L"Couldn't load expected results");
        return;
    }

    AutoDeletePtr<AtomPoolGroup> pAtoms1;
    VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(12, &pAtoms1));
    if (pAtoms1 == nullptr)
    {
        Log::Error(L"Couldn't create AtomPoolGroup");
        return;
    }

    AutoDeletePtr<AtomPoolGroup> pAtoms2;
    VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(12, &pAtoms2));
    if (pAtoms2 == nullptr)
    {
        Log::Error(L"Couldn't create AtomPoolGroup");
        return;
    }

    AutoDeletePtr<TestEnvironment> pEnv1;
    VERIFY_SUCCEEDED(TestEnvironment::CreateInstance(L"Env1", pAtoms1, nullptr, &pEnv1));

    AutoDeletePtr<TestEnvironment> pEnv2;
    VERIFY_SUCCEEDED(TestEnvironment::CreateInstance(L"Env2", pAtoms2, pEnv1, &pEnv2));

    bool identical = CheckEnvironmentVersionIsIdentical(pEnv1->GetVersionInfo(), pEnv2->GetVersionInfo());
    VERIFY(identical == shouldBeIdentical);

    String errString;
    bool compatible = CheckEnvironmentVersionIsCompatible(pEnv2, pEnv1->GetVersionInfo());
    VERIFY_IS_TRUE(compatible == shouldBeCompatible);
}

void EnvironmentVersionUnitTests::EnvironmentInitializerTests(ENVIRONMENT_INITIALIZER const* initializer)
{
    String tmp;

    for (int i = 0; i < initializer->pEnvironmentDescription->numVersions; i++)
    {
        AutoDeletePtr<AtomPoolGroup> atoms;
        VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(&atoms));
        AutoDeletePtr<MrmEnvironment> environment;
        VERIFY_SUCCEEDED(MrmEnvironment::CreateInstance(atoms, initializer, i, &environment));

        Log::Comment(tmp.Format(L"[ Verifying Environment Version %d ]", i));
        VERIFY((atoms != nullptr) && (environment != nullptr));

        const IEnvironmentVersionInfo* version = environment->GetVersionInfo();

        // Verify that the return environment matches one computed from scratch
        AutoDeletePtr<IEnvironmentVersionInfo> computed;
        VERIFY_SUCCEEDED(UnitTests::ComputeWindowsEnvironmentVersionInfo(
            environment, version->GetMajorVersion(), version->GetMinorVersion(), &computed));
        VERIFY(computed != nullptr);

        VERIFY_ARE_EQUAL(version->GetMajorVersion(), computed->GetMajorVersion());
        VERIFY_ARE_EQUAL(version->GetMinorVersion(), computed->GetMinorVersion());
        VERIFY_ARE_EQUAL(version->GetNumQualifierTypes(), computed->GetNumQualifierTypes());
        VERIFY_ARE_EQUAL(version->GetNumQualifiers(), computed->GetNumQualifiers());
        VERIFY_ARE_EQUAL(version->GetNumItemTypes(), computed->GetNumItemTypes());
        VERIFY_ARE_EQUAL(version->GetNumConditionOperators(), computed->GetNumConditionOperators());
        VERIFY_ARE_EQUAL(version->GetNumResourceValueTypes(), computed->GetNumResourceValueTypes());
        VERIFY_ARE_EQUAL(version->GetNumResourceValueLocators(), computed->GetNumResourceValueLocators());

        if (version->GetVersionChecksum() != computed->GetVersionChecksum())
        {
            String str;
            Log::Warning(
                str.Format(L"Expected checksum 0x%x, computed 0x%x\n", version->GetVersionChecksum(), computed->GetVersionChecksum()));
        }
        VERIFY_ARE_EQUAL(version->GetVersionChecksum(), computed->GetVersionChecksum());
    }
}

void EnvironmentVersionUnitTests::KnownEnvironmentTests()
{
    Log::Comment(L"[ Testing Core Environment Initializer ]");
    EnvironmentInitializerTests(CoreEnvironment::GetEnvironmentInitializer());

    Log::Comment(L"[ Testing Future Test Environment ]");
    EnvironmentInitializerTests(&FutureCoreEnvironment::FutureCoreEnvironmentInitializer);
}

void EnvironmentReferenceUnitTests::NewFromEnvironmentTest()
{
    AtomPoolGroup* pAtoms;
    VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(&pAtoms));
    VERIFY(pAtoms != nullptr);

    MrmEnvironment* pEnv;
    VERIFY_SUCCEEDED(MrmEnvironment::CreateInstance(
        pAtoms, CoreEnvironment::GetEnvironmentInitializer(), TestEnvironmentVersions[2].major, TestEnvironmentVersions[2].minor, &pEnv));
    VERIFY(pEnv != nullptr);

    EnvironmentReference* pRef;
    VERIFY_SUCCEEDED(EnvironmentReference::CreateInstance(pEnv, &pRef));
    VERIFY(pRef != nullptr);

    VERIFY(pRef->CheckIsIdentical(pEnv));
    VERIFY(pRef->CheckIsCompatible(pEnv));

    VERIFY(DefString_ICompare(pEnv->GetUniqueName(), pRef->GetUniqueName()) == 0);

    VERIFY_ARE_EQUAL(pRef->GetMajorVersion(), pEnv->GetVersionInfo()->GetMajorVersion());
    VERIFY_ARE_EQUAL(pRef->GetMinorVersion(), pEnv->GetVersionInfo()->GetMinorVersion());

    VERIFY_ARE_EQUAL(pRef->GetNumQualifierTypes(), pEnv->GetQualifierTypeNames()->GetNumAtoms());
    VERIFY_ARE_EQUAL(pRef->GetNumQualifiers(), pEnv->GetQualifierNames()->GetNumAtoms());
    VERIFY_ARE_EQUAL(pRef->GetNumItemTypes(), pEnv->GetItemTypeNames()->GetNumAtoms());
    VERIFY_ARE_EQUAL(pRef->GetNumResourceValueTypes(), pEnv->GetResourceValueTypeNames()->GetNumAtoms());
    VERIFY_ARE_EQUAL(pRef->GetNumResourceValueLocators(), pEnv->GetResourceValueLocatorNames()->GetNumAtoms());
    VERIFY_ARE_EQUAL(pRef->GetNumConditionOperators(), pEnv->GetConditionOperatorNames()->GetNumAtoms());

    VERIFY_ARE_EQUAL(pRef->GetQualifierTypesPoolIndex(), pEnv->GetQualifierTypeNames()->GetPoolIndex());
    VERIFY_ARE_EQUAL(pRef->GetQualifiersPoolIndex(), pEnv->GetQualifierNames()->GetPoolIndex());
    VERIFY_ARE_EQUAL(pRef->GetItemTypesPoolIndex(), pEnv->GetItemTypeNames()->GetPoolIndex());
    VERIFY_ARE_EQUAL(pRef->GetResourceValueTypesPoolIndex(), pEnv->GetResourceValueTypeNames()->GetPoolIndex());
    VERIFY_ARE_EQUAL(pRef->GetResourceValueLocatorsPoolIndex(), pEnv->GetResourceValueLocatorNames()->GetPoolIndex());
    VERIFY_ARE_EQUAL(pRef->GetConditionOperatorsPoolIndex(), pEnv->GetConditionOperatorNames()->GetPoolIndex());

    delete pRef;
    delete pEnv;
    delete pAtoms;
}
} // namespace UnitTests
