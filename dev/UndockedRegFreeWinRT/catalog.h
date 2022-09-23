// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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

HRESULT WinRTGetThreadingModel_PackageGraph(
    HSTRING activatableClassId,
    ABI::Windows::Foundation::ThreadingType* threading_model);

HRESULT WinRTGetThreadingModel_SxS(
    HSTRING activatableClassId,
    ABI::Windows::Foundation::ThreadingType* threading_model);

HRESULT WinRTGetActivationFactory(
    HSTRING activatableClassId,
    REFIID  iid,
    void** factory);

HRESULT WinRTGetActivationFactory_PackageGraph(
    HSTRING activatableClassId,
    REFIID  iid,
    void** factory);

HRESULT WinRTGetActivationFactory_SxS(
    HSTRING activatableClassId,
    REFIID  iid,
    void** factory);

HRESULT WinRTGetMetadataFile(
    const HSTRING name,
    IMetaDataDispenserEx* metaDataDispenser,
    HSTRING* metaDataFilePath,
    IMetaDataImport2** metaDataImport,
    mdTypeDef* typeDefToken);
