// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources
{

const PCWSTR IBuildQualifierType::DefaultPackagingAffinity = L"default";

template<typename Func>
HRESULT ProcessQualifierValueList(_In_ PCWSTR valueFromProvider, _In_ Func process)
{
    unsigned positionInList = 0;
    StringResult valueList;
    StringResult value;
    size_t pos = 0;
    HRESULT hr = S_OK;

    RETURN_IF_FAILED(value.SetRef(valueFromProvider));

    if (value.TryFindFirstOf(L';', &pos))
    {
        // It's a list.  Walk it to make sure all values are valid.
        // 'value' points to individual values, valueList holds
        // the whole list.
        RETURN_IF_FAILED(valueList.SetRef(valueFromProvider));

        // GetWritableRef will make a copy for us and return a pointer.
        size_t charsLeft = 0;
        PWSTR buf;
        bool last = false;

        RETURN_IF_FAILED(valueList.GetWritableRef(&buf, &charsLeft));

        // skip any leading whitespace
        while ((*buf != L'\0') && (charsLeft > 0) && iswspace(*buf))
        {
            buf++;
            charsLeft--;
        }

        RETURN_IF_FAILED(value.SetRef(buf));

        while (!last)
        {
            if (pos < charsLeft)
            {
                buf[pos] = L'\0';

                if (!process(positionInList++, value.GetRef(), &hr))
                {
                    return hr;
                }

                buf += pos + 1;
                charsLeft -= pos + 1;
                RETURN_IF_FAILED(value.SetRef(buf));

                last = !value.TryFindFirstOf(L';', &pos);
            }
            else
            {
                last = true;
            }
        }
    }

    if (!process(positionInList++, value.GetRef(), &hr))
    {
        return hr;
    }

    return S_OK;
}

HRESULT
QualifierTypeBase::ValidateQualifierValue(_In_ PCWSTR qualifierValue) const
{
    auto testSingle = [&](unsigned position, PCWSTR singleValue, HRESULT* hr) {
        *hr = S_OK;
        if (position >= GetMaxQualifierEntries())
        {
            *hr = HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
            return false;
        }

        if ((position > 0) && (!AreListValuesAllowed()))
        {
            *hr = HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
            return false;
        }

        if (DefString_IsEmpty(singleValue) && (!AreEmptyValuesAllowed()))
        {
            *hr = HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
            return false;
        }
        *hr = ValidateSingleQualifierValue(singleValue);
        return (SUCCEEDED(*hr));
    };

    return ProcessQualifierValueList(qualifierValue, testSingle);
}

HRESULT
QualifierTypeBase::ValidateOrMakeCompatibleQualifierValue(_In_ PCWSTR qualifierValue, _Inout_ StringResult* compatibleValue) const
{
    RETURN_IF_FAILED(compatibleValue->SetRef(L""));

    auto testSingle = [&](unsigned position, PCWSTR singleValue, HRESULT* hr) {
        *hr = S_OK;
        if (position >= GetMaxQualifierEntries())
        {
            *hr = HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
            return false;
        }

        // we don't know how to modify values in a list, so if we have a correction and > 1
        // element we have to bail.
        if ((position > 0) && ((!AreListValuesAllowed()) || (!compatibleValue->IsEmpty())))
        {
            *hr = HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
            return false;
        }

        if (DefString_IsEmpty(singleValue) && (!AreEmptyValuesAllowed()))
        {
            *hr = HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
            return false;
        }

        *hr = ValidateOrMakeCompatibleSingleQualifierValue(singleValue, compatibleValue);

        return (SUCCEEDED(*hr)) && ((position == 0) || compatibleValue->IsEmpty());
    };

    return ProcessQualifierValueList(qualifierValue, testSingle);
}

HRESULT
QualifierTypeBase::ValidateOrMakeCompatibleSingleQualifierValue(_In_ PCWSTR value, _Inout_ StringResult* compatibleValue) const
{
    // default implementation can't force compatibility
    RETURN_IF_FAILED(compatibleValue->SetRef(nullptr));
    return ValidateQualifierValue(value);
}

HRESULT
QualifierTypeBase::ValidateQualifier(_In_ const IQualifier* pQualifier) const
{
    ICondition::ConditionOperator op;
    Atom qualifier;
    StringResult value;

    RETURN_IF_FAILED(pQualifier->GetOperator(&op));
    RETURN_IF_FAILED(pQualifier->GetOperand1Qualifier(&qualifier));
    RETURN_IF_FAILED(pQualifier->GetOperand2Literal(&value));
    RETURN_IF_FAILED(ValidateQualifierComparison(qualifier, op, value.GetRef()));

    return S_OK;
}

HRESULT
QualifierTypeBase::ValidateQualifierComparison(
    _In_ Atom /*qualifierName*/,
    _In_ ICondition::ConditionOperator op,
    _In_ PCWSTR pQualifierValue) const
{
    if (op != ICondition::MatchOp)
    {
        RETURN_HR(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_OPERATOR));
    }

    return ValidateSingleQualifierValue(pQualifierValue);
}

