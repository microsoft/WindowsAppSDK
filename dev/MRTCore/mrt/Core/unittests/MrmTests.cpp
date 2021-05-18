// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <Windows.h>
#include <WexTestClass.h>
#include "..\src\MRM.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTest
{
class BasicTest
{
public:
    TEST_CLASS(BasicTest);

    TEST_METHOD(ReadResourceString)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;
        VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, nullptr, nullptr, L"resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceString), S_OK);

        VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Groove Music"), 0);

        MrmFreeResource(resourceString);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringWithResourceMap)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmMapHandle childResourceMap;
        VERIFY_ARE_EQUAL(MrmGetChildResourceMap(resourceManager, nullptr, L"Microsoft.UI.Xaml", &childResourceMap), S_OK);

        MrmMapHandle childChildResourceMap;
        VERIFY_ARE_EQUAL(MrmGetChildResourceMap(resourceManager, childResourceMap, L"Resources", &childChildResourceMap), S_OK);

        wchar_t* resourceString;
        VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, nullptr, childChildResourceMap, L"HelpTextMoreButton", &resourceString), S_OK);

        VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Invoke to show or hide the text entry fields."), 0);

        MrmFreeResource(resourceString);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringFromFullUri)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;
        VERIFY_ARE_EQUAL(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource://Microsoft.ZuneMusic/resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceString), S_OK);

        VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Groove Music"), 0);

        MrmFreeResource(resourceString);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringFromFullUri_ImplicitResourceMap)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;
        VERIFY_ARE_EQUAL(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource:///resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceString), S_OK);

        VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Groove Music"), 0);

        MrmFreeResource(resourceString);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringFromFullUri_InvalidUri)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;

        VERIFY_ARE_EQUAL(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource://", &resourceString), E_INVALIDARG);

        VERIFY_ARE_EQUAL(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource:///", &resourceString), E_INVALIDARG);

        VERIFY_ARE_EQUAL(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource:///abc", &resourceString), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));

        VERIFY_ARE_EQUAL(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource://abc", &resourceString), E_INVALIDARG);

        VERIFY_ARE_EQUAL(MrmLoadStringResourceFromResourceUri(resourceManager, nullptr, L"ms-resource://Microsoft.ZuneMusic/abc", &resourceString), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));

        VERIFY_ARE_EQUAL(
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
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmContextHandle resourceContext;
        VERIFY_ARE_EQUAL(MrmCreateResourceContext(resourceManager, &resourceContext), S_OK);

        PWSTR* qualifierNames = nullptr;
        UINT32 size = 0;
        VERIFY_ARE_EQUAL(MrmGetAllQualifierNames(resourceContext, &size, &qualifierNames), S_OK);

        // We currently support 12 qualifiers defined in MrmConstants.h
        VERIFY_ARE_EQUAL(size, 12u);
        VERIFY_ARE_EQUAL(wcscmp(*qualifierNames, L"Language"), 0);
        VERIFY_ARE_EQUAL(wcscmp(*(qualifierNames + 11), L"Custom"), 0);

        MrmFreeQualifierNamesOrValues(size, qualifierNames);

        {
            VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"Contrast", L"WHITE"), S_OK);
            VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"TargetSize", L"96"), S_OK);

            wchar_t* resourceString;
            VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, resourceContext, nullptr, L"Files/Assets/AppList.png", &resourceString), S_OK);

            // File resources have the path of the PRI file prepended to turn them into fully qualified paths.
            VERIFY_IS_NOT_NULL(wcsstr(resourceString, L"Assets\\contrast-white\\AppList.targetsize-96_contrast-white.png"));

            wchar_t* qualifierValue;
            VERIFY_ARE_EQUAL(MrmGetQualifier(resourceContext, L"Contrast", &qualifierValue), S_OK);
            VERIFY_ARE_EQUAL(wcscmp(qualifierValue, L"WHITE"), 0);
            MrmFreeResource(qualifierValue);

            VERIFY_ARE_EQUAL(MrmGetQualifier(resourceContext, L"TargetSize", &qualifierValue), S_OK);
            VERIFY_ARE_EQUAL(wcscmp(qualifierValue, L"96"), 0);
            MrmFreeResource(qualifierValue);

            MrmFreeResource(resourceString);
        }

        {
            VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"Contrast", L"BLACK"), S_OK);
            VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"TargetSize", L"72"), S_OK);

            wchar_t* resourceString;
            VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, resourceContext, nullptr, L"Files/Assets/AppList.png", &resourceString), S_OK);

            // File resources have the path of the PRI file prepended to turn them into fully qualified paths.
            VERIFY_IS_NOT_NULL(wcsstr(resourceString, L"Assets\\contrast-black\\AppList.targetsize-72_contrast-black.png"));

            MrmFreeResource(resourceString);
        }

        MrmDestroyResourceContext(resourceContext);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringWithLanguageQualifier)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmContextHandle resourceContext;
        VERIFY_ARE_EQUAL(MrmCreateResourceContext(resourceManager, &resourceContext), S_OK);

        wchar_t* resourceString;
        VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"Language", L"en-US"), S_OK);
        VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceString), S_OK);

        VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Equalizer"), 0);
        MrmFreeResource(resourceString);

        VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"Language", L"en-GB"), S_OK);
        VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceString), S_OK);

        VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Equaliser"), 0);
        MrmFreeResource(resourceString);

        // en-AU is closer to en-GB
        VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"Language", L"en-AU"), S_OK);
        VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceString), S_OK);

        VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Equaliser"), 0);
        MrmFreeResource(resourceString);

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadEmbeddedResourceFromFullUri)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmResourceData resourceData {};
        VERIFY_ARE_EQUAL(MrmLoadEmbeddedResourceFromResourceUri(resourceManager, nullptr, L"ms-resource://Microsoft.ZuneMusic/Files/Controls/AlbumBasicInfoControl.xbf", &resourceData), S_OK);

        VERIFY_ARE_EQUAL(resourceData.size, 15002u);

        MrmFreeResource(resourceData.data);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadEmbeddedResource)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmResourceData resourceData {};
        VERIFY_ARE_EQUAL(MrmLoadEmbeddedResource(resourceManager, nullptr, nullptr, L"Files/Controls/AlbumBasicInfoControl.xbf", &resourceData), S_OK);
        VERIFY_ARE_EQUAL(resourceData.size, 15002u);

        MrmFreeResource(resourceData.data);
        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadEmbeddedResourceAsString_Fails)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;
        VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, nullptr, nullptr, L"Files/Controls/AlbumBasicInfoControl.xbf", &resourceString), HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH));

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadStringOrEmbeddedResource)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        {
            MrmType resourceType;
            wchar_t* resourceString;
            MrmResourceData resourceData {};

            VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResource(resourceManager, nullptr, nullptr, L"Files/Controls/AlbumBasicInfoControl.xbf", &resourceType, &resourceString, &resourceData), S_OK);

            VERIFY_IS_NULL(resourceString);
            VERIFY_IS_TRUE(resourceType == MrmType_Embedded);
            VERIFY_IS_NOT_NULL(resourceData.data);
            VERIFY_ARE_EQUAL(resourceData.size, 15002u);

            MrmFreeResource(resourceData.data);
        }

        {
            MrmType resourceType;
            wchar_t* resourceString;
            MrmResourceData resourceData {};

            VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResource(resourceManager, nullptr, nullptr, L"resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceType, &resourceString, &resourceData), S_OK);

            VERIFY_IS_NOT_NULL(resourceString);
            VERIFY_IS_TRUE(resourceType == MrmType_String);
            VERIFY_IS_NULL(resourceData.data);
            VERIFY_ARE_EQUAL(resourceData.size, 0u);
            VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Groove Music"), 0);

            MrmFreeResource(resourceString);
        }

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadStringOrEmbeddedResourceWithQualifierOverride)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmContextHandle resourceContext;
        VERIFY_ARE_EQUAL(MrmCreateResourceContext(resourceManager, &resourceContext), S_OK);

        VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"Contrast", L"WHITE"), S_OK);
        VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"TargetSize", L"96"), S_OK);

        {
            MrmType resourceType;
            wchar_t* resourceString;
            MrmResourceData resourceData {};

            VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResource(resourceManager, resourceContext, nullptr, L"Files/Controls/AlbumBasicInfoControl.xbf", &resourceType, &resourceString, &resourceData), S_OK);

            VERIFY_IS_NULL(resourceString);
            VERIFY_IS_TRUE(resourceType == MrmType_Embedded);
            VERIFY_IS_NOT_NULL(resourceData.data);
            VERIFY_ARE_EQUAL(resourceData.size, 15002u);

            MrmFreeResource(resourceData.data);
        }

        {
            MrmType resourceType;
            wchar_t* resourceString;
            MrmResourceData resourceData {};

            VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResource(resourceManager, resourceContext, nullptr, L"Files/Assets/AppList.png", &resourceType, &resourceString, &resourceData), S_OK);

            VERIFY_IS_NOT_NULL(resourceString);
            VERIFY_IS_TRUE(resourceType == MrmType_Path);
            VERIFY_IS_NULL(resourceData.data);
            VERIFY_ARE_EQUAL(resourceData.size, 0u);

            // File resources have the path of the PRI file prepended to turn them into fully qualified paths.
            VERIFY_IS_NOT_NULL(wcsstr(resourceString, L"Assets\\contrast-white\\AppList.targetsize-96_contrast-white.png"));

            MrmFreeResource(resourceString);

            UINT32 qualifierCount;
            PWSTR* qualifierNames = nullptr;
            PWSTR* qualifierValues = nullptr;
            VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResourceWithQualifierValues(resourceManager, resourceContext, nullptr, L"Files/Assets/AppList.png", &resourceType, &resourceString, &resourceData, &qualifierCount, &qualifierNames, &qualifierValues), S_OK);

            VERIFY_IS_NOT_NULL(resourceString);
            VERIFY_IS_TRUE(resourceType == MrmType_Path);
            VERIFY_IS_NULL(resourceData.data);
            VERIFY_ARE_EQUAL(resourceData.size, 0u);

            // File resources have the path of the PRI file prepended to turn them into fully qualified paths.
            VERIFY_IS_NOT_NULL(wcsstr(resourceString, L"Assets\\contrast-white\\AppList.targetsize-96_contrast-white.png"));

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
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        // Enumerate under Microsoft.UI.Xaml/Resources
        MrmMapHandle childResourceMap;
        VERIFY_ARE_EQUAL(MrmGetChildResourceMap(resourceManager, nullptr, L"Microsoft.UI.Xaml", &childResourceMap), S_OK);

        MrmMapHandle childChildResourceMap;
        VERIFY_ARE_EQUAL(MrmGetChildResourceMap(resourceManager, childResourceMap, L"Resources", &childChildResourceMap), S_OK);

        UINT32 count;
        VERIFY_ARE_EQUAL(MrmGetResourceCount(resourceManager, childChildResourceMap, &count), S_OK);
        VERIFY_ARE_EQUAL(count, static_cast<UINT32>(78));

        MrmType resourceType;
        wchar_t* resourceString = nullptr;
        wchar_t* resourceName = nullptr;
        MrmResourceData resourceData {};
        for (UINT32 i = 0; i < count; i++)
        {
            VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResourceByIndex(resourceManager, nullptr, childChildResourceMap, i, &resourceType, &resourceName, &resourceString, &resourceData), S_OK);

            VERIFY_IS_TRUE(resourceType == MrmType_String);
            VERIFY_IS_NULL(resourceData.data);
            VERIFY_ARE_EQUAL(resourceData.size, 0u);

            switch (i)
            {
            case 0:
            {
                VERIFY_ARE_EQUAL(wcscmp(resourceName, L"AutomationNameAlphaSlider"), 0);
                VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Opacity"), 0);
                break;
            }

            case 1:
            {
                VERIFY_ARE_EQUAL(wcscmp(resourceName, L"AutomationNameAlphaTextBox"), 0);
                VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Opacity"), 0);
                break;
            }

            case 2:
            {
                VERIFY_ARE_EQUAL(wcscmp(resourceName, L"AutomationNameBlueTextBox"), 0);
                VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Blue"), 0);
                break;
            }

            case 77:
            {
                VERIFY_ARE_EQUAL(wcscmp(resourceName, L"ValueStringValueSliderWithoutColorName"), 0);
                VERIFY_ARE_EQUAL(wcscmp(resourceString, L"%1!u!"), 0);
                break;
            }
            }

            MrmFreeResource(resourceString);
            MrmFreeResource(resourceName);
            resourceString = nullptr;
            resourceName = nullptr;
        }

        VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResourceByIndex(resourceManager, nullptr, childChildResourceMap, count, &resourceType, &resourceName, &resourceString, &resourceData), HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND));

        // Enumerate under Files/Controls
        VERIFY_ARE_EQUAL(MrmGetChildResourceMap(resourceManager, nullptr, L"Files", &childResourceMap), S_OK);
        VERIFY_ARE_EQUAL(MrmGetChildResourceMap(resourceManager, childResourceMap, L"Controls", &childChildResourceMap), S_OK);
        VERIFY_ARE_EQUAL(MrmGetResourceCount(resourceManager, childChildResourceMap, &count), S_OK);
        VERIFY_ARE_EQUAL(count, static_cast<UINT32>(28));

        for (UINT32 i = 0; i < count; i++)
        {
            VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResourceByIndex(resourceManager, nullptr, childChildResourceMap, i, &resourceType, &resourceName, &resourceString, &resourceData), S_OK);

            VERIFY_IS_TRUE(resourceType == MrmType_Embedded);
            VERIFY_IS_NULL(resourceString);
            VERIFY_IS_NOT_NULL(resourceData.data);
            VERIFY_IS_TRUE(resourceData.size != 0);

            switch (i)
            {
            case 0:
            {
                VERIFY_ARE_EQUAL(wcscmp(resourceName, L"AlbumBasicInfoControl.xbf"), 0);
                break;
            }

            case 1:
            {
                VERIFY_ARE_EQUAL(wcscmp(resourceName, L"AlbumMetadataEditDialog.xbf"), 0);
                break;
            }

            case 2:
            {
                VERIFY_ARE_EQUAL(wcscmp(resourceName, L"ArtistBasicInfoControl.xbf"), 0);
                break;
            }

            case 27:
            {
                VERIFY_ARE_EQUAL(wcscmp(resourceName, L"TrackMetadataEditDialog.xbf"), 0);
                break;
            }
            }

            MrmFreeResource(resourceData.data);
            MrmFreeResource(resourceName);
            resourceName = nullptr;
            resourceData.data = nullptr;
            resourceData.size = 0;
        }

        VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResourceByIndex(resourceManager, nullptr, childChildResourceMap, count, &resourceType, &resourceName, &resourceString, &resourceData), HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND));

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(ReadResourceStringWithQualifierValue)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        MrmContextHandle resourceContext;
        VERIFY_ARE_EQUAL(MrmCreateResourceContext(resourceManager, &resourceContext), S_OK);

        MrmType resourceType;
        wchar_t* resourceString;
        MrmResourceData resourceData{};
        UINT32 qualifierCount;
        PWSTR* qualifierNames = nullptr;
        PWSTR* qualifierValues = nullptr;
        VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"Language", L"en-US"), S_OK);
        VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResourceWithQualifierValues(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceType, &resourceString, &resourceData, &qualifierCount, &qualifierNames, &qualifierValues), S_OK);

        VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Equalizer"), 0);
        MrmFreeResource(resourceString);

        VerifyQualifierValue(qualifierCount, qualifierNames, qualifierValues, L"Language", L"en-US");
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierNames);
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierValues);

        VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"Language", L"en-GB"), S_OK);
        VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResourceWithQualifierValues(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceType, &resourceString, &resourceData, &qualifierCount, &qualifierNames, &qualifierValues), S_OK);

        VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Equaliser"), 0);
        MrmFreeResource(resourceString);

        VerifyQualifierValue(qualifierCount, qualifierNames, qualifierValues, L"Language", L"en-GB");
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierNames);
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierValues);

        // en-AU is closer to en-GB
        VERIFY_ARE_EQUAL(MrmSetQualifier(resourceContext, L"Language", L"en-AU"), S_OK);
        VERIFY_ARE_EQUAL(MrmLoadStringOrEmbeddedResourceWithQualifierValues(resourceManager, resourceContext, nullptr, L"resources/IDS_WHATS_NEW_1710_2_EQUALIZER_TITLE", &resourceType, &resourceString, &resourceData, &qualifierCount, &qualifierNames, &qualifierValues), S_OK);

        VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Equaliser"), 0);
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
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L"invalid.pri", &resourceManager), HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));
    }

    TEST_METHOD(InvalidResource)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        wchar_t* resourceString;
        VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, nullptr, nullptr, L"resources/wrongresource", &resourceString), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(RepeatedCalls)
    {
        MrmManagerHandle resourceManager;
        VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

        for (unsigned int i = 0; i < 100; i++)
        {
            wchar_t* resourceString;
            VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, nullptr, nullptr, L"resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceString), S_OK);
            VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Groove Music"), 0);

            MrmFreeResource(resourceString);
        }

        MrmDestroyResourceManager(resourceManager);
    }

    TEST_METHOD(RepeatedInits)
    {
        for (unsigned int i = 0; i < 100; i++)
        {
            MrmManagerHandle resourceManager;
            VERIFY_ARE_EQUAL(MrmCreateResourceManager(L".\\resources.pri", &resourceManager), S_OK);

            wchar_t* resourceString;
            VERIFY_ARE_EQUAL(MrmLoadStringResource(resourceManager, nullptr, nullptr, L"resources/IDS_MANIFEST_MUSIC_APP_NAME", &resourceString), S_OK);
            VERIFY_ARE_EQUAL(wcscmp(resourceString, L"Groove Music"), 0);

            MrmFreeResource(resourceString);
            MrmDestroyResourceManager(resourceManager);
        }
    }

    TEST_METHOD(GetFilePath)
    {
        wchar_t* path;
        VERIFY_ARE_EQUAL(MrmGetFilePathFromName(L"resources.pri", &path), S_OK);
        VERIFY_IS_NOT_NULL(wcsstr(path, L"resources.pri"));
        MrmFreeResource(path);

        VERIFY_ARE_EQUAL(MrmGetFilePathFromName(L"something.pri", &path), S_OK);
        // Even if the file doesn't exist, we will still return a path. This is for those don't use PRI for resource.
        VERIFY_IS_NOT_NULL(wcsstr(path, L"something.pri"));
        MrmFreeResource(path);

        VERIFY_ARE_EQUAL(MrmGetFilePathFromName(nullptr, &path), S_OK);
        VERIFY_IS_NOT_NULL(wcsstr(path, L"resources.pri"));
        MrmFreeResource(path);
    }

private:
    void VerifyQualifierValue(UINT32 qualifierCount, PWSTR* qualifierNames, PWSTR* qualifierValues, PCWSTR name, PCWSTR expectedValue)
    {
        VERIFY_IS_TRUE(qualifierCount > 0);
        bool found = false;
        for (UINT32 i = 0; i < qualifierCount; i++)
        {
            if (0 == _wcsicmp(name, qualifierNames[i]))
            {
                VERIFY_IS_TRUE(0 == _wcsicmp(expectedValue, qualifierValues[i]));
                found = true;
                break;
            }
        }
        VERIFY_IS_TRUE(found);
    }
};
} // namespace UnitTest
