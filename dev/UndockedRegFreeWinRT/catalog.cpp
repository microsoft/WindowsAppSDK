// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "catalog.h"
#include "Microsoft.Utf8.h"
#include "TypeResolution.h"

#include <activation.h>
#include <shlwapi.h>
#include <rometadata.h>

#include <wrl.h>

#include <../DynamicDependency/API/MddWinRT.h>

using namespace std;
using namespace Microsoft::WRL;

//TODO Components won't respect COM lifetime. workaround to get them in the COM list? See dev\UndockedRegFreeWinRT\catalog.cpp

extern "C"
{
    typedef HRESULT(__stdcall* activation_factory_type)(HSTRING, IActivationFactory**);
}

// Intentionally no class factory cache here. That would be excessive since
// other layers already cache.
struct component
{
    wstring module_name;
    wstring xmlns;
    HMODULE handle = nullptr;
    activation_factory_type get_activation_factory{};
    ABI::Windows::Foundation::ThreadingType threading_model{ ABI::Windows::Foundation::ThreadingType::ThreadingType_BOTH };

    ~component()
    {
        if (handle)
        {
            FreeLibrary(handle);
        }
    }

    HRESULT LoadModule()
    {
        if (handle == nullptr)
        {
            handle = LoadLibraryExW(module_name.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
            if (handle == nullptr)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }
            this->get_activation_factory = (activation_factory_type)GetProcAddress(handle, "DllGetActivationFactory");
            if (this->get_activation_factory == nullptr)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }
        }
        return (handle != nullptr && this->get_activation_factory != nullptr) ? S_OK : E_FAIL;
    }

    HRESULT GetActivationFactory(HSTRING className, REFIID  iid, void** factory)
    {
        RETURN_IF_FAILED(LoadModule());

        IActivationFactory* ifactory = nullptr;
        HRESULT hr = this->get_activation_factory(className, &ifactory);
        // optimize for IActivationFactory?
        if (SUCCEEDED(hr))
        {
            hr = ifactory->QueryInterface(iid, factory);
            ifactory->Release();
        }
        return hr;
    }
};

static unordered_map<wstring, shared_ptr<component>> g_types;

HRESULT LoadManifestFromPath(std::wstring path)
{
    if (path.size() < 4)
    {
        return COR_E_ARGUMENT;
    }
    std::wstring ext(path.substr(path.size() - 4, path.size()));
    if ((CompareStringOrdinal(ext.c_str(), -1, L".exe", -1, TRUE) == CSTR_EQUAL) ||
        (CompareStringOrdinal(ext.c_str(), -1, L".dll", -1, TRUE) == CSTR_EQUAL))
    {
        return LoadFromEmbeddedManifest(path.c_str());
    }
    else
    {
        return LoadFromSxSManifest(path.c_str());
    }
}

HRESULT LoadFromSxSManifest(PCWSTR path)
{
    return WinRTLoadComponentFromFilePath(path);
}

HRESULT LoadFromEmbeddedManifest(PCWSTR path)
{
    wil::unique_hmodule handle(LoadLibraryExW(path, nullptr, LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), !handle);

    // Try both just to be on the safe side
    HRSRC hrsc = FindResourceW(handle.get(), MAKEINTRESOURCEW(1), RT_MANIFEST);
    if (!hrsc)
    {
        hrsc = FindResourceW(handle.get(), MAKEINTRESOURCEW(2), RT_MANIFEST);
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), !hrsc);
    }
    HGLOBAL embeddedManifest = LoadResource(handle.get(), hrsc);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), !embeddedManifest);

    DWORD length = SizeofResource(handle.get(), hrsc);
    void* data = LockResource(embeddedManifest);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), !data);

    return WinRTLoadComponentFromString(std::string_view((char*)data, length));
}

HRESULT WinRTLoadComponentFromFilePath(PCWSTR manifestPath)
{
    try
    {
        wil::unique_hfile file{ ::CreateFileW(manifestPath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr) };
        RETURN_HR_IF(HRESULT_FROM_WIN32(GetLastError()), !file);

        LARGE_INTEGER fileSize{};
        RETURN_IF_WIN32_BOOL_FALSE(::GetFileSizeEx(file.get(), &fileSize));
        const auto dataSize{ fileSize.QuadPart };
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), dataSize > INT32_MAX);
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_SXS_XML_E_UNEXPECTEDEOF), dataSize == 0);

        const auto bufferSize{ static_cast<DWORD>(dataSize) + 1 };
        std::unique_ptr<char[]> buffer{ std::make_unique<char[]>(bufferSize) };

        DWORD bytesRead{};
        RETURN_IF_WIN32_BOOL_FALSE(::ReadFile(file.get(), buffer.get(), bufferSize, &bytesRead, nullptr));
        file.reset();
        buffer[bytesRead] = '\0';

        return WinRTLoadComponentFromString(std::string_view(buffer.get(), bytesRead));
    }
    catch(...)
    {
        LOG_CAUGHT_EXCEPTION();
        return ERROR_SXS_MANIFEST_PARSE_ERROR;
    }
}

