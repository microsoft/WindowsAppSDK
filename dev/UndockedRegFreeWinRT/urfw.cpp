﻿// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include <roapi.h>
#include <wrl.h>
#include <ctxtcall.h>
#include <activation.h>
#include <VersionHelpers.h>

#include <IsWindowsVersion.h>

#include "urfw.h"

#include "catalog.h"
#include "TypeResolution.h"

#include <../Detours/detours.h>

// Ensure that metadata resolution functions are imported so they can be detoured
extern "C"
{
    __declspec(dllimport) HRESULT WINAPI RoGetMetaDataFile(
        const HSTRING name,
        IMetaDataDispenserEx* metaDataDispenser,
        HSTRING* metaDataFilePath,
        IMetaDataImport2** metaDataImport,
        mdTypeDef* typeDefToken);

    __declspec(dllimport) HRESULT WINAPI RoParseTypeName(
        HSTRING typeName,
        DWORD* partsCount,
        HSTRING** typeNameParts);

    __declspec(dllimport) HRESULT WINAPI RoResolveNamespace(
        const HSTRING name,
        const HSTRING windowsMetaDataDir,
        const DWORD packageGraphDirsCount,
        const HSTRING* packageGraphDirs,
        DWORD* metaDataFilePathsCount,
        HSTRING** metaDataFilePaths,
        DWORD* subNamespacesCount,
        HSTRING** subNamespaces);

    __declspec(dllimport) HRESULT WINAPI RoIsApiContractPresent(
        PCWSTR name,
        UINT16 majorVersion,
        UINT16 minorVersion,
        BOOL* present);

    __declspec(dllimport) HRESULT WINAPI RoIsApiContractMajorVersionPresent(
        PCWSTR name,
        UINT16 majorVersion,
        BOOL* present);
}

static decltype(RoActivateInstance)* TrueRoActivateInstance = RoActivateInstance;
static decltype(RoGetActivationFactory)* TrueRoGetActivationFactory = RoGetActivationFactory;
static decltype(RoGetMetaDataFile)* TrueRoGetMetaDataFile = RoGetMetaDataFile;
static decltype(RoResolveNamespace)* TrueRoResolveNamespace = RoResolveNamespace;

static bool g_apisAreDetoured{};

enum class ActivationLocation
{
    CurrentApartment,
    CrossApartmentMTA
};

VOID CALLBACK EnsureMTAInitializedCallBack(
    PTP_CALLBACK_INSTANCE /*instance*/,
    PVOID                 /*parameter*/,
    PTP_WORK              /*work*/)
{
    Microsoft::WRL::ComPtr<IComThreadingInfo> spThreadingInfo;
    CoGetObjectContext(IID_PPV_ARGS(&spThreadingInfo));
}

/*
In the context callback call to the MTA apartment, there is a bug that prevents COM
from automatically initializing MTA remoting. It only allows NTA to be intialized
outside of the NTA and blocks all others. The workaround for this is to spin up another
thread that is not been CoInitialize. COM treats this thread as a implicit MTA and
when we call CoGetObjectContext on it we implicitily initialized the MTA.
*/
HRESULT EnsureMTAInitialized()
{
    TP_CALLBACK_ENVIRON callBackEnviron;
    InitializeThreadpoolEnvironment(&callBackEnviron);
    PTP_POOL pool = CreateThreadpool(nullptr);
    if (pool == nullptr)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    SetThreadpoolThreadMaximum(pool, 1);
    if (!SetThreadpoolThreadMinimum(pool, 1))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    PTP_CLEANUP_GROUP cleanupgroup = CreateThreadpoolCleanupGroup();
    if (cleanupgroup == nullptr)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    SetThreadpoolCallbackPool(&callBackEnviron, pool);
    SetThreadpoolCallbackCleanupGroup(&callBackEnviron,
        cleanupgroup,
        nullptr);
    PTP_WORK ensureMTAInitializedWork = CreateThreadpoolWork(
        &EnsureMTAInitializedCallBack,
        nullptr,
        &callBackEnviron);
    if (ensureMTAInitializedWork == nullptr)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    SubmitThreadpoolWork(ensureMTAInitializedWork);
    CloseThreadpoolCleanupGroupMembers(cleanupgroup, FALSE, nullptr);
    return S_OK;
}

