// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <activationregistration.h>
#include <cor.h>
#include <xmllite.h>

HRESULT LoadManifestFromPath(std::wstring path);

HRESULT LoadFromSxSManifest(PCWSTR path);

HRESULT LoadFromEmbeddedManifest(PCWSTR path);

HRESULT WinRTLoadComponentFromFilePath(PCWSTR manifestPath);

HRESULT WinRTLoadComponentFromString(std::string_view xmlStringValue);

HRESULT ParseRootManifestFromXmlReaderInput(IUnknown* pInput);

HRESULT ParseFileTag(IXmlReader* xmlReader);

HRESULT ParseActivatableClassTag(IXmlReader* xmlReader, PCWSTR fileName);

HRESULT WinRTGetThreadingModel(
    HSTRING activatableClassId,
    ABI::Windows::Foundation::ThreadingType* threading_model);

HRESULT WinRTGetActivationFactory(
    HSTRING activatableClassId,
    REFIID  iid,
    void** factory);

HRESULT WinRTGetMetadataFile(
    const HSTRING name,
    IMetaDataDispenserEx* metaDataDispenser,
    HSTRING* metaDataFilePath,
    IMetaDataImport2** metaDataImport,
    mdTypeDef* typeDefToken);
