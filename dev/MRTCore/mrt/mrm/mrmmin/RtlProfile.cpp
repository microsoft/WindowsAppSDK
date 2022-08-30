// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"

namespace Microsoft::Resources
{

/*! 
 * Profile for use of MRT within RTL:
 *    - Only supports core environment & universal app platform 
 *    - Knows nothing about packages
 *    - Only implements language qualifier & qualifier type - all others stubbed
 *    - Knows how to find merged files but cannot write anything anywhere
 */
class RtlProfile : public CoreProfile
{
public:
    virtual ~RtlProfile() {}

    // CoreProfile::IsLoadPriFileAllowed = 0
    // Default core profile allows any PRI file to be loaded

    // CoreProfile::IsFullyQualifiedReferenceAllowed = 0
    // Default core profile allows references to files but not to packages

    // CoreProfile::IsResourceMapLookupByNameAllowed = 0
    // Default core profile allows resource map lookup by name

    // CoreProfile::IsResourceFileAutoLoadSupported
    // Default core profile supports autoload of any file

    // CoreProfile::GetRootFolderForFile = 0
    // Default core profile reports the folder which contains the PRI file

    // CoreProfile::IsLoadResourceMapAllowed = 0
    // Default core profile allows load resource map

    // CoreProfile::IsSupportedFileMagicNumber
    // Default core profile does not support legacy client or phone PRI files

    // CoreProfile::GetTargetPlatformAndVersionForFileMagic
    // Default core profile supports only universal files for the default
    // version of the wincore platform.

    // CoreProfile::GetTargetPlatformAndVersion
    // Default core profile uses default version of wincore platform

    // CoreProfile::GetNumEnvironments
    // Default core profile supports only CoreEnvironment

    // CoreProfile::GetEnvironmentVersionInfo
    // Default core profile supports only CoreEnvironment at index 0

    // CoreProfile::CreateEnvironment
    // Default core profile supports only CoreEnvironment at index 0

    // CoreProfile::GetTypeForQualifier
    HRESULT
    GetTypeForQualifier(_In_ const IEnvironment* pEnvironment, _In_ Atom qualifierAtom, _Out_ IBuildQualifierType** ppTypeOut) const;

    // CoreProfile::GetProviderForQualifier
    HRESULT GetProviderForQualifier(
        _In_ const IEnvironment* pEnvironment,
        _In_ Atom qualifierAtom,
        _Out_ IQualifierValueProvider** ppProviderOut) const;

    // CoreProfile::GetMergeFolders = 0
    // Default core profile gets default system merge folder and empty app folder

    // CoreProfile::GetBuildConfiguration
    // Default core profile returns default (universal) file with all capabilities

    // CoreProfile::GetDefaultUniqueName
    // Default core profile uses ms-appx scheme to construct unique name

    // CoreProfile::GetNumThreadAwareQualifiers
    // Default core profile implementation returns 0

    // CoreProfile::GetThreadAwareQualifierName
    // Default core profile supports no thread aware qualifiers

    static HRESULT CreateInstance(_Outptr_ RtlProfile** profile)
    {
        *profile = nullptr;
        RtlProfile* pRtrn = new RtlProfile();
        RETURN_IF_NULL_ALLOC(pRtrn);

        *profile = pRtrn;

        return S_OK;
    }

protected:
    RtlProfile() : CoreProfile() {}
};

// NOTE:  The current implementation of the language list qualifier type is bogus.  It doesn't actually do
// anything language-tag specific yet.

class RtlLanguageListQualifierType : public QualifierTypeBase
{
public:
    static HRESULT CreateInstance(_Outptr_ RtlLanguageListQualifierType** type)
    {
        *type = nullptr;

        RtlLanguageListQualifierType* pRtrn = new RtlLanguageListQualifierType();
        RETURN_IF_NULL_ALLOC(pRtrn);

        *type = pRtrn;

        return S_OK;
    }

    virtual ~RtlLanguageListQualifierType() {}

    HRESULT ValidateSingleQualifierValue(_In_ PCWSTR pValue) const override
    {
        if ((pValue == nullptr) || (*pValue == L'\0') || !_DefIsWellFormedTag(pValue))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
        }

        return S_OK;
    }

    double EvaluateSingleQualifierValue(_In_ PCWSTR valueOnAsset, _In_ PCWSTR valueFromProvider) const override
    {
        double result = 0.0;

        // Same value -> 1
        // Same value, but the provider value is a neutral -> 0.5, as we want to score a full match higher than a neutral.
        // Different value -> 0
        // This is not a full BCP47 distance match implementation, and will not match say en-GB and en-US.
        if (DefString_ICompare(valueOnAsset, valueFromProvider) == Def_Equal)
        {
            result = wcslen(valueOnAsset) > 3 ? 1.0 : 0.5;
        }

        return result;
    }

