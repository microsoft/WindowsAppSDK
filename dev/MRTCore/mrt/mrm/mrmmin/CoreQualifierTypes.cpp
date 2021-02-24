// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

#include "mrm/platform/WindowsCore.h"
#include "mrm/platform/CoreQualifierTypes.h"

namespace Microsoft::Resources
{

HRESULT ContrastQualifierType::CreateInstance(_Outptr_ ContrastQualifierType** type)
{
    *type = nullptr;

    ContrastQualifierType* pRtrn = new ContrastQualifierType();
    RETURN_IF_NULL_ALLOC(pRtrn);

    *type = pRtrn;

    return S_OK;
}

HRESULT ContrastQualifierType::Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pszProviderValue, _Out_ double* score) const
{
    *score = 0.0;

    StringResult qualifierValue;
    double result = 0.0;

    RETURN_IF_FAILED(ValidateQualifier(pQualifier));
    RETURN_IF_FAILED(ValidateQualifierValue(pszProviderValue));
    RETURN_IF_FAILED(pQualifier->GetOperand2Literal(&qualifierValue));

    PCWSTR pszQualifierValue = qualifierValue.GetRef();

    // same value => 1.0
    // any of standard => 0.0
    // asset white  => 0.5
    // others => 0.1
    if (CompareStringOrdinal(pszProviderValue, -1, pszQualifierValue, -1, TRUE) == 2)
    {
        result = 1.0;
    }
    else
    {
        if (CompareStringOrdinal(CoreEnvironment::ContrastValue_Standard, -1, pszProviderValue, -1, TRUE) == 2 ||
            CompareStringOrdinal(CoreEnvironment::ContrastValue_Standard, -1, pszQualifierValue, -1, TRUE) == 2)
        {
            result = 0.0;
        }
        else if (CompareStringOrdinal(CoreEnvironment::ContrastValue_High, -1, pszQualifierValue, -1, TRUE) == 2)
        {
            result = 0.5;
        }
        else if (CompareStringOrdinal(CoreEnvironment::ContrastValue_White, -1, pszQualifierValue, -1, TRUE) == 2)
        {
            result = 0.1;
        }
        else if (CompareStringOrdinal(CoreEnvironment::ContrastValue_White, -1, pszProviderValue, -1, TRUE) == 2)
        {
            result = 0.1;
        }
        else if (CompareStringOrdinal(CoreEnvironment::ContrastValue_Black, -1, pszQualifierValue, -1, TRUE) == 2)
        {
            // make sure the asset (condition) value is a supported one by adding this additional comparison.
            result = 0.5;
        }
        else
        {
            result = 0.0;
        }
    }

    *score = result;

    return S_OK;
}

HRESULT ScaleQualifierType::CreateInstance(_Outptr_ ScaleQualifierType** type)
{
    *type = nullptr;

    ScaleQualifierType* pRtrn = new ScaleQualifierType();
    RETURN_IF_NULL_ALLOC(pRtrn);

    *type = pRtrn;

    return S_OK;
}