HRESULT WinRTLoadComponentFromString(std::string_view xmlStringValue)
{
    try
    {
        auto wideXmlString = ::Microsoft::Utf8::ToUtf16(xmlStringValue.data());

        // Expand any env vars, such as %MICROSOFT_WINDOWSAPPRUNTIME_BASE_DIRECTORY% in asmv3:file.loadFrom
        auto expandedSize = ExpandEnvironmentStringsW(wideXmlString.data(), nullptr, 0);
        RETURN_HR_IF(HRESULT_FROM_WIN32(GetLastError()), expandedSize == 0);
        std::unique_ptr<WCHAR[]> expanded{ std::make_unique<WCHAR[]>(expandedSize) };
        expandedSize = ExpandEnvironmentStringsW(wideXmlString.data(), expanded.get(), expandedSize);
        RETURN_HR_IF(HRESULT_FROM_WIN32(GetLastError()), expandedSize == 0);

        ComPtr<IStream> xmlStream;
        xmlStream.Attach(SHCreateMemStream(reinterpret_cast<const BYTE*>(expanded.get()), static_cast<UINT>(expandedSize * sizeof(WCHAR))));
        RETURN_HR_IF_NULL(E_OUTOFMEMORY, xmlStream);
        ComPtr<IXmlReaderInput> xmlReaderInput;
        RETURN_IF_FAILED(CreateXmlReaderInputWithEncodingName(xmlStream.Get(), nullptr, L"UCS-2", FALSE, nullptr, &xmlReaderInput));

        return ParseRootManifestFromXmlReaderInput(xmlReaderInput.Get());
    }
    catch (...)
    {
        LOG_CAUGHT_EXCEPTION();
        return ERROR_SXS_MANIFEST_PARSE_ERROR;
    }
}

HRESULT ParseRootManifestFromXmlReaderInput(IUnknown* input)
{
    XmlNodeType nodeType;
    PCWSTR localName = nullptr;
    auto locale = _create_locale(LC_ALL, "C");
    ComPtr<IXmlReader> xmlReader;
    RETURN_IF_FAILED(CreateXmlReader(__uuidof(IXmlReader), (void**)&xmlReader, nullptr));
    RETURN_IF_FAILED(xmlReader->SetInput(input));
    while (S_OK == xmlReader->Read(&nodeType))
    {
        if (nodeType == XmlNodeType_Element)
        {
            RETURN_IF_FAILED((xmlReader->GetLocalName(&localName, nullptr)));

            if (_wcsicmp_l(localName, L"file", locale) == 0)
            {
                RETURN_IF_FAILED(ParseFileTag(xmlReader.Get()));
            }
        }
    }

    return S_OK;
}

HRESULT ParseFileTag(IXmlReader* xmlReader)
{
    PCWSTR localName = nullptr;
    PCWSTR value = nullptr;
    std::wstring fileName;
    auto locale = _create_locale(LC_ALL, "C");
    HRESULT hr = xmlReader->MoveToFirstAttribute();
    if (S_FALSE == hr)
    {
        return HRESULT_FROM_WIN32(ERROR_SXS_MANIFEST_PARSE_ERROR);
    }
    else
    {
        while (TRUE)
        {
            if (FAILED_LOG(xmlReader->GetLocalName(&localName, NULL)))
            {
                return HRESULT_FROM_WIN32(ERROR_SXS_MANIFEST_PARSE_ERROR);
            }
            if (FAILED_LOG(xmlReader->GetValue(&value, NULL)))
            {
                return HRESULT_FROM_WIN32(ERROR_SXS_MANIFEST_PARSE_ERROR);
            }
            if (localName != nullptr)
            {
                if ((_wcsicmp_l(L"name", localName, locale) == 0) && fileName.empty())
                {
                    fileName = value;
                }
                else if (_wcsicmp_l(L"loadFrom", localName, locale) == 0)
                {
                    // override bare filename with fully qualified loadFrom path if supplied
                    fileName = value;
                }
            }
            if (xmlReader->MoveToNextAttribute() != S_OK)
            {
                break;
            }
        }
    }
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_SXS_MANIFEST_PARSE_ERROR), fileName.empty());
    XmlNodeType nodeType;
    while (S_OK == xmlReader->Read(&nodeType))
    {
        if (nodeType == XmlNodeType_Element)
        {
            RETURN_IF_FAILED(xmlReader->GetLocalName(&localName, nullptr));
            if (localName != nullptr && _wcsicmp_l(localName, L"activatableClass", locale) == 0)
            {
                RETURN_IF_FAILED(ParseActivatableClassTag(xmlReader, fileName.c_str()));
            }
        }
        else if (nodeType == XmlNodeType_EndElement)
        {
            RETURN_IF_FAILED(xmlReader->GetLocalName(&localName, nullptr));
            RETURN_HR_IF(S_OK, localName != nullptr && _wcsicmp_l(localName, L"file", locale) == 0);
        }
    }
    return S_OK;
}

