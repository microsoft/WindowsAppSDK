// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"

namespace Microsoft::Resources::Build
{

HRESULT SectionCopierFactory::Create(
    __in DEFFILE_SECTION_TYPEID sectionTypeId,
    __in const IFileSection* const pFileSection,
    __in RemapInfo* pRemap,
    _Outptr_ SectionCopier** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pFileSection == nullptr) || (pRemap == nullptr));

    if (BaseFile::SectionTypesEqual(sectionTypeId, gAtomPoolSectionType))
    {
        return FileAtomPoolCopier::CreateInstance(pFileSection, pRemap, (FileAtomPoolCopier**)result);
    }

    return E_INVALIDARG;
}

} // namespace Microsoft::Resources::Build