// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "Helpers.h"
#include "mrm/build/Base.h"
#include "mrm/readers/MrmManagers.h"
#include "mrm/readers/References.h"

#include "TestPri.h"
#include "TestHSchema.h"
#include "TestMap.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{
class ResourceReferenceUnitTests : public WEX::TestClass<ResourceReferenceUnitTests>, public FileBasedTest
{

    TEST_CLASS(ResourceReferenceUnitTests);

    TEST_CLASS_SETUP(ClassSetup);
    TEST_CLASS_CLEANUP(ClassCleanup);

    TEST_METHOD_SETUP(MethodSetup);
    TEST_METHOD_CLEANUP(MethodCleanup);

    BEGIN_TEST_METHOD(SimpleReferenceTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:ResourceReference.UnitTests.xml#SimpleReferenceTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(BlobFormatTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:ResourceReference.UnitTests.xml#BlobFormatTests")
    END_TEST_METHOD();
};

bool ResourceReferenceUnitTests::ClassSetup()
{
    if (!SetupClassFolders(L"ResourceReference"))
    {
        Log::Error(L"Unable to set up test data folders for ResourceReference");
        return false;
    }
    return true;
}

bool ResourceReferenceUnitTests::ClassCleanup()
{
    if (!CleanupClassFolders())
    {
        Log::Warning(L"Unable to clean up class folders for ResourceReference");
    }
    return true;
}

bool ResourceReferenceUnitTests::MethodSetup() { return true; }

bool ResourceReferenceUnitTests::MethodCleanup()
{
    // Always attempt to cleanup in case the method exited prematurely
    TryCleanupTestMethodOutputFolder();
    return true;
}

_Success_(return ) static bool GetOrigin(_Out_ UINT16* pOriginFlagsOut, _Inout_ StringResult* pOriginOut)
{
    String tmp;

    // Origin is one of:
    //      "internal" (no name specified)
    // or:
    //      "{file,package}; <name>"
    // Where "<name>" is the name of the file or package used for the reference
    String originSpecStr;
    TestStringArray originSpec;
    if (FAILED(TestData::TryGetValue(L"Origin", originSpecStr)) || !originSpec.InitFromList(originSpecStr) ||
        ((originSpec.GetNumStrings() != 1) && (originSpec.GetNumStrings() != 2)))
    {
        Log::Warning(tmp.Format(L"[ Missing or malformed Origin specification ]"));
        return false;
    }

    UINT16 originType = ResourceReference::fMrmRefType_UnspecifiedOrigin;
    PCWSTR pszOrigin = nullptr;

    if (originSpec.GetNumStrings() == 1)
    {
        if (DefString_ICompare(originSpec.GetString(0), L"internal") != Def_Equal)
        {
            Log::Warning(tmp.Format(L"[ Length 1 Origin must be \"internal\" ]"));
            return false;
        }
    }
    else
    {
        if (DefString_ICompare(originSpec.GetString(0), L"file") == Def_Equal)
        {
            originType = ResourceReference::fMrmRefType_FileOrigin;
        }
        else if (DefString_ICompare(originSpec.GetString(0), L"package") == Def_Equal)
        {
            originType = ResourceReference::fMrmRefType_PackageOrigin;
        }
        else
        {
            Log::Warning(tmp.Format(L"[ Length 2 Origin must be \"package\" or \"file\" ]"));
            return false;
        }

        pszOrigin = originSpec.GetString(1);
    }

    *pOriginFlagsOut = originType;
    return SUCCEEDED(pOriginOut->SetCopy(pszOrigin));
}

static HRESULT BuildReference(
    _In_ const IResourceMapBase* pMap,
    _In_ PCWSTR pResourceName,
    _In_ UINT16 originType,
    _In_opt_ PCWSTR pszOrigin,
    _Inout_ BlobResult* pBlobOut)
{
    String tmp;

    // Look up the referenced resource
    NamedResourceResult resource;
    HRESULT hr = pMap->GetResource(pResourceName, &resource);
    if (FAILED(hr))
    {
        Log::Warning(tmp.Format(L"[ Named resource \"%s\" not found. ignored. ]", pResourceName));
        return hr;
    }

    // Now build a blob for it
    if ((originType == ResourceReference::fMrmRefType_UnspecifiedOrigin) && (pszOrigin == nullptr))
    {
        Log::Comment(tmp.Format(L"[ Building internal reference \"%s\" ]", pResourceName));
        hr = ReferenceBuilder::GetInternalReferenceBlob(&resource, pBlobOut);
    }
    else
    {
        Log::Comment(tmp.Format(L"[ Building external reference \"%s\" ]", pResourceName));
        hr = ReferenceBuilder::GetExternalReferenceBlob(originType, pszOrigin, &resource, pBlobOut);
    }

    return hr;
}

static bool VerifyBuildReferences(_In_ UINT16 originType, _In_opt_ PCWSTR pszOrigin, _In_ const IResourceMapBase* pMap)
{
    String tmp;

    // If present, BuildReferences contains a series of entries of the form:
    //     resourceName; expectedResult (0=success); flags; cbTotal; cchOriginName; cbPayload; origin; payload
    // Where 'resourceName' is the resource for which a reference is to be constructed
    // and all remaining fields describe the expected results.  "flags" is hexadecimal, other counts
    // are decimal, origin and payload are strings.

    TestDataArray<String> refs;
    if (SUCCEEDED(TestData::TryGetValue(L"BuildReferences", refs)))
    {
        // Process each "build" reference to be verified
        for (size_t i = 0; i < refs.GetSize(); i++)
        {
            TestStringArray refSpec;
            int expectedStatus = -1;

            Log::Comment(tmp.Format(L"[ BuildReference: \"%s\" ]", (PCWSTR)refs[i]));

            // Parse the build reference
            if (!refSpec.InitFromList(refs[i]) || (refSpec.GetNumStrings() < 2) || (!refSpec.TryGetStringAsInt(1, &expectedStatus)))
            {
                Log::Warning(tmp.Format(L"[ Malformed BuildReference \"%s\" ignored. ]", (PCWSTR)refs[i]));
                continue;
            }

            BlobResult blob;
            HRESULT hr = BuildReference(pMap, refSpec.GetString(0), originType, pszOrigin, &blob);

            if (expectedStatus == 0)
            {
                VERIFY(SUCCEEDED(hr));
            }
            else
            {
                VERIFY(FAILED(hr) && (hr == static_cast<HRESULT>(expectedStatus)));
            }

            // if we have more than 2 strings, there's more verification to be done...
            if (refSpec.GetNumStrings() > 2)
            {
                UINT32 cbRefBlob = static_cast<UINT32>(blob.GetSize());
                ResourceReference ref;
                VERIFY_SUCCEEDED(ref.Set(cbRefBlob, blob.GetRef(nullptr)));

                UINT32 flags;
                if (refSpec.TryGetStringAsHexadecimal(2, &flags))
                {
                    if (flags != ref.GetHeader()->flags)
                    {
                        Log::Error(tmp.Format(L"flags: Expected 0x%x, got 0x%x ]", flags, ref.GetHeader()->flags));
                    }
                }
                else
                {
                    Log::Warning(tmp.Format(L"[ Malformed flags for built blob.  Ignored. ]"));
                }

                if (refSpec.GetNumStrings() > 3)
                {
                    int cbTotal;
                    if (refSpec.TryGetStringAsInt(3, &cbTotal))
                    {
                        VERIFY(cbTotal == ref.GetHeader()->cbTotal);
                    }
                    else
                    {
                        Log::Warning(tmp.Format(L"[ Malformed cbTotal for built blob.  Ignored. ]"));
                    }
                }

                if (refSpec.GetNumStrings() > 4)
                {
                    int cchOriginName;
                    if (refSpec.TryGetStringAsInt(4, &cchOriginName))
                    {
                        VERIFY(cchOriginName == ref.GetHeader()->cchOriginName);
                    }
                    else
                    {
                        Log::Warning(tmp.Format(L"[ Malformed cchOriginName for built blob.  Ignored. ]"));
                    }
                }

                if (refSpec.GetNumStrings() > 5)
                {
                    int cbPayload;
                    if (refSpec.TryGetStringAsInt(4, &cbPayload))
                    {
                        VERIFY(cbPayload == ref.GetHeader()->cbPayload);
                    }
                    else
                    {
                        Log::Warning(tmp.Format(L"[ Malformed cbPayload for built blob.  Ignored. ]"));
                    }
                }
            }
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ BuildReferences not specified ]"));
        // not fatal, there might be LookupReferences
    }
    return true;
}

static bool VerifyLookupReferences(
    _In_ UINT16 originType,
    _In_opt_ PCWSTR pszOrigin,
    _In_opt_ UnifiedResourceView* pView,
    _In_ const IResourceMapBase* pMap)
{
    String tmp;

    // This test does lookups, either against a context or without a map.  Need
    // to create the context we're going to use.
    AutoDeletePtr<OverrideResolver> pContext;
    VERIFY_SUCCEEDED(OverrideResolver::CreateInstance(pView->GetDefaultResolver(), &pContext));

    String contextSpec;
    TestStringArray contextStrings;
    if (SUCCEEDED(TestData::TryGetValue(L"Context", contextSpec)) && contextStrings.InitFromList((PCWSTR)contextSpec))
    {

        for (int i = 0; i < contextStrings.GetNumStrings(); i += 2)
        {
            PCWSTR pQualifierName = contextStrings.GetString(i);

            if (i == (contextStrings.GetNumStrings() - 1))
            {
                Log::Warning(tmp.Format(L"[ Missing value for context qualifier \"%s\" - ignored. ]", pQualifierName));
                continue;
            }

            PCWSTR pQualifierValue = contextStrings.GetString(i + 1);

            Log::Comment(tmp.Format(L"[ Context: %s = \"%s\" ]", pQualifierName, pQualifierValue));

            if (FAILED(pContext->SetQualifier(pQualifierName, pQualifierValue)))
            {
                Log::Warning(tmp.Format(L"[ Unable to set qualifier %s to \"%s\". Skipping test. ]", pQualifierName, pQualifierValue));
                return false;
            }
        }
    }

    // If present, LookupReferences contains a series of entries of the form:
    //     resource; supplyMapOnLookup; expectedResult (0=success); expectedValue
    // Where 'resourceName' is the resource for which a reference is to be constructed.
    // The remaining fields describe the lookup operation to be validated:
    // - 'supplyMapOnLookup' - indicates whether the map used to look up the resource
    //                         should be supplied for lookup as well
    // - 'expectedResult'    - is a hex number describing the expected DEFRESULT reported
    //                         for the operation (0=success)
    // - 'expectedValue'     - The string value expected to be returned by the operation.
    TestDataArray<String> refs;
    if (SUCCEEDED(TestData::TryGetValue(L"LookupReferences", refs)))
    {
        // Process each "build" reference to be verified
        for (size_t i = 0; i < refs.GetSize(); i++)
        {
            TestStringArray refSpec;
            bool useMap = true;
            UINT32 expectedStatus = 0;

            Log::Comment(tmp.Format(L"[ LookupReference: \"%s\" ]", (PCWSTR)refs[i]));

            // Parse the build reference
            if (!refSpec.InitFromList(refs[i]) || (refSpec.GetNumStrings() < 3) || (!refSpec.TryGetStringAsBool(1, &useMap)) ||
                (!refSpec.TryGetStringAsHexadecimal(2, &expectedStatus)))
            {
                Log::Warning(tmp.Format(L"[ Malformed LookupReference \"%s\" ignored. ]", (PCWSTR)refs[i]));
                continue;
            }

            // Build the reference blob
            BlobResult blob;
            VERIFY_SUCCEEDED(BuildReference(pMap, refSpec.GetString(0), originType, pszOrigin, &blob));

            // Now create the reference
            UINT32 cbRefBlob = static_cast<UINT32>(blob.GetSize());
            ResourceReference ref;
            VERIFY_SUCCEEDED(ref.Set(cbRefBlob, blob.GetRef(nullptr)));

            // Now do the lookup
            HRESULT hr = S_OK;
            StringResult value;
            if (useMap)
            {
                Log::Comment(tmp.Format(L"[ Resolving \"%s\" with map and context ]", refSpec.GetString(0)));
                hr = ref.ResolveAsString(pView, pContext, &value);
            }
            else
            {
                Log::Comment(tmp.Format(L"[ Resolving \"%s\" without map and context ]", refSpec.GetString(0)));
                hr = ref.ResolveAsString(nullptr, nullptr, &value);
            }

            if (expectedStatus == 0)
            {
                VERIFY(SUCCEEDED(hr));
            }
            else if (SUCCEEDED(hr) || ((UINT32)hr != expectedStatus))
            {
                Log::Error(tmp.Format(L"Expected failure with 0x%x, got 0x%x", expectedStatus, hr));
            }

            if (SUCCEEDED(hr) && (refSpec.GetNumStrings() > 3))
            {
                PCWSTR pGotValue = value.GetRef();
                PCWSTR pExpectedValue = refSpec.GetString(3);

                Log::Comment(tmp.Format(L"[ Expect \"%s\", got \"%s\" ]", pExpectedValue, pGotValue));
                if (pExpectedValue[0] == '*')
                {
                    VERIFY(DefString_IsSuffixI(&pExpectedValue[1], pGotValue));
                }
                else
                {
                    VERIFY(value.ICompare(pExpectedValue) == Def_Equal);
                }
            }
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ LookupReferences not specified ]"));
    }
    return true;
}

void ResourceReferenceUnitTests::SimpleReferenceTests()
{
    String tmp;
    TestHPri pri;

    if (!SetupTestMethodOutputFolder(L"SimpleReferenceTests"))
    {
        return;
    }

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    String priPath;
    if (FAILED(TestHPri::BuildPriFileFromTestVars(L"", L"Map", &pri, this, pProfile, priPath, nullptr)))
    {
        Log::Warning(tmp.Format(L"[ Couldn't load \"map.pri\" from test vars ]"));
        return;
    }

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != nullptr);