    HRESULT Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pszProviderValue, _Out_ double* score) const override
    {
        *score = 0.0;

        if (wcslen(pszProviderValue) > 0)
        {
            StringResult qualifierValue;
            RETURN_IF_FAILED(ValidateQualifier(pQualifier));
            RETURN_IF_FAILED(pQualifier->GetOperand2Literal(&qualifierValue));

            (void)_DefGetDistanceOfClosestLanguageInList(qualifierValue.GetRef(), pszProviderValue, L';', score);
            if (*score < 0.0)
            {
                // Not evaluated by previous function. Use base method.
                RETURN_IF_FAILED(QualifierTypeBase::Evaluate(pQualifier, pszProviderValue, score));
            }
        }

        return S_OK;
    }

    int GetMaxQualifierEntries() const override { return 256; }

protected:
    RtlLanguageListQualifierType() : QualifierTypeBase(ListValuesAllowed | EmptyValuesNotAllowed) {}
};

HRESULT
RtlProfile::GetTypeForQualifier(_In_ const IEnvironment* pEnvironment, _In_ Atom qualifierAtom, _Out_ IBuildQualifierType** ppTypeOut) const
{
    ResourceQualifier qualifier;

    *ppTypeOut = nullptr;

    RETURN_IF_FAILED(pEnvironment->GetQualifier(qualifierAtom, &qualifier));
    switch (static_cast<CoreEnvironment::QualifierTypeIndex>(qualifier.qualifierType.GetIndex()))
    {
    case CoreEnvironment::QualifierTypeIndex::LanguageList:
        RETURN_IF_FAILED(RtlLanguageListQualifierType::CreateInstance((RtlLanguageListQualifierType**)ppTypeOut));
        break;
    case CoreEnvironment::QualifierTypeIndex::Contrast:
    case CoreEnvironment::QualifierTypeIndex::RegionId:
    case CoreEnvironment::QualifierTypeIndex::LayoutDirection:
    case CoreEnvironment::QualifierTypeIndex::Theme:
        RETURN_IF_FAILED(StringIdentifierQualifierType::CreateInstance(
            12, QualifierTypeBase::RequiredValueQualifierTypeFlags, (StringIdentifierQualifierType**)ppTypeOut));
        break;
    case CoreEnvironment::QualifierTypeIndex::DXFeatureLevel:
        RETURN_IF_FAILED(StringIdentifierQualifierType::CreateInstance(
            5, QualifierTypeBase::OptionalValueQualifierTypeFlags, (StringIdentifierQualifierType**)ppTypeOut));
        break;
    case CoreEnvironment::QualifierTypeIndex::AlternateForm:
        RETURN_IF_FAILED(StringIdentifierQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_AlternateForm_Max_Length,
            QualifierTypeBase::OptionalValueQualifierTypeFlags,
            (StringIdentifierQualifierType**)ppTypeOut));
        break;
    case CoreEnvironment::QualifierTypeIndex::Configuration:
        RETURN_IF_FAILED(StringIdentifierQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_Configuration_Max_Length,
            QualifierTypeBase::OptionalValueQualifierTypeFlags,
            (StringIdentifierQualifierType**)ppTypeOut));
        break;
    case CoreEnvironment::QualifierTypeIndex::Scale:
        RETURN_IF_FAILED(IntegerQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_Scale_Min_Value,
            CoreEnvironment::Qualifier_Scale_Max_Value,
            false,
            (IntegerQualifierType**)ppTypeOut));
        break;
    case CoreEnvironment::QualifierTypeIndex::TargetSize:
        RETURN_IF_FAILED(IntegerQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_TargetSize_Min_Value,
            CoreEnvironment::Qualifier_TargetSize_Max_Value,
            true,
            (IntegerQualifierType**)ppTypeOut));
        break;
    case CoreEnvironment::QualifierTypeIndex::DeviceFamily:
        RETURN_IF_FAILED(StringIdentifierQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_DeviceFamily_MaxLength,
            QualifierTypeBase::RequiredValueQualifierTypeFlags,
            (StringIdentifierQualifierType**)ppTypeOut));
        break;
    case CoreEnvironment::QualifierTypeIndex::CustomQualifier:
        RETURN_IF_FAILED(StringIdentifierQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_DeviceFamily_MaxLength,
            QualifierTypeBase::OptionalListQualifierTypeFlags,
            (StringIdentifierQualifierType**)ppTypeOut));
        break;
    default:
        RETURN_HR(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT));
        break;
    }

    return S_OK;
}

HRESULT RtlProfile::GetProviderForQualifier(
    _In_ const IEnvironment* /*pEnvironment*/,
    _In_ Atom qualifierAtom,
    _Out_ IQualifierValueProvider** ppProviderOut) const
{
    if (qualifierAtom.GetIndex() == static_cast<Atom::Index>(CoreEnvironment::QualifierIndex::Language))
    {
        RETURN_IF_FAILED(WindowsDisplayLanguageProvider::CreateInstance(this, (WindowsDisplayLanguageProvider**)ppProviderOut));
    }
    else
    {
        RETURN_IF_FAILED(GenericQVProvider::CreateInstance((GenericQVProvider**)ppProviderOut));
    }

    return S_OK;
}

HRESULT CoreProfile::ChooseDefaultProfile(_Outptr_ CoreProfile** profile) { return RtlProfile::CreateInstance((RtlProfile**)profile); }

} // namespace Microsoft::Resources