HRESULT
QualifierTypeBase::Evaluate(_In_ const IQualifier* qualifierOnAsset, _In_ PCWSTR valueFromProvider, _Out_ double* score) const
{
    *score = 0.0;

    StringResult valueOnAsset;
    RETURN_IF_FAILED(qualifierOnAsset->GetOperand2Literal(&valueOnAsset));

    if (AreListValuesAllowed())
    {
        double localScore = 0.0;
        auto evaluateSingle = [&](unsigned position, PCWSTR singleValue, HRESULT* hr) {
            *hr = S_OK;
            double singleItemScore = EvaluateSingleQualifierValue(valueOnAsset.GetRef(), singleValue);
            if (singleItemScore > 0.0)
            {
                localScore = ScoreInPosition(position, singleItemScore);
            }

            // Stop if we find a matching value (score > 0) or
            // hit an error.  Otherwise continue.
            return (localScore == 0.0);
        };

        RETURN_IF_FAILED(ProcessQualifierValueList(valueFromProvider, evaluateSingle));
        *score = localScore;
        return S_OK;
    }

    *score = EvaluateSingleQualifierValue(valueOnAsset.GetRef(), valueFromProvider);
    return S_OK;
}

double QualifierTypeBase::EvaluateSingleQualifierValue(_In_ PCWSTR valueOnAsset, _In_ PCWSTR valueFromProvider) const
{
    double result = 0.0;

    // same value => 1.0, others => 0.0
    if (DefString_ICompare(valueOnAsset, valueFromProvider) == Def_Equal)
    {
        result = 1.0;
    }

    return result;
}

HRESULT
QualifierTypeBase::Compare(_In_ const IQualifier* pQualifier1, _In_ const IQualifier* pQualifier2, _Out_ DEFCOMPARISON* result) const
{
    *result = Def_CompareError;

    DEFCOMPARISON rtrn = IQualifier::Compare(pQualifier1, pQualifier2);
    if (rtrn == Def_Equal)
    {
        RETURN_IF_FAILED(InnerCompare(pQualifier1, pQualifier2, &rtrn));
    }

    *result = rtrn;
    return S_OK;
}

HRESULT
QualifierTypeBase::CompareForValue(
    _In_ const IQualifier* pQualifier1,
    _In_ const IQualifier* pQualifier2,
    _In_ PCWSTR /* pValue */,
    _Out_ DEFCOMPARISON* result) const
{
    return Compare(pQualifier1, pQualifier2, result);
}