HRESULT ParseActivatableClassTag(IXmlReader* xmlReader, PCWSTR fileName)
{
    auto locale = _create_locale(LC_ALL, "C");
    auto this_component = make_shared<component>();
    this_component->module_name = fileName;
    HRESULT hr = xmlReader->MoveToFirstAttribute();
    const WCHAR* activatableClass = nullptr;
    const WCHAR* threadingModel = nullptr;
    if (S_FALSE == hr)
    {
        return HRESULT_FROM_WIN32(ERROR_SXS_MANIFEST_PARSE_ERROR);
    }
    else
    {
        while (TRUE)
        {
            const WCHAR* pwszLocalName;
            const WCHAR* pwszValue;
            if (FAILED_LOG(xmlReader->GetLocalName(&pwszLocalName, NULL)))
            {
                return HRESULT_FROM_WIN32(ERROR_SXS_MANIFEST_PARSE_ERROR);
            }
            if (FAILED_LOG(xmlReader->GetValue(&pwszValue, NULL)))
            {
                return HRESULT_FROM_WIN32(ERROR_SXS_MANIFEST_PARSE_ERROR);
            }
            if (pwszLocalName != nullptr)
            {
                if (_wcsicmp_l(L"threadingModel", pwszLocalName, locale) == 0)
                {
                    threadingModel = pwszValue;
                }
                else if (_wcsicmp_l(L"name", pwszLocalName, locale) == 0)
                {
                    activatableClass = pwszValue;
                }
            }
            if (xmlReader->MoveToNextAttribute() != S_OK)
            {
                break;
            }
        }
    }
    if (threadingModel == nullptr)
    {
        return HRESULT_FROM_WIN32(ERROR_SXS_MANIFEST_PARSE_ERROR);
    }
    if (_wcsicmp_l(L"sta", threadingModel, locale) == 0)
    {
        this_component->threading_model = ABI::Windows::Foundation::ThreadingType::ThreadingType_STA;
    }
    else if (_wcsicmp_l(L"mta", threadingModel, locale) == 0)
    {
        this_component->threading_model = ABI::Windows::Foundation::ThreadingType::ThreadingType_MTA;
    }
    else if (_wcsicmp_l(L"both", threadingModel, locale) == 0)
    {
        this_component->threading_model = ABI::Windows::Foundation::ThreadingType::ThreadingType_BOTH;
    }
    else
    {
        return HRESULT_FROM_WIN32(ERROR_SXS_MANIFEST_PARSE_ERROR);
    }

    if (activatableClass == nullptr || !activatableClass[0])
    {
        return HRESULT_FROM_WIN32(ERROR_SXS_MANIFEST_PARSE_ERROR);
    }
    // Check for duplicate activatable classes
    auto component_iter = g_types.find(activatableClass);
    if (component_iter != g_types.end())
    {
        return HRESULT_FROM_WIN32(ERROR_SXS_DUPLICATE_ACTIVATABLE_CLASS);
    }
    g_types[activatableClass] = this_component;
    return S_OK;
}

HRESULT WinRTGetThreadingModel(HSTRING activatableClassId, ABI::Windows::Foundation::ThreadingType* threading_model)
{
    HRESULT hr{ WinRTGetThreadingModel_PackageGraph(activatableClassId, threading_model) };
    if (hr == REGDB_E_CLASSNOTREG)  // Not found
    {
        hr = WinRTGetThreadingModel_SxS(activatableClassId, threading_model);
    }
    return hr;
}

