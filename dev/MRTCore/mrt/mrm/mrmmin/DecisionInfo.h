// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace Microsoft::Resources
{

class IRawDecisionInfo : public DefObject
{
public:
    virtual ~IRawDecisionInfo() {}

    virtual const IDecisionInfo* GetPool() const = 0;

    virtual const RemapAtomPool* GetQualifierMapping() const = 0;

    virtual int GetNumBaseQualifiers() const = 0;
    virtual int GetNumQualifiers() const = 0;
    virtual int GetNumQualifierSets() const = 0;
    virtual int GetNumDecisions() const = 0;
    virtual int GetNumReferences() const = 0;
    virtual UINT32 GetLiteralsSizeInChars() const = 0;

    bool IsValidBaseQualifierIndex(int i) const { return (i >= 0) && (i < GetNumBaseQualifiers()); }
    bool IsValidQualifierIndex(int i) const { return (i >= 0) && (i < GetNumQualifiers()); }
    bool IsValidQualifierSetIndex(int i) const { return (i >= 0) && (i < GetNumQualifierSets()); }
    bool IsValidDecisionIndex(int i) const { return (i >= 0) && (i < GetNumDecisions()); }
    bool IsValidReferenceIndex(int i) const { return (i >= 0) && (i < GetNumReferences()); }
    bool IsValidLiteralOffset(int offset) const { return (offset >= 0) && (offset < GetLiteralsSizeInChars()); }

    virtual HRESULT GetBaseQualifier(_In_ int index, _Out_ MRMFILE_BASE_QUALIFIER* ppQualiferOut) const = 0;
    virtual HRESULT GetQualifier(_In_ int index, _Out_ MRMFILE_QUALIFIER* ppQualifierOut) const = 0;
    virtual HRESULT GetQualifierSet(_In_ int index, _Out_ MRMFILE_QUALIFIER_SET* ppQualifierSetOut) const = 0;
    virtual HRESULT GetDecision(_In_ int index, _Out_ MRMFILE_DECISION* ppDecisionOut) const = 0;
    virtual HRESULT GetReference(_In_ int index, _Out_ UINT16* ppReferenceOut) const = 0;
    virtual HRESULT GetLiteral(_In_ int offset, _Inout_ StringResult* pLiteralOut) const = 0;

    virtual HRESULT GetDecisionNumQualifierSets(_In_ int index, _Out_ int* pNumSetsOut) const = 0;

protected:
    IRawDecisionInfo() {}
};

} // namespace Microsoft::Resources