HRESULT
QualifierTypeBase::InnerCompare(_In_ const IQualifier* pQualifier1, _In_ const IQualifier* pQualifier2, _Out_ DEFCOMPARISON* result) const
{
    *result = Def_Equal;

    StringResult str1;
    StringResult str2;
    if (FAILED(pQualifier1->GetOperand2Literal(&str1)) || FAILED(pQualifier2->GetOperand2Literal(&str2)))
    {
        return S_OK;
    }

    RETURN_IF_FAILED(str1.CompareWithOptions(&str2, DefCompare_CaseInsensitive, result));

    return S_OK;
}

_Success_(return ) bool QualifierTypeBase::IsValidValue(_In_ PCWSTR pValue, _In_ QualifierFormat format, _In_ bool bAllowList)
{
    if (DefString_IsEmpty(pValue))
    {
        return false;
    }

    PCWSTR pTest = pValue;

    switch (format)
    {
    case QualifierTypeBase::StringQualifier:
        while (*pTest != L'\0')
        {
            if ((!iswalnum(*pTest) && (*pTest != L'-')))
            {
                if ((!bAllowList) || (*pValue != L';'))
                {
                    return false;
                }
            }
            pTest++;
        }
        break;
    case QualifierTypeBase::NumericQualifier:
        while (*pTest != L'\0')
        {
            if (!iswdigit(*pTest))
            {
                if ((!bAllowList) || (*pValue != L';'))
                {
                    return false;
                }
            }
            pTest++;
        }
        break;
    }

    return true;
}

IBuildQualifierType::PackagingFlags QualifierTypeBase::GetDefaultPackagingFlags() const
{
    return IBuildQualifierType::PackagingDefaultFlags;
}

int QualifierTypeBase::GetMaxQualifierEntries() const { return MaxItemsInList; }

HRESULT
QualifierTypeBase::GetPackagingInfo(
    _In_ const IQualifier* pQualifier,
    _In_ UINT32 buildConfiguration,
    _In_reads_(numAutoPackageValues) PCWSTR* const ppAutoPackageValues,
    _In_ size_t const numAutoPackageValues,
    _Out_ IBuildQualifierType::PackagingFlags* pFlagsOut,
    _Inout_ StringResult* pAffinityOut) const
{
    *pFlagsOut = GetDefaultPackagingFlags();
    double fallbackScore;
    RETURN_IF_FAILED(pQualifier->GetFallbackScore(&fallbackScore));

    // With granular splitting the qualifier never goes into the default package.
    if (((buildConfiguration & MrmBuildConfiguration::UseGranularResourceSplittingFlag) == 0) &&
        ((fallbackScore == 1.0) || ((fallbackScore > 0.0) && ((*pFlagsOut & PackagingFlags::PackagingFallbackHandlingMask) ==
                                                              PackagingFlags::PackagingAllFallbackToMainPackage))))
    {
        return pAffinityOut->SetRef(DefaultPackagingAffinity);
    }

    // If no autoPackage list, use previous method.
    if (ppAutoPackageValues == nullptr || numAutoPackageValues == 0)
    {
        return pQualifier->GetOperand2Literal(pAffinityOut);
    }

    // Compare qualifier value to the list of auto packages, a match goes in to that package.
    // No match = goes in the main package.

    StringResult qualifierValue;
    RETURN_IF_FAILED(pQualifier->GetOperand2Literal(&qualifierValue));

    for (size_t i = 0; i < numAutoPackageValues; i++)
    {
        if ((ppAutoPackageValues[i] == nullptr) || (ppAutoPackageValues[i][0] == L'\0'))
        {
            RETURN_HR(E_INVALIDARG);
        }

        DEFCOMPARISON result;
        RETURN_IF_FAILED(qualifierValue.CompareWithOptions(ppAutoPackageValues[i], DEFCOMPAREOPTIONS::DefCompare_CaseInsensitive, &result));

        if (result == DEFCOMPARISON::Def_Equal)
        {
            return pAffinityOut->SetContentsFromOther(&qualifierValue);
        }
    }

    // Nothing in the AutoPackage list matches, goes in the main package.
    return pAffinityOut->SetRef(DefaultPackagingAffinity);
}