HRESULT ScaleQualifierType::GetPackagingInfo(
    _In_ const IQualifier* pQualifier,
    _In_ UINT32 buildConfiguration,
    _In_reads_(numAutoPackageValues) PCWSTR* const ppAutoPackageValues,
    _In_ size_t const numAutoPackageValues,
    _Out_ PackagingFlags* pFlagsOut,
    _Inout_ StringResult* pAffinityOut) const
{
    StringResult qualifierValue;

    // by default, scale is reported and is allowed in resource packages
    *pFlagsOut = PackagingAllowResourcePackage | PackagingReportQualifier;

    RETURN_IF_FAILED(ValidateQualifier(pQualifier));
    RETURN_IF_FAILED(pQualifier->GetOperand2Literal(&qualifierValue));

    int iQualifierValue = _wtoi(qualifierValue.GetRef());
    double fallbackScore;

    // If no autoPackage list, use previous method.
    if (ppAutoPackageValues == nullptr || numAutoPackageValues == 0)
    {
        // Scale 80 is special. It always goes in the main package and shouldn't be reported.
        if (iQualifierValue == 80)
        {
            *pFlagsOut = PackagingBlockResourcePackage | PackagingDoNotReportQualifier;
            return pAffinityOut->SetRef(DefaultPackagingAffinity);
        }

        // Granular splitting means you never end up in the default package.
        RETURN_IF_FAILED(pQualifier->GetFallbackScore(&fallbackScore));
        if ((fallbackScore == 1.0) && ((buildConfiguration & MrmBuildConfiguration::UseGranularResourceSplittingFlag) == 0))
        {
            return pAffinityOut->SetRef(DefaultPackagingAffinity);
        }

        return pAffinityOut->SetContentsFromOther(&qualifierValue);
    }

    RETURN_IF_FAILED(pQualifier->GetFallbackScore(&fallbackScore));

    if ((iQualifierValue < 100) || (fallbackScore == 1.0))
    {
        // Scale values less than 100 are special, they always go in the main package
        // and are not reported.
        if (iQualifierValue < 100)
        {
            *pFlagsOut = PackagingBlockResourcePackage | PackagingDoNotReportQualifier;
        }
        return pAffinityOut->SetRef(DefaultPackagingAffinity);
    }

    int indexOfBestMatch = -1;
    int bestMatchDelta = m_maxAllowedValue + 1; // Initially set larger than max, so that anything will be better.

    for (size_t i = 0; i < numAutoPackageValues; i++)
    {
        if ((ppAutoPackageValues[i] == nullptr) || (ppAutoPackageValues[i][0] == L'\0'))
        {
            return E_INVALIDARG;
        }

        int delta = iQualifierValue - _wtoi(ppAutoPackageValues[i]);

        if ((delta >= 0) && (delta < bestMatchDelta))
        {
            bestMatchDelta = delta;
            indexOfBestMatch = static_cast<int>(i);
        }
    }

    if ((indexOfBestMatch >= 0) && ((indexOfBestMatch < numAutoPackageValues)))
    {
        StringResult package;
        RETURN_IF_FAILED(package.Init(ppAutoPackageValues[indexOfBestMatch]));
        return pAffinityOut->SetContentsFromOther(&package);
    }

    // Nothing in the AutoPackage list matches - goes in the main package.
    return pAffinityOut->SetRef(DefaultPackagingAffinity);
}

HRESULT ScaleQualifierType::Evaluate(_In_ const IQualifier* pAssetQualifier, _In_ PCWSTR pContextValue, _Out_ double* score) const
{
    *score = 0.0;

    double result = 0.0;
    StringResult assetQualifierValue;

    RETURN_IF_FAILED(ValidateQualifier(pAssetQualifier));
    RETURN_IF_FAILED(ValidateQualifierValue(pContextValue)); // downlevel provider can return illegal values

    if (DefString_IsEmpty(pContextValue))
    {
        // Empty provider value is valid but doesn't match anything
        return S_OK;
    }

    RETURN_IF_FAILED(pAssetQualifier->GetOperand2Literal(&assetQualifierValue));

    int contextValue = _wtoi(pContextValue);
    int assetValue = _wtoi(assetQualifierValue.GetRef());

    // same value => 1.0
    // (asset > context) && (asset <= context * 2) => 0.75..0.99
    // (asset < context) && (asset >= context / 2) => 0.50..0.74
    // (asset > context * 2) => 0.25..0.49
    // (asset < context / 2) => 0.01..0.24
    // cond < prov => 0.5
    int delta = assetValue - contextValue;

    if (assetValue == contextValue)
    {
        result = 1.0;
    }
    else if (assetValue > contextValue)
    {
        result = (delta <= contextValue) ? (1.00 - ComputeScoreWithinBucket(assetValue, contextValue, contextValue * 2, 0.25)) :
                                           (0.50 - ComputeScoreWithinBucket(assetValue, contextValue * 2, m_maxAllowedValue, 0.25));
    }
    else
    {
        // Per contract, scale always matches, so the bottom range starts at 0.01.
        result = (assetValue >= (contextValue / 2)) ?
                     (0.50 + ComputeScoreWithinBucket(assetValue, contextValue / 2, contextValue, 0.25)) :
                     (0.01 + ComputeScoreWithinBucket(assetValue, m_minAllowedValue, contextValue / 2, 0.23));
    }

    *score = result;

    return S_OK;
}