    Log::Comment(tmp.Format(L"[ Loading file \"%s\" ]", (PCWSTR)priPath));
    const ManagedResourceMap* pMap;
    VERIFY_SUCCEEDED(pView->SetApplicationFile((PCWSTR)priPath, GetTestOutputPath(), &pMap));
    VERIFY(pMap != nullptr);

    UINT16 originType;
    StringResult originName;
    if (!GetOrigin(&originType, &originName))
    {
        Log::Warning(tmp.Format(L"[ Couldn't get origin.  Skipping test. ]"));
        return;
    }

    VerifyBuildReferences(originType, originName.GetRef(), pMap);
    VerifyLookupReferences(originType, originName.GetRef(), pView, pMap);
}

void ResourceReferenceUnitTests::BlobFormatTests()
{
    String tmp;
    TestHPri pri;

    if (!SetupTestMethodOutputFolder(L"BlobFormatTests"))
    {
        return;
    }

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    String priPath;
    if (FAILED(TestHPri::BuildPriFileFromTestVars(L"", L"Map", &pri, this, pProfile, priPath, nullptr)))
    {
        Log::Warning(tmp.Format(L"[ Couldn't load \"map.pri\" from test vars ]"));
        return;
    }

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != nullptr);

    Log::Comment(tmp.Format(L"[ Loading file \"%s\" ]", (PCWSTR)priPath));
    const ManagedResourceMap* pMap;
    VERIFY_SUCCEEDED(pView->SetApplicationFile((PCWSTR)priPath, GetTestOutputPath(), &pMap));
    VERIFY(pMap != nullptr);

    // Okay, we have a map to work with.  Let's test some stuff.
    BYTE blobBuffer[1024];
    MRM_REFERENCE_BLOB* pBlob = reinterpret_cast<MRM_REFERENCE_BLOB*>(&blobBuffer[0]);
    PWSTR pOrigin = reinterpret_cast<PWSTR>(&pBlob[1]);
    size_t cbBlobUsed;

    ResourceReference ref;

    TestDataArray<String> blobs;
    if (SUCCEEDED(TestData::TryGetValue(L"ReferenceBlobs", blobs)))
    {
        for (size_t i = 0; i < blobs.GetSize(); i++)
        {
            TestStringArray blobSpecs;
            if (blobSpecs.InitFromList((PCWSTR)blobs[i]))
            {
                UINT32 flags;
                UINT32 cbTotal;
                UINT32 cchOrigin;
                UINT32 cbPayload;
                UINT32 expectedCreateStatus;
                UINT32 expectedResolveStatus;
                PCWSTR pTestOrigin;
                PCWSTR pTestPayload;

                if ((blobSpecs.GetNumStrings() == 8) && blobSpecs.TryGetStringAsHexadecimal(0, &flags) &&
                    blobSpecs.TryGetStringAsHexadecimal(1, &cbTotal) && blobSpecs.TryGetStringAsHexadecimal(2, &cchOrigin) &&
                    blobSpecs.TryGetStringAsHexadecimal(3, &cbPayload) && blobSpecs.TryGetStringAsHexadecimal(6, &expectedCreateStatus) &&
                    blobSpecs.TryGetStringAsHexadecimal(7, &expectedResolveStatus))
                {

                    Log::Comment(tmp.Format(L"[ ReferenceBlob=\"%s\" ]", (PCWSTR)blobs[i]));

                    pTestOrigin = blobSpecs.GetString(4);
                    pTestPayload = blobSpecs.GetString(5);

                    if (DefString_Compare(pTestOrigin, L"[]") == Def_Equal)
                    {
                        pTestOrigin = nullptr;
                    }
                    if (DefString_Compare(pTestPayload, L"[]") == Def_Equal)
                    {
                        pTestPayload = nullptr;
                    }

                    SecureZeroMemory(blobBuffer, sizeof(blobBuffer));
                    cbBlobUsed = sizeof(MRM_REFERENCE_BLOB);

                    pBlob->flags = (UINT16)flags;
                    pBlob->cbTotal = (UINT16)cbTotal;
                    pBlob->cchOriginName = (UINT16)cchOrigin;
                    pBlob->cbPayload = (UINT16)cbPayload;

                    if (!DefString_IsEmpty(pTestOrigin))
                    {
                        if (FAILED(DefString_CchCopy(pOrigin, (sizeof(blobBuffer) - cbBlobUsed) / sizeof(WCHAR), pTestOrigin)))
                        {
                            Log::Warning(tmp.Format(L"[ Couldn't copy origin to blob - error in test data ]"));
                            continue;
                        }

                        cbBlobUsed += (wcslen(pTestOrigin) + 1) * sizeof(WCHAR);
                    }

                    if (!DefString_IsEmpty(pTestPayload))
                    {
                        UINT32 payloadInt;

                        cbBlobUsed = _DEFFILE_PAD(cbBlobUsed, 4);

                        // If the value starts with # our payload is an integer
                        if ((pTestPayload[0] == L'#') && (swscanf_s(&pTestPayload[1], L"%x", &payloadInt) == 1))
                        {
                            if ((sizeof(blobBuffer) - cbBlobUsed) < sizeof(UINT32))
                            {
                                Log::Warning(L"[ integer payload would overrun end of blob -- error in test data ]");
                                continue;
                            }

                            UINT32* pPayloadInt = reinterpret_cast<UINT32*>(&blobBuffer[cbBlobUsed]);
                            *pPayloadInt = payloadInt;
                        }
                        else
                        {
                            WCHAR* pPayload = reinterpret_cast<WCHAR*>(&blobBuffer[cbBlobUsed]);

                            if (FAILED(DefString_CchCopy(pPayload, (sizeof(blobBuffer) - cbBlobUsed) / sizeof(WCHAR), pTestPayload)))
                            {
                                Log::Warning(tmp.Format(L"[ Couldn't copy payload to blob - error in test data ]"));
                                continue;
                            }

                            cbBlobUsed += (wcslen(pTestPayload) + 1) * sizeof(WCHAR);
                        }
                    }

                    if (expectedCreateStatus == 0)
                    {
                        VERIFY_SUCCEEDED(ref.Set(sizeof(blobBuffer), blobBuffer));

                        StringResult stringValue;
                        if (expectedResolveStatus == 0)
                        {
                            VERIFY_SUCCEEDED(ref.ResolveAsString(pView, pView->GetDefaultResolver(), &stringValue));
                        }
                        else
                        {
                            HRESULT hr = ref.ResolveAsString(pView, pView->GetDefaultResolver(), &stringValue);
                            VERIFY_FAILED(hr);
                            VERIFY_IS_TRUE((UINT32)hr == expectedResolveStatus);
                        }
                    }
                    else
                    {
                        HRESULT hr = ref.Set(sizeof(blobBuffer), blobBuffer);
                        VERIFY_IS_TRUE(FAILED(hr) && ((UINT32)hr == expectedCreateStatus));
                    }
                }
                else
                {
                    Log::Warning(tmp.Format(L"[ Malformed ReferenceBlob entry \"%s\" ]", (PCWSTR)blobs[i]));
                }
            }
        }
    }
}
} // namespace UnitTests