HRESULT GetActivationLocation(HSTRING activatableClassId, ActivationLocation &activationLocation)
{
    // We don't override inbox (Windows.*) runtimeclasses
    UINT32 activatableClassIdAsStringLength{};
    auto activatableClassIdAsString{ WindowsGetStringRawBuffer(activatableClassId, &activatableClassIdAsStringLength) };
    {
        // Does the activatableClassId start with "Windows."?
        auto windowsNamespacePrefix{ L"Windows." };
        const int windowsNamespacePrefixLength{ 8 };
        if (activatableClassIdAsStringLength >= windowsNamespacePrefixLength)
        {
            if (CompareStringOrdinal(activatableClassIdAsString, windowsNamespacePrefixLength, windowsNamespacePrefix, windowsNamespacePrefixLength, FALSE) == CSTR_EQUAL)
            {
                return REGDB_E_CLASSNOTREG;
            }
        }
    }

    APTTYPE aptType{};
    APTTYPEQUALIFIER aptQualifier{};
    RETURN_IF_FAILED(CoGetApartmentType(&aptType, &aptQualifier));

    ABI::Windows::Foundation::ThreadingType threading_model;
    const HRESULT hr{ WinRTGetThreadingModel(activatableClassId, &threading_model) };
    if (FAILED(hr))
    {
        if (hr == REGDB_E_CLASSNOTREG)  // Not found
        {
            return REGDB_E_CLASSNOTREG;
        }
        RETURN_HR_MSG(hr, "URFW: ActivatableClassId=%ls", activatableClassIdAsString);
    }
    switch (threading_model)
    {
    case ABI::Windows::Foundation::ThreadingType_BOTH:
        activationLocation = ActivationLocation::CurrentApartment;
        break;
    case ABI::Windows::Foundation::ThreadingType_STA:
        if (aptType == APTTYPE_MTA)
        {
            return RO_E_UNSUPPORTED_FROM_MTA;
        }
        else
        {
            activationLocation = ActivationLocation::CurrentApartment;
        }
        break;
    case ABI::Windows::Foundation::ThreadingType_MTA:
        if (aptType == APTTYPE_MTA)
        {
            activationLocation = ActivationLocation::CurrentApartment;
        }
        else
        {
            activationLocation = ActivationLocation::CrossApartmentMTA;
        }
        break;
    }
    return S_OK;
}


HRESULT WINAPI RoActivateInstanceDetour(HSTRING activatableClassId, IInspectable** instance)
{
    ActivationLocation location;
    HRESULT hr = GetActivationLocation(activatableClassId, location);
    if (hr == REGDB_E_CLASSNOTREG)
    {
        return TrueRoActivateInstance(activatableClassId, instance);
    }
    RETURN_IF_FAILED(hr);

    // Activate in current apartment
    if (location == ActivationLocation::CurrentApartment)
    {
        Microsoft::WRL::ComPtr<IActivationFactory> pFactory;
        RETURN_IF_FAILED(WinRTGetActivationFactory(activatableClassId, __uuidof(IActivationFactory), (void**)&pFactory));
        return pFactory->ActivateInstance(instance);
    }

    // Cross apartment MTA activation
    struct CrossApartmentMTAActData {
        HSTRING activatableClassId;
        IStream *stream;
    };

    CrossApartmentMTAActData cbdata{ activatableClassId };
    CO_MTA_USAGE_COOKIE mtaUsageCookie;
    RETURN_IF_FAILED(CoIncrementMTAUsage(&mtaUsageCookie));
    RETURN_IF_FAILED(EnsureMTAInitialized());
    Microsoft::WRL::ComPtr<IContextCallback> defaultContext;
    ComCallData data;
    data.pUserDefined = &cbdata;
    RETURN_IF_FAILED(CoGetDefaultContext(APTTYPE_MTA, IID_PPV_ARGS(&defaultContext)));
    RETURN_IF_FAILED(defaultContext->ContextCallback(
        [](_In_ ComCallData* pComCallData) -> HRESULT
        {
            CrossApartmentMTAActData* data = reinterpret_cast<CrossApartmentMTAActData*>(pComCallData->pUserDefined);
            Microsoft::WRL::ComPtr<IInspectable> instance;
            Microsoft::WRL::ComPtr<IActivationFactory> pFactory;
            RETURN_IF_FAILED(WinRTGetActivationFactory(data->activatableClassId, __uuidof(IActivationFactory), (void**)&pFactory));
            RETURN_IF_FAILED(pFactory->ActivateInstance(&instance));
            RETURN_IF_FAILED(CoMarshalInterThreadInterfaceInStream(IID_IInspectable, instance.Get(), &data->stream));
            return S_OK;
        },
        &data, IID_ICallbackWithNoReentrancyToApplicationSTA, 5, nullptr)); // 5 is meaningless.
    RETURN_IF_FAILED(CoGetInterfaceAndReleaseStream(cbdata.stream, IID_IInspectable, (LPVOID*)instance));
    return S_OK;
}