double ScaleQualifierType::CalculateScaleFactorScore(_In_ int assetValue, _In_ int contextValue)
{
    double result = 0.0;

    // same value => 1.0
    // (asset > context) && (asset <= context * 2) => 0.75..0.99
    // (asset < context) && (asset >= context / 2) => 0.50..0.74
    // (asset > context * 2) => 0.25..0.49
    // (asset < context / 2) => 0.01..0.24
    // cond < prov => 0.5
    int delta = assetValue - contextValue;

    if (assetValue == contextValue)
    {
        result = 1.0;
    }
    else if (assetValue > contextValue)
    {
        result = (delta <= contextValue) ?
                     (1.00 - ComputeScoreWithinBucket(assetValue, contextValue, contextValue * 2, 0.25)) :
                     (0.50 - ComputeScoreWithinBucket(assetValue, contextValue * 2, CoreEnvironment::Qualifier_Scale_Max_Value, 0.25));
    }
    else
    {
        // Per contract, scale always matches, so the bottom range starts at 0.01.
        result = (assetValue >= (contextValue / 2)) ?
                     (0.50 + ComputeScoreWithinBucket(assetValue, contextValue / 2, contextValue, 0.25)) :
                     (0.01 + ComputeScoreWithinBucket(assetValue, CoreEnvironment::Qualifier_Scale_Min_Value, contextValue / 2, 0.23));
    }

    return result;
}

double ScaleQualifierType::ComputeScoreWithinBucket(
    _In_ int value,
    _In_ int bucketMinValue,
    _In_ int bucketMaxValue,
    _In_ double bucketSize)
{
    return ((static_cast<double>(value - bucketMinValue)) / (static_cast<double>(bucketMaxValue - bucketMinValue))) * bucketSize;
}

HRESULT DXFeatureLevelQualifierType::CreateInstance(_Outptr_ DXFeatureLevelQualifierType** type)
{
    *type = nullptr;
    DXFeatureLevelQualifierType* pRtrn = new DXFeatureLevelQualifierType();
    RETURN_IF_NULL_ALLOC(pRtrn);

    *type = pRtrn;

    return S_OK;
}

HRESULT DXFeatureLevelQualifierType::Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pszProviderValue, _Out_ double* score) const
{
    *score = 0.0;

    double result = 0.0;
    StringResult qualifierValue;
    int providerLevel = -1;
    int qualifierLevel = -1;

    if (DefString_ICompare(pszProviderValue, CoreEnvironment::DXFeatureLevelValue_9) == Def_Equal)
    {
        providerLevel = 9;
    }
    else if (DefString_ICompare(pszProviderValue, CoreEnvironment::DXFeatureLevelValue_10) == Def_Equal)
    {
        providerLevel = 10;
    }
    else if (DefString_ICompare(pszProviderValue, CoreEnvironment::DXFeatureLevelValue_11) == Def_Equal)
    {
        providerLevel = 11;
    }
    else if (DefString_ICompare(pszProviderValue, CoreEnvironment::DXFeatureLevelValue_12) == Def_Equal)
    {
        providerLevel = 12;
    }

    if (SUCCEEDED(pQualifier->GetOperand2Literal(&qualifierValue)))
    {
        if (DefString_ICompare(qualifierValue.GetRef(), CoreEnvironment::DXFeatureLevelValue_9) == Def_Equal)
        {
            qualifierLevel = 9;
        }
        else if (DefString_ICompare(qualifierValue.GetRef(), CoreEnvironment::DXFeatureLevelValue_10) == Def_Equal)
        {
            qualifierLevel = 10;
        }
        else if (DefString_ICompare(qualifierValue.GetRef(), CoreEnvironment::DXFeatureLevelValue_11) == Def_Equal)
        {
            qualifierLevel = 11;
        }
        else if (DefString_ICompare(qualifierValue.GetRef(), CoreEnvironment::DXFeatureLevelValue_12) == Def_Equal)
        {
            qualifierLevel = 12;
        }
    }

    if ((providerLevel > 0) && (qualifierLevel > 0))
    {
        if (providerLevel == qualifierLevel)
        {
            result = 1.0;
        }
        else
        {
            switch (providerLevel)
            {
            case 9:
                // if the system is dx9, non-DX 9 assets never match
                break;
            case 10:
                if (qualifierLevel == 9)
                {
                    result = 0.75; // dx9 assets are sort-of okay for dx10
                }
                break;
            case 11:
                if (qualifierLevel == 9)
                {
                    result = 0.25;
                }
                else if (qualifierLevel == 10)
                {
                    result = 0.75;
                }
                break;
            case 12:
                if (qualifierLevel == 9)
                {
                    result = 0.25;
                }
                else if (qualifierLevel == 10)
                {
                    result = 0.5;
                }
                else if (qualifierLevel == 11)
                {
                    result = 0.75;
                }
            }
        }
    }

    *score = result;

    return S_OK;
}

HRESULT DeviceFamilyQualifierType::CreateInstance(_Outptr_ DeviceFamilyQualifierType** type)
{
    *type = nullptr;
    DeviceFamilyQualifierType* pRtrn = new DeviceFamilyQualifierType();
    RETURN_IF_NULL_ALLOC(pRtrn);

    *type = pRtrn;

    return S_OK;
}