// StringQualifierType implementation
_Pre_satisfies_(maxAllowedLength > 0) HRESULT StringIdentifierQualifierType::CreateInstance(
    _In_ size_t maxAllowedLength,
    _In_ QualifierTypeFlags flags,
    _Outptr_ StringIdentifierQualifierType** type)
{
    *type = nullptr;
    StringIdentifierQualifierType* pRtrn = new StringIdentifierQualifierType(maxAllowedLength, flags);
    RETURN_IF_NULL_ALLOC(pRtrn);

    *type = pRtrn;

    return S_OK;
}

HRESULT
StringIdentifierQualifierType::ValidateSingleQualifierValue(_In_ PCWSTR pValue) const
{
    if (DefString_IsEmpty(pValue))
    {
        if (AreEmptyValuesAllowed())
        {
            return S_OK;
        }
    }
    else if (IsValidStringIdentifier(pValue, m_maxAllowedLength))
    {
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
}

bool StringIdentifierQualifierType::IsValidStringIdentifier(_In_ PCWSTR pValue, _In_ size_t maxSize)
{
    PCWSTR pTest = pValue;

    while (*pTest != L'\0')
    {
        // don't overrun
        if ((pTest - pValue) >= maxSize)
        {
            return false;
        }

        // Identifier can contain alphanumeric, dash or underscore
        if ((!iswalnum(*pTest)) && (*pTest != L'-') && (*pTest != L'_'))
        {
            return false;
        }

        pTest++;
    }

    return true;
}

// EnumerationQualifierType

HRESULT
EnumerationQualifierType::CreateInstance(
    _In_reads_(numAllowedValues) const PCWSTR* pAllowedValues,
    _In_ size_t numAllowedValues,
    _Outptr_ EnumerationQualifierType** type)
{
    *type = nullptr;
    EnumerationQualifierType* pRtrn = new EnumerationQualifierType(pAllowedValues, numAllowedValues);
    RETURN_IF_NULL_ALLOC(pRtrn);

    *type = pRtrn;
    return S_OK;
}

HRESULT
EnumerationQualifierType::ValidateSingleQualifierValue(_In_ PCWSTR pValue) const
{
    if (!DefString_IsEmpty(pValue))
    {
        for (int i = 0; i < m_numAllowedValues; i++)
        {
            if (DefString_ICompare(pValue, m_pAllowedValues[i]) == Def_Equal)
            {
                return S_OK;
            }
        }
    }

    return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
}

HRESULT
EnumerationQualifierType::Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pszProviderValue, _Out_ double* score) const
{
    *score = 0.0;

    RETURN_IF_FAILED(ValidateQualifier(pQualifier));
    RETURN_IF_FAILED(ValidateQualifierValue(pszProviderValue)); // downlevel provider can return illegal values

    StringResult qualifierValue;
    RETURN_IF_FAILED(pQualifier->GetOperand2Literal(&qualifierValue));

    PCWSTR pszQualifierValue = qualifierValue.GetRef();

    // same value => 1.0
    // others => 0.0
    if (DefString_ICompare(pszProviderValue, pszQualifierValue) == Def_Equal)
    {
        *score = 1.0;
    }
    else
    {
        *score = 0.0;
    }

    return S_OK;
}

_Pre_satisfies_(maxAllowedValue > minAllowedValue) HRESULT IntegerQualifierType::CreateInstance(
    _In_ int minAllowedValue,
    _In_ int maxAllowedValue,
    _In_ bool allowEmptyProviderValue,
    _Outptr_ IntegerQualifierType** type)
{
    *type = nullptr;
    IntegerQualifierType* pRtrn = new IntegerQualifierType(minAllowedValue, maxAllowedValue, allowEmptyProviderValue);
    RETURN_IF_NULL_ALLOC(pRtrn);

    *type = pRtrn;
    return S_OK;
}