HRESULT WinRTGetThreadingModel_PackageGraph(HSTRING activatableClassId, ABI::Windows::Foundation::ThreadingType* threading_model)
{
    return MddCore::WinRT::GetThreadingModel(activatableClassId, *threading_model);
}

HRESULT WinRTGetThreadingModel_SxS(HSTRING activatableClassId, ABI::Windows::Foundation::ThreadingType* threading_model)
{
    auto raw_class_name = WindowsGetStringRawBuffer(activatableClassId, nullptr);
    auto component_iter = g_types.find(raw_class_name);
    if (component_iter != g_types.end())
    {
        *threading_model = component_iter->second->threading_model;
        return S_OK;
    }
    return REGDB_E_CLASSNOTREG;
}

HRESULT WinRTGetActivationFactory(
    HSTRING activatableClassId,
    REFIID iid,
    void** factory)
{
    RETURN_IF_FAILED(WinRTGetActivationFactory_PackageGraph(activatableClassId, iid, factory));
    if (*factory == nullptr)    // Not found
    {
        RETURN_IF_FAILED(WinRTGetActivationFactory_SxS(activatableClassId, iid, factory));
    }
    return S_OK;

}

HRESULT WinRTGetActivationFactory_PackageGraph(
    HSTRING activatableClassId,
    REFIID iid,
    void** factory)
{
    RETURN_IF_FAILED(MddCore::WinRT::GetActivationFactory(activatableClassId, iid, factory));
    return S_OK;
}

HRESULT WinRTGetActivationFactory_SxS(
    HSTRING activatableClassId,
    REFIID iid,
    void** factory)
{
    auto raw_class_name = WindowsGetStringRawBuffer(activatableClassId, nullptr);
    auto component_iter = g_types.find(raw_class_name);
    if (component_iter != g_types.end())
    {
        return component_iter->second->GetActivationFactory(activatableClassId, iid, factory);
    }
    return REGDB_E_CLASSNOTREG;
}

HRESULT WinRTGetMetadataFile(
    const HSTRING name,
    IMetaDataDispenserEx* metaDataDispenser,
    HSTRING* metaDataFilePath,
    IMetaDataImport2** metaDataImport,
    mdTypeDef* typeDefToken)
{
    wchar_t folderPrefix[9];
    PCWSTR pszFullName = WindowsGetStringRawBuffer(name, nullptr);
    HRESULT hr = StringCchCopyW(folderPrefix, _countof(folderPrefix), pszFullName);
    if (hr != S_OK && hr != STRSAFE_E_INSUFFICIENT_BUFFER)
    {
        return hr;
    }
    if (CompareStringOrdinal(folderPrefix, -1, L"Windows.", -1, FALSE) == CSTR_EQUAL)
    {
        return RO_E_METADATA_NAME_NOT_FOUND;
    }

    if (metaDataFilePath != nullptr)
    {
        *metaDataFilePath = nullptr;
    }
    if (metaDataImport != nullptr)
    {
        *metaDataImport = nullptr;
    }
    if (typeDefToken != nullptr)
    {
        *typeDefToken = mdTypeDefNil;
    }

    if (((metaDataImport == nullptr) && (typeDefToken != nullptr)) ||
        ((metaDataImport != nullptr) && (typeDefToken == nullptr)))
    {
        return E_INVALIDARG;
    }

    ComPtr<IMetaDataDispenserEx> spMetaDataDispenser;
    // The API uses the caller's passed-in metadata dispenser. If null, it
    // will create an instance of the metadata reader to dispense metadata files.
    if (metaDataDispenser == nullptr)
    {
        // Avoid using CoCreateInstance here, which will trigger a Feature-On-Demand (FOD)
        // installation request of .NET Framework 3.5 if it's not already installed. In the
        // mean time, Windows App SDK runtime doesn't need .NET Framework 3.5.
        RETURN_IF_FAILED(MetaDataGetDispenser(CLSID_CorMetaDataDispenser,
            IID_IMetaDataDispenser,
            &spMetaDataDispenser));
        {
            auto versionString{ wil::make_bstr_nothrow(L"WindowsRuntime 1.4") };
            RETURN_IF_NULL_ALLOC(versionString);
            VARIANT version{};
            version.vt = VT_BSTR;
            version.bstrVal = versionString.get();
            RETURN_IF_FAILED(spMetaDataDispenser->SetOption(MetaDataRuntimeVersion, &version));
        }
    }
    return UndockedRegFreeWinRT::ResolveThirdPartyType(
        spMetaDataDispenser.Get(),
        pszFullName,
        metaDataFilePath,
        metaDataImport,
        typeDefToken);
}
