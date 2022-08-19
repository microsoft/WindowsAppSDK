// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources
{

bool QualifierValueProviderBase::IsPersistentQualifier() const
{
    // Persistent qualifiers should inherit this class and override this method.
    return false;
}

bool QualifierValueProviderBase::AllowPersistentEmptyStringValue() const
{
    // For most qualifiers we don't want to allow the application to set a persistent value of an empty string.
    return false;
}

HRESULT
QualifierValueProviderBase::SetPersistentQualifierValue(
    _In_ PCWSTR /*qualifierName*/,
    _In_ PCWSTR qualifierValue,
    _Inout_opt_ const IProviderDataSources* /*dataSources*/) const
{
    if (m_profile == nullptr || !IsPersistentQualifier())
    {
        return HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    }

    StringResult existingValue;
    bool haveNewValue = (DefString_IsEmpty(qualifierValue) == FALSE);
    bool haveExistingValue = m_profile->TryGetApplicationSetting(m_subKeyName.GetRef(), m_qualifierKeyName.GetRef(), &existingValue) &&
                             (!existingValue.IsEmpty());

    if ((haveExistingValue != haveNewValue) ||
        (haveExistingValue && (DefString_ICompare(existingValue.GetRef(), qualifierValue) != Def_Equal)))
    {
        // New value - update and notify
        RETURN_IF_FAILED(m_profile->SetApplicationSetting(m_subKeyName.GetRef(), m_qualifierKeyName.GetRef(), qualifierValue));

        StringResult packageName;
        RETURN_IF_FAILED(m_profile->GetPackageInfo(0, &packageName, nullptr, nullptr));
    }

    return S_OK;
}

HRESULT
QualifierValueProviderBase::GetQualifierValue(_In_ Atom attr, _Inout_ const IProviderDataSources* pData, _Inout_ StringResult* pResultOut)
    const
{
    if (m_profile != nullptr && IsPersistentQualifier())
    {
        // Attempting to get a persistent override value is best effort
        if (m_profile->TryGetApplicationSetting(m_subKeyName.GetRef(), m_qualifierKeyName.GetRef(), pResultOut))
        {
            if (!pResultOut->IsEmpty() || AllowPersistentEmptyStringValue())
            {
                // Only return S_OK if we were able to get a persisted value. (Otherwise we want to fall back and call the *Inner method).
                return S_OK;
            }
        }
    }

    return GetQualifierValueInner(attr, pData, pResultOut);
}

HRESULT
GenericQVProvider::CreateInstance(_In_ PCWSTR pValue, _Outptr_ GenericQVProvider** provider)
{
    *provider = nullptr;
    AutoDeletePtr<GenericQVProvider> pRtrn = new GenericQVProvider();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->m_value.SetCopy(pValue));
    *provider = pRtrn.Detach();

    return S_OK;
}

GenericQVProvider::~GenericQVProvider() {}

HRESULT GenericQVProvider::GetQualifierValueInner(
    _In_ Atom /*attr*/,
    _Inout_ const IProviderDataSources* /*pData*/,
    _Inout_ StringResult* pResultOut) const
{
    RETURN_IF_FAILED(pResultOut->SetCopy(m_value.GetRef()));

    return S_OK;
}

HRESULT
WindowsDisplayLanguageProvider::CreateInstance(
    _In_ const CoreProfile* profile,
    _In_ PCWSTR subKeyName,
    _In_ PCWSTR qualifierKeyName,
    _Outptr_ WindowsDisplayLanguageProvider** result)
{
    *result = nullptr;

    AutoDeletePtr<WindowsDisplayLanguageProvider> pRtrn = new WindowsDisplayLanguageProvider();
    RETURN_IF_NULL_ALLOC(pRtrn);

    pRtrn->m_profile = profile;

    RETURN_IF_FAILED(pRtrn->m_subKeyName.SetCopy(subKeyName));
    RETURN_IF_FAILED(pRtrn->m_qualifierKeyName.SetCopy(qualifierKeyName));

    *result = pRtrn.Detach();

    return S_OK;
}

WindowsDisplayLanguageProvider::WindowsDisplayLanguageProvider() {}

bool WindowsDisplayLanguageProvider::IsPersistentQualifier() const { return true; }

HRESULT
WindowsDisplayLanguageProvider::GetQualifierValueInner(
    _In_ Atom /*attr*/,
    _Inout_ const IProviderDataSources* /*pData*/,
    _Inout_ StringResult* pResultOut) const
{
    ULONG ulNumLanguages;
    wchar_t wszLanguageBuffer[LOCALE_NAME_MAX_LENGTH + 1] = {};
    PWSTR pszLanguageBuffer = wszLanguageBuffer;
    ULONG cchLanguageBuffer = _countof(wszLanguageBuffer);
    unique_deffree_ptr<WCHAR> allocatedBuffer;
    if (!::GetThreadPreferredUILanguages(MUI_LANGUAGE_NAME | MUI_UI_FALLBACK, &ulNumLanguages, pszLanguageBuffer, &cchLanguageBuffer))
    {
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            pszLanguageBuffer = _DefArray_AllocZeroed(wchar_t, cchLanguageBuffer);
            RETURN_IF_NULL_ALLOC(pszLanguageBuffer);

            allocatedBuffer.reset(pszLanguageBuffer);
            RETURN_IF_WIN32_BOOL_FALSE(::GetThreadPreferredUILanguages(
                MUI_LANGUAGE_NAME | MUI_UI_FALLBACK, &ulNumLanguages, pszLanguageBuffer, &cchLanguageBuffer));
        }
        else
        {
            RETURN_HR(HRESULT_FROM_WIN32(GetLastError()));
        }
    }

    DEF_ASSERT(cchLanguageBuffer >= 3);
    __analysis_assume(cchLanguageBuffer >= 3 && (cchLanguageBuffer < (LOCALE_NAME_MAX_LENGTH + 1)));
    // Adjust to last chars of the language list
    cchLanguageBuffer -= 2; // Remove last double null-terms
    cchLanguageBuffer--; // Count become index

    while (cchLanguageBuffer != 0)
    {
        if (pszLanguageBuffer[cchLanguageBuffer] == L'\0')
        {
            pszLanguageBuffer[cchLanguageBuffer] = L';';
        }
        cchLanguageBuffer--;
    }

    RETURN_IF_FAILED(pResultOut->SetCopy(pszLanguageBuffer));

    return S_OK;
}

} // namespace Microsoft::Resources
