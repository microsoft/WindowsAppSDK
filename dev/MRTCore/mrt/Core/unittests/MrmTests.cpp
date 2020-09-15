// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include <Windows.h>
#include "..\src\MRM.h"

#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{

TEST_CLASS(BasicTest)
{
public:
    TEST_METHOD(ReadResourceString)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;
        Assert::AreEqual(MrmLoadStringResource(resourceManager, nullptr, nullptr, L"resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceString), S_OK);

        Assert::AreEqual(resourceString, L"Groove Music");

        MrmFreeResource(resourceString);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringWithResourceMap)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmMapHandle childResourceMap;
        Assert::AreEqual(MrmGetChildResourceMap(resourceManager, nullptr, L"Microsoft.UI.Xaml", &childResourceMap), S_OK);

        MrmMapHandle childChildResourceMap;
        Assert::AreEqual(MrmGetChildResourceMap(resourceManager, childResourceMap, L"Resources", &childChildResourceMap), S_OK);

        wchar_t* resourceString;
        Assert::AreEqual(MrmLoadStringResource(resourceManager, nullptr, childChildResourceMap, L"HelpTextMoreButton", &resourceString), S_OK);

        Assert::AreEqual(resourceString, L"Invoke to show or hide the text entry fields.");

        MrmFreeResource(resourceString);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringFromFullUri)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;
        Assert::AreEqual(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource://Microsoft.ZuneMusic/resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceString), S_OK);

        Assert::AreEqual(resourceString, L"Groove Music");

        MrmFreeResource(resourceString);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringFromFullUri_ImplicitResourceMap)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;
        Assert::AreEqual(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource:///resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceString), S_OK);

        Assert::AreEqual(resourceString, L"Groove Music");

        MrmFreeResource(resourceString);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringFromFullUri_InvalidUri)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;

        Assert::AreEqual(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource://", &resourceString), E_INVALIDARG);

        Assert::AreEqual(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource:///", &resourceString), E_INVALIDARG);

        Assert::AreEqual(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource:///abc", &resourceString), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));

        Assert::AreEqual(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource://abc", &resourceString), E_INVALIDARG);

        Assert::AreEqual(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource://Microsoft.ZuneMusic/abc", &resourceString), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));

        Assert::AreEqual(
            MrmLoadStringResourceFromResourceUri(
                resourceManager,
                nullptr,
                L"ms-resource://"
                L"1234567890112345678901234567890112345678901234567890112345678901234567890112345678901234567890112345678901234567890112345"
                L"6789012345678901123456789012345678901123456789012345678901123456789012345678901123456789012345678901234567890123456789012"
                L"345678901234567890123456",
                &resourceString),
            E_INVALIDARG);

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringWithQualifierOverride)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmContextHandle resourceContext;
        Assert::AreEqual(MrmCreateResourceContext(resourceManager, &resourceContext), S_OK);

        PWSTR* qualifierNames = nullptr;
        UINT32 size = 0;
        Assert::AreEqual(MrmGetAllQualifierNames(resourceContext, &size, &qualifierNames), S_OK);

        // We currently support 12 qualifiers defined in MrmConstants.h
        Assert::AreEqual(size, 12u);
        Assert::AreEqual(*qualifierNames, L"Language");
        Assert::AreEqual(*(qualifierNames + 11), L"Custom");

        MrmFreeQualifierNamesOrValues(size, qualifierNames);

        {
            Assert::AreEqual(MrmSetQualifier(resourceContext, L"Contrast", L"WHITE"), S_OK);
            Assert::AreEqual(MrmSetQualifier(resourceContext, L"TargetSize", L"96"), S_OK);

            wchar_t* resourceString;
            Assert::AreEqual(MrmLoadStringResource(resourceManager, resourceContext, nullptr, L"Files/Assets/AppList.png", &resourceString), S_OK);

            // File resources have the path of the PRI file prepended to turn them into fully qualified paths.
            Assert::IsNotNull(wcsstr(resourceString, L"Assets\\contrast-white\\AppList.targetsize-96_contrast-white.png"));

            wchar_t* qualifierValue;
            Assert::AreEqual(MrmGetQualifier(resourceContext, L"Contrast", &qualifierValue), S_OK);
            Assert::AreEqual(qualifierValue, L"WHITE");
            MrmFreeResource(qualifierValue);

            Assert::AreEqual(MrmGetQualifier(resourceContext, L"TargetSize", &qualifierValue), S_OK);
            Assert::AreEqual(qualifierValue, L"96");
            MrmFreeResource(qualifierValue);

            MrmFreeResource(resourceString);
        }

        {
            Assert::AreEqual(MrmSetQualifier(resourceContext, L"Contrast", L"BLACK"), S_OK);
            Assert::AreEqual(MrmSetQualifier(resourceContext, L"TargetSize", L"72"), S_OK);

            wchar_t* resourceString;
            Assert::AreEqual(MrmLoadStringResource(resourceManager, resourceContext, nullptr, L"Files/Assets/AppList.png", &resourceString), S_OK);

            // File resources have the path of the PRI file prepended to turn them into fully qualified paths.
            Assert::IsNotNull(wcsstr(resourceString, L"Assets\\contrast-black\\AppList.targetsize-72_contrast-black.png"));

            MrmFreeResource(resourceString);
        }

        MrmDestroyResourceContext(resourceContext);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringWithLanguageQualifier)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmContextHandle resourceContext;
        Assert::AreEqual(MrmCreateResourceContext(resourceManager, &resourceContext), S_OK);

        wchar_t* resourceString;
        Assert::AreEqual(MrmSetQualifier(resourceContext, L"Language", L"en-US"), S_OK);
        Assert::AreEqual(MrmLoadStringResource(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceString), S_OK);

        Assert::AreEqual(resourceString, L"Equalizer");
        MrmFreeResource(resourceString);

        Assert::AreEqual(MrmSetQualifier(resourceContext, L"Language", L"en-GB"), S_OK);
        Assert::AreEqual(MrmLoadStringResource(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceString), S_OK);

        Assert::AreEqual(resourceString, L"Equaliser");
        MrmFreeResource(resourceString);

        // en-AU is closer to en-GB
        Assert::AreEqual(MrmSetQualifier(resourceContext, L"Language", L"en-AU"), S_OK);
        Assert::AreEqual(MrmLoadStringResource(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceString), S_OK);

        Assert::AreEqual(resourceString, L"Equaliser");
        MrmFreeResource(resourceString);

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadEmbeddedResourceFromFullUri)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmResourceData resourceData {};
        Assert::AreEqual(MrmLoadEmbeddedResourceFromResourceUri(resourceManager, nullptr, L"ms-resource://Microsoft.ZuneMusic/Files/Controls/AlbumBasicInfoControl.xbf", &resourceData), S_OK);

        Assert::AreEqual(resourceData.size, 15002u);

        MrmFreeResource(resourceData.data);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadEmbeddedResource)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmResourceData resourceData {};
        Assert::AreEqual(MrmLoadEmbeddedResource(resourceManager, nullptr, nullptr, L"Files/Controls/AlbumBasicInfoControl.xbf", &resourceData), S_OK);
        Assert::AreEqual(resourceData.size, 15002u);

        MrmFreeResource(resourceData.data);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadEmbeddedResourceAsString_Fails)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;
        Assert::AreEqual(MrmLoadStringResource(resourceManager, nullptr, nullptr, L"Files/Controls/AlbumBasicInfoControl.xbf", &resourceString), HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH));

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadStringOrEmbeddedResource)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        {
            MrmType resourceType;
            wchar_t* resourceString;
            MrmResourceData resourceData {};

            Assert::AreEqual(MrmLoadStringOrEmbeddedResource(resourceManager, nullptr, nullptr, L"Files/Controls/AlbumBasicInfoControl.xbf", &resourceType, &resourceString, &resourceData), S_OK);

            Assert::IsNull(resourceString);
            Assert::IsTrue(resourceType == MrmType_Embedded);
            Assert::IsNotNull(resourceData.data);
            Assert::AreEqual(resourceData.size, 15002u);

            MrmFreeResource(resourceData.data);
        }

        {
            MrmType resourceType;
            wchar_t* resourceString;
            MrmResourceData resourceData {};

            Assert::AreEqual(MrmLoadStringOrEmbeddedResource(resourceManager, nullptr, nullptr, L"resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceType, &resourceString, &resourceData), S_OK);

            Assert::IsNotNull(resourceString);
            Assert::IsTrue(resourceType == MrmType_String);
            Assert::IsNull(resourceData.data);
            Assert::AreEqual(resourceData.size, 0u);
            Assert::AreEqual(resourceString, L"Groove Music");

            MrmFreeResource(resourceString);
        }

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadStringOrEmbeddedResourceWithQualifierOverride)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmContextHandle resourceContext;
        Assert::AreEqual(MrmCreateResourceContext(resourceManager, &resourceContext), S_OK);

        Assert::AreEqual(MrmSetQualifier(resourceContext, L"Contrast", L"WHITE"), S_OK);
        Assert::AreEqual(MrmSetQualifier(resourceContext, L"TargetSize", L"96"), S_OK);

        {
            MrmType resourceType;
            wchar_t* resourceString;
            MrmResourceData resourceData {};

            Assert::AreEqual(MrmLoadStringOrEmbeddedResource(resourceManager, resourceContext, nullptr, L"Files/Controls/AlbumBasicInfoControl.xbf", &resourceType, &resourceString, &resourceData), S_OK);

            Assert::IsNull(resourceString);
            Assert::IsTrue(resourceType == MrmType_Embedded);
            Assert::IsNotNull(resourceData.data);
            Assert::AreEqual(resourceData.size, 15002u);

            MrmFreeResource(resourceData.data);
        }

        {
            MrmType resourceType;
            wchar_t* resourceString;
            MrmResourceData resourceData {};

            Assert::AreEqual(MrmLoadStringOrEmbeddedResource(resourceManager, resourceContext, nullptr, L"Files/Assets/AppList.png", &resourceType, &resourceString, &resourceData), S_OK);

            Assert::IsNotNull(resourceString);
            Assert::IsTrue(resourceType == MrmType_Path);
            Assert::IsNull(resourceData.data);
            Assert::AreEqual(resourceData.size, 0u);

            // File resources have the path of the PRI file prepended to turn them into fully qualified paths.
            Assert::IsNotNull(wcsstr(resourceString, L"Assets\\contrast-white\\AppList.targetsize-96_contrast-white.png"));

            MrmFreeResource(resourceString);

            UINT32 qualifierCount;
            PWSTR* qualifierNames = nullptr;
            PWSTR* qualifierValues = nullptr;
            Assert::AreEqual(MrmLoadStringOrEmbeddedResourceWithQualifierValues(resourceManager, resourceContext, nullptr, L"Files/Assets/AppList.png", &resourceType, &resourceString, &resourceData, &qualifierCount, &qualifierNames, &qualifierValues), S_OK);

            Assert::IsNotNull(resourceString);
            Assert::IsTrue(resourceType == MrmType_Path);
            Assert::IsNull(resourceData.data);
            Assert::AreEqual(resourceData.size, 0u);

            // File resources have the path of the PRI file prepended to turn them into fully qualified paths.
            Assert::IsNotNull(wcsstr(resourceString, L"Assets\\contrast-white\\AppList.targetsize-96_contrast-white.png"));

            VerifyQualifierValue(qualifierCount, qualifierNames, qualifierValues, L"Contrast", L"WHITE");
            VerifyQualifierValue(qualifierCount, qualifierNames, qualifierValues, L"TargetSize", L"96");
            MrmFreeQualifierNamesOrValues(qualifierCount, qualifierNames);
            MrmFreeQualifierNamesOrValues(qualifierCount, qualifierValues);

            MrmFreeResource(resourceString);
        }

        MrmDestroyResourceContext(resourceContext);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(EnumerateResourceMap)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        // Enumerate under Microsoft.UI.Xaml/Resources
        MrmMapHandle childResourceMap;
        Assert::AreEqual(MrmGetChildResourceMap(resourceManager, nullptr, L"Microsoft.UI.Xaml", &childResourceMap), S_OK);

        MrmMapHandle childChildResourceMap;
        Assert::AreEqual(MrmGetChildResourceMap(resourceManager, childResourceMap, L"Resources", &childChildResourceMap), S_OK);

        UINT32 count;
        Assert::AreEqual(MrmGetResourceCount(resourceManager, childChildResourceMap, &count), S_OK);
        Assert::AreEqual<UINT32>(count, 78);

        MrmType resourceType;
        wchar_t* resourceString = nullptr;
        wchar_t* resourceName = nullptr;
        MrmResourceData resourceData {};
        for (UINT32 i = 0; i < count; i++)
        {
            Assert::AreEqual(MrmLoadStringOrEmbeddedResourceByIndex(resourceManager, nullptr, childChildResourceMap, i, &resourceType, &resourceName, &resourceString, &resourceData), S_OK);

            Assert::IsTrue(resourceType == MrmType_String);
            Assert::IsNull(resourceData.data);
            Assert::AreEqual(resourceData.size, 0u);

            switch (i)
            {
            case 0:
            {
                Assert::AreEqual(resourceName, L"AutomationNameAlphaSlider");
                Assert::AreEqual(resourceString, L"Opacity");
                break;
            }

            case 1:
            {
                Assert::AreEqual(resourceName, L"AutomationNameAlphaTextBox");
                Assert::AreEqual(resourceString, L"Opacity");
                break;
            }

            case 2:
            {
                Assert::AreEqual(resourceName, L"AutomationNameBlueTextBox");
                Assert::AreEqual(resourceString, L"Blue");
                break;
            }

            case 77:
            {
                Assert::AreEqual(resourceName, L"ValueStringValueSliderWithoutColorName");
                Assert::AreEqual(resourceString, L"%1!u!");
                break;
            }
            }

            MrmFreeResource(resourceString);
            MrmFreeResource(resourceName);
            resourceString = nullptr;
            resourceName = nullptr;
        }

        Assert::AreEqual(MrmLoadStringOrEmbeddedResourceByIndex(resourceManager, nullptr, childChildResourceMap, count, &resourceType, &resourceName, &resourceString, &resourceData), HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND));

        // Enumerate under Files/Controls
        Assert::AreEqual(MrmGetChildResourceMap(resourceManager, nullptr, L"Files", &childResourceMap), S_OK);
        Assert::AreEqual(MrmGetChildResourceMap(resourceManager, childResourceMap, L"Controls", &childChildResourceMap), S_OK);
        Assert::AreEqual(MrmGetResourceCount(resourceManager, childChildResourceMap, &count), S_OK);
        Assert::AreEqual<UINT32>(count, 28);

        for (UINT32 i = 0; i < count; i++)
        {
            Assert::AreEqual(MrmLoadStringOrEmbeddedResourceByIndex(resourceManager, nullptr, childChildResourceMap, i, &resourceType, &resourceName, &resourceString, &resourceData), S_OK);

            Assert::IsTrue(resourceType == MrmType_Embedded);
            Assert::IsNull(resourceString);
            Assert::IsNotNull(resourceData.data);
            Assert::IsTrue(resourceData.size != 0);

            switch (i)
            {
            case 0:
            {
                Assert::AreEqual(resourceName, L"AlbumBasicInfoControl.xbf");
                break;
            }

            case 1:
            {
                Assert::AreEqual(resourceName, L"AlbumMetadataEditDialog.xbf");
                break;
            }

            case 2:
            {
                Assert::AreEqual(resourceName, L"ArtistBasicInfoControl.xbf");
                break;
            }

            case 27:
            {
                Assert::AreEqual(resourceName, L"TrackMetadataEditDialog.xbf");
                break;
            }
            }

            MrmFreeResource(resourceData.data);
            MrmFreeResource(resourceName);
            resourceName = nullptr;
            resourceData.data = nullptr;
            resourceData.size = 0;
        }

        Assert::AreEqual(MrmLoadStringOrEmbeddedResourceByIndex(resourceManager, nullptr, childChildResourceMap, count, &resourceType, &resourceName, &resourceString, &resourceData), HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND));

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringWithQualifierValue)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmContextHandle resourceContext;
        Assert::AreEqual(MrmCreateResourceContext(resourceManager, &resourceContext), S_OK);

        MrmType resourceType;
        wchar_t* resourceString;
        MrmResourceData resourceData{};
        UINT32 qualifierCount;
        PWSTR* qualifierNames = nullptr;
        PWSTR* qualifierValues = nullptr;
        Assert::AreEqual(MrmSetQualifier(resourceContext, L"Language", L"en-US"), S_OK);
        Assert::AreEqual(MrmLoadStringOrEmbeddedResourceWithQualifierValues(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceType, &resourceString, &resourceData, &qualifierCount, &qualifierNames, &qualifierValues), S_OK);

        Assert::AreEqual(resourceString, L"Equalizer");
        MrmFreeResource(resourceString);

        VerifyQualifierValue(qualifierCount, qualifierNames, qualifierValues, L"Language", L"en-US");
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierNames);
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierValues);

        Assert::AreEqual(MrmSetQualifier(resourceContext, L"Language", L"en-GB"), S_OK);
        Assert::AreEqual(MrmLoadStringOrEmbeddedResourceWithQualifierValues(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceType, &resourceString, &resourceData, &qualifierCount, &qualifierNames, &qualifierValues), S_OK);

        Assert::AreEqual(resourceString, L"Equaliser");
        MrmFreeResource(resourceString);

        VerifyQualifierValue(qualifierCount, qualifierNames, qualifierValues, L"Language", L"en-GB");
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierNames);
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierValues);

        // en-AU is closer to en-GB
        Assert::AreEqual(MrmSetQualifier(resourceContext, L"Language", L"en-AU"), S_OK);
        Assert::AreEqual(MrmLoadStringOrEmbeddedResourceWithQualifierValues(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceType, &resourceString, &resourceData, &qualifierCount, &qualifierNames, &qualifierValues), S_OK);

        Assert::AreEqual(resourceString, L"Equaliser");
        MrmFreeResource(resourceString);

        // resource candidate for en-GB is picked as en-AU is closer to en-GB
        VerifyQualifierValue(qualifierCount, qualifierNames, qualifierValues, L"Language", L"en-GB");
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierNames);
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierValues);

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(InvalidPriName)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L"invalid.pri", &resourceManager), HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));
    }

    TEST_METHOD(InvalidResource)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;
        Assert::AreEqual(MrmLoadStringResource(resourceManager, nullptr, nullptr, L"resources/wrongresource", &resourceString), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(RepeatedCalls)
    {
        MrmManagerHandle resourceManager;
        Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        for (unsigned int i = 0; i < 100; i++)
        {
            wchar_t* resourceString;
            Assert::AreEqual(MrmLoadStringResource(resourceManager, nullptr, nullptr, L"resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceString), S_OK);
            Assert::AreEqual(resourceString, L"Groove Music");

            MrmFreeResource(resourceString);
        }

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(RepeatedInits)
    {
        for (unsigned int i = 0; i < 100; i++)
        {
            MrmManagerHandle resourceManager;
            Assert::AreEqual(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

            wchar_t* resourceString;
            Assert::AreEqual(MrmLoadStringResource(resourceManager, nullptr, nullptr, L"resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceString), S_OK);
            Assert::AreEqual(resourceString, L"Groove Music");

            MrmFreeResource(resourceString);
            MrmDestroyResourceManager(resourceManager);
        }
    }

private:
    void VerifyQualifierValue(UINT32 qualifierCount, PWSTR* qualifierNames, PWSTR* qualifierValues, PCWSTR name, PCWSTR expectedValue)
    {
        Assert::IsTrue(qualifierCount > 0);
        bool found = false;
        for (UINT32 i = 0; i < qualifierCount; i++)
        {
            if (0 == _wcsicmp(name, qualifierNames[i]))
            {
                Assert::IsTrue(0 == _wcsicmp(expectedValue, qualifierValues[i]));
                found = true;
                break;
            }
        }
        Assert::IsTrue(found);
    }
};
} // namespace UnitTest