HRESULT WINAPI RoGetActivationFactoryDetour(HSTRING activatableClassId, REFIID iid, void** factory)
{
    ActivationLocation location;
    HRESULT hr = GetActivationLocation(activatableClassId, location);
    if (hr == REGDB_E_CLASSNOTREG)
    {
        return TrueRoGetActivationFactory(activatableClassId, iid, factory);
    }
    RETURN_IF_FAILED(hr);

    // Activate in current apartment
    if (location == ActivationLocation::CurrentApartment)
    {
        RETURN_IF_FAILED(WinRTGetActivationFactory(activatableClassId, iid, factory));
        return S_OK;
    }
    // Cross apartment MTA activation
    struct CrossApartmentMTAActData {
        HSTRING activatableClassId;
        IStream* stream;
    };
    CrossApartmentMTAActData cbdata{ activatableClassId };
    CO_MTA_USAGE_COOKIE mtaUsageCookie;
    RETURN_IF_FAILED(CoIncrementMTAUsage(&mtaUsageCookie));
    RETURN_IF_FAILED(EnsureMTAInitialized());
    Microsoft::WRL::ComPtr<IContextCallback> defaultContext;
    ComCallData data;
    data.pUserDefined = &cbdata;
    RETURN_IF_FAILED(CoGetDefaultContext(APTTYPE_MTA, IID_PPV_ARGS(&defaultContext)));
    defaultContext->ContextCallback(
        [](_In_ ComCallData* pComCallData) -> HRESULT
        {
            CrossApartmentMTAActData* data = reinterpret_cast<CrossApartmentMTAActData*>(pComCallData->pUserDefined);
            Microsoft::WRL::ComPtr<IActivationFactory> pFactory;
            RETURN_IF_FAILED(WinRTGetActivationFactory(data->activatableClassId, __uuidof(IActivationFactory), (void**)&pFactory));
            RETURN_IF_FAILED(CoMarshalInterThreadInterfaceInStream(IID_IActivationFactory, pFactory.Get(), &data->stream));
            return S_OK;
        },
        &data, IID_ICallbackWithNoReentrancyToApplicationSTA, 5, nullptr); // 5 is meaningless.
    RETURN_IF_FAILED(CoGetInterfaceAndReleaseStream(cbdata.stream, IID_IActivationFactory, factory));
    return S_OK;
}