HRESULT
IntegerQualifierType::ValidateSingleQualifierValue(_In_ PCWSTR pValue) const
{
    PCWSTR pTest = pValue;

    if (!DefString_IsEmpty(pValue))
    {
        while (*pTest != L'\0')
        {
            if (!iswdigit(*pTest))
            {
                RETURN_HR(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE));
            }
            pTest++;
        }

        int value = _wtoi(pValue);
        if ((value >= m_minAllowedValue) && (value <= m_maxAllowedValue))
        {
            return S_OK;
        }
    }
    else if (m_allowEmptyProviderValue)
    {
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
}

HRESULT
IntegerQualifierType::Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pszProviderValue, _Out_ double* score) const
{
    *score = 0.0;

    RETURN_IF_FAILED(ValidateQualifier(pQualifier));
    RETURN_HR_IF_EXPECTED(S_OK, DefString_IsEmpty(pszProviderValue)); // Empty provider value is valid but doesn't match anything
    RETURN_IF_FAILED(ValidateQualifierValue(pszProviderValue)); // downlevel provider can return illegal values

    StringResult qualifierValue;
    RETURN_IF_FAILED(pQualifier->GetOperand2Literal(&qualifierValue));

    int providerValue = _wtoi(pszProviderValue);
    int qualiferValue = _wtoi(qualifierValue.GetRef());

    // same value => 1.0
    // cond > prov => 0.75
    // cond < prov => 0.5
    int comparisonResult = providerValue - qualiferValue;

    if (comparisonResult == 0)
    {
        *score = 1.0;
    }
    else if (comparisonResult > 0)
    {
        *score = 0.5;
    }
    else
    {
        *score = 0.75;
    }

    return S_OK;
}

HRESULT
IntegerQualifierType::InnerCompare(_In_ const IQualifier* pQualifier1, _In_ const IQualifier* pQualifier2, _Out_ DEFCOMPARISON* result)
    const
{
    *result = Def_CompareError;
    // how do we sort when all else is equal?
    // Suggestion:  From largest to smallest
    StringResult qualifierValue1;
    StringResult qualifierValue2;

    RETURN_IF_FAILED(pQualifier1->GetOperand2Literal(&qualifierValue1));
    RETURN_IF_FAILED(pQualifier2->GetOperand2Literal(&qualifierValue2));

    int qv1 = _wtoi(qualifierValue1.GetRef());
    int qv2 = _wtoi(qualifierValue2.GetRef());
    int diff = qv1 - qv2;

    if (diff > 0)
    {
        *result = Def_Greater;
    }
    else if (diff < 0)
    {
        *result = Def_Less;
    }
    else
    {
        RETURN_IF_FAILED(QualifierTypeBase::InnerCompare(pQualifier1, pQualifier2, result));
    }

    return S_OK;
}

HRESULT
IntegerQualifierType::CompareForValue(
    _In_ const IQualifier* pQualifier1,
    _In_ const IQualifier* pQualifier2,
    _In_ PCWSTR pValue,
    _Out_ DEFCOMPARISON* result) const
{
    *result = Def_CompareError;

    StringResult qualifierValue1;
    StringResult qualifierValue2;

    RETURN_IF_FAILED(pQualifier1->GetOperand2Literal(&qualifierValue1));
    RETURN_IF_FAILED(pQualifier2->GetOperand2Literal(&qualifierValue2));

    int pv = _wtoi(pValue);
    int qv1 = _wtoi(qualifierValue1.GetRef());
    int qv2 = _wtoi(qualifierValue2.GetRef());

    // If (pv < min(qv1, qv2)) the smaller value wins,
    // otherwise the larger value wins
    if (qv1 > qv2)
    {
        *result = ((pv > qv2) ? Def_Greater : Def_Less);
    }
    else if (qv2 > qv1)
    {
        *result = ((pv > qv1) ? Def_Less : Def_Greater);
    }
    else
    {
        *result = Def_Equal;
    }

    return S_OK;
}

} // namespace Microsoft::Resources