HRESULT DeviceFamilyQualifierType::Evaluate(_In_ const IQualifier* pAssetQualifier, _In_ PCWSTR pContextValue, _Outptr_ double* score) const
{
    *score = 0.0;

    StringResult assetValue;
    double result = 0.0;

    if (SUCCEEDED(pAssetQualifier->GetOperand2Literal(&assetValue)))
    {
        if (DefString_IEqual(pContextValue, assetValue.GetRef()))
        {
            result = 1.0;
        }
        else if (DefString_IEqual(CoreEnvironment::DeviceFamilyValue_UniversalAppPlatform, assetValue.GetRef()))
        {
            // Universal assets are a match for any platform.
            result = 0.5;
        }
        else if (DefString_IEqual(CoreEnvironment::DeviceFamilyValue_Core, pContextValue))
        {
            // There are apps that only declare desktop assets but that can still run on Windows.Core devices.
            // To enable that scenario, allow desktop assets to be a partial match for core devices.
            if (DefString_IEqual(CoreEnvironment::DeviceFamilyValue_Desktop, assetValue.GetRef()))
            {
                result = 0.25;
            }
        }

        // NOTE: All others are considered a mismatch.
        // See pwszDeviceFamilyStrings in %SDXROOT%\minkernel\ntdll\devicefamily.c for a list of known device family strings.
    }

    *score = result;
    return S_OK;
}

HRESULT
CoreEnvironment::GetDefaultQualifierType(_In_ CoreEnvironment::QualifierTypeIndex qualifierTypeIndex, _Out_ IBuildQualifierType** ppTypeOut)
{
    *ppTypeOut = nullptr;

    // Currently no core implementation of language list or region
    switch (qualifierTypeIndex)
    {
    case CoreEnvironment::QualifierTypeIndex::LanguageList:
    case CoreEnvironment::QualifierTypeIndex::RegionId:
        return E_NOTIMPL;
    case CoreEnvironment::QualifierTypeIndex::Contrast:
        return ContrastQualifierType::CreateInstance((ContrastQualifierType**)ppTypeOut);
    case CoreEnvironment::QualifierTypeIndex::Scale:
        return ScaleQualifierType::CreateInstance((ScaleQualifierType**)ppTypeOut);
    case CoreEnvironment::QualifierTypeIndex::TargetSize:
        return IntegerQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_TargetSize_Min_Value,
            CoreEnvironment::Qualifier_TargetSize_Max_Value,
            true,
            (IntegerQualifierType**)ppTypeOut);
    case CoreEnvironment::QualifierTypeIndex::LayoutDirection:
        return EnumerationQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_LayoutDirection_AllowedValues,
            CoreEnvironment::Qualifier_LayoutDirection_NumAllowedValues,
            (EnumerationQualifierType**)ppTypeOut);
    case CoreEnvironment::QualifierTypeIndex::Theme:
        return EnumerationQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_Theme_AllowedValues,
            CoreEnvironment::Qualifier_Theme_NumAllowedValues,
            (EnumerationQualifierType**)ppTypeOut);
    case CoreEnvironment::QualifierTypeIndex::Configuration:
        return StringIdentifierQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_Configuration_Max_Length,
            QualifierTypeBase::RequiredValueQualifierTypeFlags,
            (StringIdentifierQualifierType**)ppTypeOut);
    case CoreEnvironment::QualifierTypeIndex::AlternateForm:
        return StringIdentifierQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_AlternateForm_Max_Length,
            QualifierTypeBase::OptionalValueQualifierTypeFlags,
            (StringIdentifierQualifierType**)ppTypeOut);
    case CoreEnvironment::QualifierTypeIndex::DXFeatureLevel:
        return DXFeatureLevelQualifierType::CreateInstance((DXFeatureLevelQualifierType**)ppTypeOut);
    case CoreEnvironment::QualifierTypeIndex::DeviceFamily:
        return DeviceFamilyQualifierType::CreateInstance((DeviceFamilyQualifierType**)ppTypeOut);
    case CoreEnvironment::QualifierTypeIndex::CustomQualifier:
        return StringIdentifierQualifierType::CreateInstance(
            CoreEnvironment::Qualifier_Custom_MaxLength,
            QualifierTypeBase::OptionalListQualifierTypeFlags,
            (StringIdentifierQualifierType**)ppTypeOut);
    }

    return E_MRM_BAD_NAME;
}

} // namespace Microsoft::Resources
