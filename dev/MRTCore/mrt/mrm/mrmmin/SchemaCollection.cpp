// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"

namespace Microsoft::Resources
{

HRESULT SchemaCollectionSchemaWrapper::CreateInstance(
    _In_ const IHierarchicalSchema* schema,
    _In_ bool assumeOwnership,
    _Outptr_ SchemaCollectionSchemaWrapper** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, schema);

    SchemaCollectionSchemaWrapper* rtrn = new SchemaCollectionSchemaWrapper(schema, assumeOwnership);
    RETURN_IF_NULL_ALLOC(rtrn);

    *result = rtrn;

    return S_OK;
}

HRESULT
SchemaCollectionSchemaWrapper::CreateInstance(_In_ const IHierarchicalSchema* schema, _Outptr_ SchemaCollectionSchemaWrapper** result)
{
    return CreateInstance(schema, false, result);
}

SchemaCollectionSchemaWrapper::~SchemaCollectionSchemaWrapper() { delete m_mySchema; }

HRESULT SchemaCollectionSchemaWrapper::GetSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;

    // We have exactly one schema, so index 0 is our schema and anything else is out of range.
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), index != 0);

    *result = m_schema;
    return S_OK;
}

HRESULT SchemaCollectionSchemaWrapper::GetSchemaById(_In_ PCWSTR schemaId, _Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(schemaId));

    if ((m_schema != nullptr) && DefString_IEqual(m_schema->GetSimpleId(), schemaId))
    {
        *result = m_schema;
    }

    return S_OK;
}

HRESULT SchemaCollectionSchemaWrapper::FindSchema(
    _In_ const HierarchicalSchemaReference* wantRef,
    _Outptr_ const IHierarchicalSchema** matchingSchema) const
{
    if ((m_schema != nullptr) && wantRef->CheckIsCompatible(m_schema))
    {
        *matchingSchema = m_schema;
        return S_OK;
    }

    *matchingSchema = nullptr;
    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

SchemaCollectionSchemaWrapper::SchemaCollectionSchemaWrapper(_In_ const IHierarchicalSchema* schema, _In_ bool assumeOwnership) :
    m_mySchema(assumeOwnership ? schema : nullptr), m_schema(schema)
{}

} // namespace Microsoft::Resources
