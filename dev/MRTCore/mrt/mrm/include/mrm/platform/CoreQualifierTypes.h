// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Microsoft::Resources
{

class ContrastQualifierType : public EnumerationQualifierType
{
public:
    static HRESULT CreateInstance(_Outptr_ ContrastQualifierType** type);

    virtual ~ContrastQualifierType() {}

    HRESULT Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pValue, _Out_ double* score) const;

protected:
    ContrastQualifierType() :
        EnumerationQualifierType(CoreEnvironment::Qualifier_Contrast_AllowedValues, CoreEnvironment::Qualifier_Contrast_NumAllowedValues)
    {}
};

class ScaleQualifierType : public IntegerQualifierType
{
public:
    static HRESULT CreateInstance(_Outptr_ ScaleQualifierType** type);

    virtual ~ScaleQualifierType() {}

    inline IBuildQualifierType::PackagingFlags GetDefaultPackagingFlags() const
    {
        return IBuildQualifierType::PackagingAllowResourcePackage | IBuildQualifierType::PackagingReportQualifier;
    }

    virtual HRESULT GetPackagingInfo(
        _In_ const IQualifier* pQualifier,
        _In_ UINT32 buildConfiguration,
        _In_reads_(numAutoPackageValues) PCWSTR* ppAutoPackageValues,
        _In_ size_t numAutoPackageValues,
        _Out_ IBuildQualifierType::PackagingFlags* pFlagsOut,
        _Inout_ StringResult* pAffinityOut) const;

    virtual HRESULT Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pValue, _Out_ double* score) const;

    static double CalculateScaleFactorScore(_In_ int assetValue, _In_ int contextValue);

protected:
    static double ComputeScoreWithinBucket(_In_ int value, _In_ int bucketMinValue, _In_ int bucketMaxValue, _In_ double bucketSize);

    ScaleQualifierType() :
        IntegerQualifierType(CoreEnvironment::Qualifier_Scale_Min_Value, CoreEnvironment::Qualifier_Scale_Max_Value, false)
    {}
};

class DXFeatureLevelQualifierType : public EnumerationQualifierType
{
public:
    static HRESULT CreateInstance(_Outptr_ DXFeatureLevelQualifierType** type);

    virtual ~DXFeatureLevelQualifierType() {}

    HRESULT Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pValue, _Out_ double* score) const;

    inline IBuildQualifierType::PackagingFlags GetDefaultPackagingFlags() const
    {
        return IBuildQualifierType::PackagingAllowResourcePackage | IBuildQualifierType::PackagingReportQualifier;
    }

protected:
    DXFeatureLevelQualifierType() :
        EnumerationQualifierType(
            CoreEnvironment::Qualifier_DXFeatureLevel_AllowedValues,
            CoreEnvironment::Qualifier_DXFeatureLevel_NumAllowedValues)
    {}
};

class DeviceFamilyQualifierType : public StringIdentifierQualifierType
{
public:
    static HRESULT CreateInstance(_Outptr_ DeviceFamilyQualifierType** type);

    virtual ~DeviceFamilyQualifierType() {}

    virtual HRESULT Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pValue, _Out_ double* score) const;

protected:
    DeviceFamilyQualifierType() :
        StringIdentifierQualifierType(CoreEnvironment::Qualifier_DeviceFamily_MaxLength, RequiredValueQualifierTypeFlags)
    {}
};

} // namespace Microsoft::Resources