HRESULT WINAPI RoGetMetaDataFileDetour(
    const HSTRING name,
    IMetaDataDispenserEx* metaDataDispenser,
    HSTRING* metaDataFilePath,
    IMetaDataImport2** metaDataImport,
    mdTypeDef* typeDefToken)
{
    HRESULT hr = WinRTGetMetadataFile(name, metaDataDispenser, metaDataFilePath, metaDataImport, typeDefToken);
    // Don't fallback on RO_E_METADATA_NAME_IS_NAMESPACE failure. This is the intended behavior for namespace names.
    if (FAILED(hr) && hr != RO_E_METADATA_NAME_IS_NAMESPACE)
    {
        hr = TrueRoGetMetaDataFile(name, metaDataDispenser, metaDataFilePath, metaDataImport, typeDefToken);
    }
    return hr;
}

HRESULT WINAPI RoResolveNamespaceDetour(
    const HSTRING name,
    const HSTRING windowsMetaDataDir,
    const DWORD packageGraphDirsCount,
    const HSTRING* packageGraphDirs,
    DWORD* metaDataFilePathsCount,
    HSTRING** metaDataFilePaths,
    DWORD* subNamespacesCount,
    HSTRING** subNamespaces)
{
    PCWSTR exeFilePath = nullptr;
    UndockedRegFreeWinRT::GetProcessExeDir(&exeFilePath);
    auto pathReference = Microsoft::WRL::Wrappers::HStringReference(exeFilePath);
    HSTRING packageGraphDirectories[] = { pathReference.Get() };
    HRESULT hr = TrueRoResolveNamespace(name, pathReference.Get(),
        ARRAYSIZE(packageGraphDirectories), packageGraphDirectories,
        metaDataFilePathsCount, metaDataFilePaths,
        subNamespacesCount, subNamespaces);
    if (FAILED(hr))
    {
        hr = TrueRoResolveNamespace(name, windowsMetaDataDir,
            packageGraphDirsCount, packageGraphDirs,
            metaDataFilePathsCount, metaDataFilePaths,
            subNamespacesCount, subNamespaces);
    }
    return hr;
}

HRESULT ExtRoLoadCatalog()
{
    WCHAR filePath[MAX_PATH]{};
    if (!GetModuleFileNameW(nullptr, filePath, _countof(filePath)))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    std::wstring manifestPath(filePath);
    HANDLE hActCtx{ INVALID_HANDLE_VALUE };
    auto exit = wil::scope_exit([&]
    {
        if (hActCtx != INVALID_HANDLE_VALUE)
        {
            ReleaseActCtx(hActCtx);
        }
    });
    wil::unique_hmodule exeModule;
    RETURN_IF_WIN32_BOOL_FALSE(GetModuleHandleExW(0, nullptr, &exeModule));
    ACTCTXW acw{ sizeof(acw) };
    acw.lpSource = manifestPath.c_str();
    acw.hModule = exeModule.get();
    acw.lpResourceName = MAKEINTRESOURCEW(1);
    acw.dwFlags = ACTCTX_FLAG_HMODULE_VALID | ACTCTX_FLAG_RESOURCE_NAME_VALID;

    hActCtx = CreateActCtxW(&acw);
    if ((hActCtx == INVALID_HANDLE_VALUE) || (hActCtx == nullptr))
    {
        const auto lastError{ GetLastError() };
        if ((lastError == ERROR_RESOURCE_DATA_NOT_FOUND) || (lastError == ERROR_RESOURCE_TYPE_NOT_FOUND))
        {
            // No resources in the executable (ERROR_RESOURCE_DATA_NOT_FOUND) or there are resources
            // but not an embedded SxS manifest we're looking for (ERROR_RESOURCE_TYPE_NOT_FOUND).
            // Either way it's Not Found == Nothing to do!
            return S_OK;
        }
        RETURN_WIN32(lastError);
    }

    PACTIVATION_CONTEXT_DETAILED_INFORMATION actCtxInfo = nullptr;
    SIZE_T bufferSize{};
    (void)QueryActCtxW(0,
        hActCtx,
        nullptr,
        ActivationContextDetailedInformation,
        nullptr,
        0,
        &bufferSize);
    RETURN_HR_IF(HRESULT_FROM_WIN32(GetLastError()), bufferSize == 0);
    auto actCtxInfoBuffer{ std::make_unique<BYTE[]>(bufferSize) };
    RETURN_IF_NULL_ALLOC(actCtxInfoBuffer);
    actCtxInfo = reinterpret_cast<PACTIVATION_CONTEXT_DETAILED_INFORMATION>(actCtxInfoBuffer.get());

    RETURN_IF_WIN32_BOOL_FALSE(QueryActCtxW(0,
        hActCtx,
        nullptr,
        ActivationContextDetailedInformation,
        actCtxInfo,
        bufferSize,
        nullptr));

    for (DWORD index = 1; index <= actCtxInfo->ulAssemblyCount; index++)
    {
        bufferSize = 0;
        PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION asmInfo = nullptr;
        (void)QueryActCtxW(0,
            hActCtx,
            &index,
            AssemblyDetailedInformationInActivationContext,
            nullptr,
            0,
            &bufferSize);
        RETURN_HR_IF(HRESULT_FROM_WIN32(GetLastError()), bufferSize == 0);
        auto asmInfobuffer{ std::make_unique<BYTE[]>(bufferSize) };
        RETURN_IF_NULL_ALLOC(asmInfobuffer);
        asmInfo = reinterpret_cast<PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION>(asmInfobuffer.get());

        RETURN_IF_WIN32_BOOL_FALSE(QueryActCtxW(0,
            hActCtx,
            &index,
            AssemblyDetailedInformationInActivationContext,
            asmInfo,
            bufferSize,
            nullptr));
        RETURN_IF_FAILED(LoadManifestFromPath(asmInfo->lpAssemblyManifestPath));
    }
    return S_OK;
}

HRESULT UrfwInitialize() noexcept
{
#if defined(TODO_URFW_DELEGATE_TO_OS_19H1PLUS)
    // Windows' Reg-Free WinRT first appeared in Windows 10 Version 1903, May 2019 Update (aka 19H1)
    // https://blogs.windows.com/windowsdeveloper/2019/04/30/enhancing-non-packaged-desktop-apps-using-windows-runtime-components/
    // Delegate to the OS' implementation when available
    if (WindowsVersion::IsWindows10_19H1OrGreater())
    {
        return S_OK;
    }
#elif defined(TODO_SEEME_PRODUCT_TARGET)
    // Delegate to the OS' implementation on >= Windows 11 24H1
    if (WindowsVersion::IsWindows11_22H2OrGreater())
    {
        return S_OK;
    }
#else
    // Delegate to the OS' implementation on >= Windows 11 24H1
    if (WindowsVersion::IsWindows11_24H1OrGreater())
    {
        return S_OK;
    }
#endif

    // OS Reg-Free WinRT isn't available so let's do it ourselves...
    DetourAttach(&(PVOID&)TrueRoActivateInstance, RoActivateInstanceDetour);
    DetourAttach(&(PVOID&)TrueRoGetActivationFactory, RoGetActivationFactoryDetour);
    DetourAttach(&(PVOID&)TrueRoGetMetaDataFile, RoGetMetaDataFileDetour);
    DetourAttach(&(PVOID&)TrueRoResolveNamespace, RoResolveNamespaceDetour);
    g_apisAreDetoured = true;
    try
    {
        RETURN_IF_FAILED(ExtRoLoadCatalog());
    }
    catch (...)
    {
        RETURN_CAUGHT_EXCEPTION();
    }
    return S_OK;
}

void UrfwShutdown() noexcept
{
    if (g_apisAreDetoured)
    {
        DetourDetach(&(PVOID&)TrueRoActivateInstance, RoActivateInstanceDetour);
        DetourDetach(&(PVOID&)TrueRoGetActivationFactory, RoGetActivationFactoryDetour);
        DetourDetach(&(PVOID&)TrueRoGetMetaDataFile, RoGetMetaDataFileDetour);
        DetourDetach(&(PVOID&)TrueRoResolveNamespace, RoResolveNamespaceDetour);
        g_apisAreDetoured = false;
    }
}

extern "C" void WINAPI winrtact_Initialize()
{
    return;
}
