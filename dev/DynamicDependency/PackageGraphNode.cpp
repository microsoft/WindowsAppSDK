// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

#include "PackageGraphNode.h"

volatile MDD_PACKAGEDEPENDENCY_CONTEXT MddCore::PackageGraphNode::s_lastContext{};

MddCore::PackageGraphNode::PackageGraphNode(
    _In_ PCWSTR packageFullName,
    INT32 rank,
    _In_ PCWSTR packageDependencyId) :
    m_rank(rank),
    m_id(packageDependencyId)
{
    THROW_IF_WIN32_ERROR(OpenPackageInfoByFullName(packageFullName, 0, &m_packageInfoReference));
    m_packageInfo = std::move(MddCore::PackageInfo::FromPackageInfoReference(m_packageInfoReference.get()));

    BuildPathList();
}

UINT32 MddCore::PackageGraphNode::CountMatchingPackages(
    const UINT32 flags,
    const PackagePathType packagePathType) const
{
    UINT32 bufferLength{};
    UINT32 count{};
    const LONG rc{ ::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, nullptr, &count) };
    if ((rc != ERROR_SUCCESS) && (rc != ERROR_INSUFFICIENT_BUFFER))
    {
        THROW_WIN32(rc);
    }
    return count;
}

UINT32 MddCore::PackageGraphNode::GetMatchingPackages(
    const UINT32 flags,
    const PackagePathType packagePathType,
    wil::unique_cotaskmem_ptr<BYTE[]>& buffer) const
{
    UINT32 bufferLength{};
    const LONG rc{ ::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, nullptr, nullptr) };
    if (rc == ERROR_SUCCESS)
    {
        // Success with no buffer can only mean count==0
        return 0;
    }
    else if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        THROW_WIN32(rc);
    }
    buffer = std::move(wil::make_unique_cotaskmem<BYTE[]>(bufferLength));
    UINT32 count{};
    THROW_IF_WIN32_ERROR(::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, buffer.get(), &count));
    return count;
}

void MddCore::PackageGraphNode::GenerateContext()
{
#if defined(_WIN64)
    MDD_PACKAGEDEPENDENCY_CONTEXT context{ reinterpret_cast<MDD_PACKAGEDEPENDENCY_CONTEXT>(InterlockedIncrement64(reinterpret_cast<volatile LONG64*>(&s_lastContext))) };
#else
    MDD_PACKAGEDEPENDENCY_CONTEXT context{ reinterpret_cast<MDD_PACKAGEDEPENDENCY_CONTEXT>(InterlockedIncrement(reinterpret_cast<volatile LONG*>(&s_lastContext))) };
#endif

    m_context.reset(context);
}

void MddCore::PackageGraphNode::AddDllDirectories()
{
    for (size_t index=0; index < m_packageInfo.Count(); ++index)
    {
        const auto& package{ m_packageInfo.Package(index) };

        wil::unique_dll_directory_cookie cookie(AddDllDirectory(package.path));

        m_addDllDirectoryCookies.push_back(std::move(cookie));
    }
}

void MddCore::PackageGraphNode::RemoveDllDirectories()
{
    m_addDllDirectoryCookies.clear();
}

void MddCore::PackageGraphNode::BuildPathList()
{
    // Should only be called if we have package info
    FAIL_FAST_HR_IF(E_UNEXPECTED, m_packageInfo.Count() == 0);

    // Build a semi-colon delimited list of paths for the packages in the package info
    std::wstring pathList;
    for (size_t index=0; index < m_packageInfo.Count(); ++index)
    {
        const auto& package{ m_packageInfo.Package(index) };
        if (index > 0)
        {
            pathList += L';';
        }
        pathList += package.path;
    }
    m_pathList = std::move(pathList);
}

void MddCore::PackageGraphNode::ParseManifestsIfNecessary()
{
    if (m_manifestsParsed)
    {
        return;
    }

    // Reset the list (in case of previous attempt and failure)
    m_inprocModules.clear();

    // Parse the packages' manifest
    for (size_t index=0; index < m_packageInfo.Count(); ++index)
    {
        const auto& package{ m_packageInfo.Package(index) };
        ParseAppxManifest(package);
    }
}


/// Parse a package's appxmanifest for WinRT inproc server definitions e.g.
/// ~~~~~
/// <Extension Category="windows.inProcessServer"...>
///   <InProcessServer>
///     <Path>foo.dll</Path>
///     <ActivatableClass ActivatableClassId="Blah.YaddaYadda" ThreadingModel="both"/>
/// ~~~~~
/// A package can have multiple such <Extension>s but each has 1 <InProcessServer> child element.
///
/// <InProcessServer> is unique in the manifest. <InProcessServer> isn't used by anything else in the manifest
/// and unlikely to be so it's safe to target this as our 'root' of parsing activity.
///
/// <InProcessServer>'s children:
///   * 1x <Path>
///   * 1+ <ActivatableClassId>
///
/// <ActivatableClass>'s attributes:
///   * ActivatableClassId=string
///   * ThreadingModel = "both" | "STA" | "MTA"
void MddCore::PackageGraphNode::ParseAppxManifest(const PACKAGE_INFO& package)
{
    std::filesystem::path filename{ package.path };
    filename /= L"appxmanifest.xml";
    wil::com_ptr<IStream> appxManifestStream;
    THROW_IF_FAILED(SHCreateStreamOnFileEx(filename.c_str(), STGM_READ, FILE_ATTRIBUTE_NORMAL, FALSE, nullptr, appxManifestStream.addressof()));

    wil::com_ptr<IXmlReader> xmlReader;
    auto appxManifestIUnknown = appxManifestStream.query<IUnknown>();
    THROW_IF_FAILED(CreateXmlReader(__uuidof(IXmlReader), reinterpret_cast<void**>(xmlReader.addressof()), nullptr));
    THROW_IF_FAILED(xmlReader->SetInput(appxManifestIUnknown.get()));
    for (;;)
    {
        XmlNodeType nodeType{};
        const HRESULT hr{ xmlReader->Read(&nodeType) };
        THROW_IF_FAILED_MSG(hr, "Error 0x%X reading %ls", hr, filename.c_str());
        if (hr == S_FALSE)
        {
            // S_FALSE = end-of-input. We're done
            break;
        }

        if (nodeType == XmlNodeType_Element)
        {
            PCWSTR localName{};
            THROW_IF_FAILED(xmlReader->GetLocalName(&localName, nullptr));
            if (CompareStringOrdinal(localName, -1, L"InProcessServer", -1, FALSE) == CSTR_EQUAL)
            {
                ParseAppxManifest_InProcessServer(xmlReader.get(), filename);
            }
        }
    }
}

/// See ParseAppxManifest for <InProcessServer>'s schema
void MddCore::PackageGraphNode::ParseAppxManifest_InProcessServer(
    IXmlReader* xmlReader,
    const std::filesystem::path& filename)
{
    MddCore::WinRTInprocModule winrtInProcModule;
    for (;;)
    {
        XmlNodeType nodeType{};
        HRESULT hr{ xmlReader->Read(&nodeType) };
        THROW_IF_FAILED_MSG(hr, "Error 0x%X parsing <InProcessServer> in %ls", hr, filename.c_str());
        if (hr == S_FALSE)
        {
            // S_FALSE = end-of-input. We're done
            break;
        }

        if (nodeType == XmlNodeType_Element)
        {
            PCWSTR localName{};
            THROW_IF_FAILED(xmlReader->GetLocalName(&localName, nullptr));
            if (CompareStringOrdinal(localName, -1, L"Path", -1, FALSE) == CSTR_EQUAL)
            {
                PCWSTR value{};
                THROW_IF_FAILED(xmlReader->GetValue(&value, nullptr));
                winrtInProcModule.Path(value);
            }
            else if (CompareStringOrdinal(localName, -1, L"ActivatableClass", -1, FALSE) == CSTR_EQUAL)
            {
                // Walk all attributes parsing those we're interested in.
                // Use this pattern for better performance than multiple MoveToAttributeByName calls.
                std::wstring activatableClassId;
                MddCore::WinRT::ThreadingModel threadingModel{};
                hr = xmlReader->MoveToFirstAttribute();
                for (;;)
                {
                    THROW_IF_FAILED_MSG(hr, "Error 0x%X parsing <ActivatableClass> in %ls", hr, filename.c_str());
                    if (hr == S_FALSE)
                    {
                        // S_FALSE = end-of-input. We're done
                        break;
                    }
                    PCWSTR value{};
                    THROW_IF_FAILED(xmlReader->GetValue(&value, nullptr));
                    if (CompareStringOrdinal(localName, -1, L"ActivatableClassId", -1, FALSE) == CSTR_EQUAL)
                    {
                        activatableClassId = value;
                    }
                    else if (CompareStringOrdinal(localName, -1, L"ThreadingModel", -1, FALSE) == CSTR_EQUAL)
                    {
                        if (CompareStringOrdinal(localName, -1, L"both", -1, FALSE) == CSTR_EQUAL)
                        {
                            threadingModel = MddCore::WinRT::ThreadingModel::Both;
                        }
                        else if (CompareStringOrdinal(localName, -1, L"STA", -1, FALSE) == CSTR_EQUAL)
                        {
                            threadingModel = MddCore::WinRT::ThreadingModel::STA;
                        }
                        else if (CompareStringOrdinal(localName, -1, L"MTA", -1, FALSE) == CSTR_EQUAL)
                        {
                            threadingModel = MddCore::WinRT::ThreadingModel::MTA;
                        }
                        else
                        {
                            THROW_HR_MSG(APPX_E_INVALID_MANIFEST, "Error 0x%X parsing <ActivatableClass> in %ls", hr, filename.c_str());
                        }
                    }

                    // Next!
                    hr =xmlReader->MoveToNextAttribute();
                }
                THROW_HR_IF_MSG(APPX_E_INVALID_MANIFEST, activatableClassId.empty() || (threadingModel == MddCore::WinRT::ThreadingModel::Unknown), "Error 0x%X parsing <ActivatableClass> in %ls", hr, filename.c_str());
                winrtInProcModule.AddInprocServer(activatableClassId, threadingModel);
            }
        }
    }
    THROW_HR_IF_MSG(APPX_E_INVALID_MANIFEST, winrtInProcModule.Path().empty() || winrtInProcModule.InprocServers().empty(), "Error 0x%X parsing <ActivatableClass> in %ls", APPX_E_INVALID_MANIFEST, filename.c_str());

    // Gotcha!
    m_inprocModules.push_back(std::move(winrtInProcModule));
}

HRESULT MddCore::PackageGraphNode::GetActivatableClassThreadingModel(
    HSTRING className,
    const std::wstring& activatableClassId,
    MddCore::WinRT::ThreadingModel& threadingModel) noexcept try
{
    // Load the WinRT definitions (if necessary)
    ParseManifestsIfNecessary();

    // Find the activation factory
    for (size_t index = 0; index < m_inprocModules.size(); ++index)
    {
        auto& inprocModule{ m_inprocModules[index] };

        auto acidThreadingModel{ inprocModule.Find(activatableClassId) };
        if (acidThreadingModel != MddCore::WinRT::ThreadingModel::Unknown)
        {
            threadingModel = acidThreadingModel;
            return S_OK;
        }
    }

    // Not found
    threadingModel = MddCore::WinRT::ThreadingModel::Unknown;
    return S_OK;
}
CATCH_RETURN();

HRESULT MddCore::PackageGraphNode::GetActivationFactory(
    HSTRING className,
    const std::wstring& activatableClassId,
    REFIID iid,
    MddCore::WinRT::ThreadingModel& threadingModel,
    void** factory) noexcept try
{
    // Load the WinRT definitions (if necessary)
    ParseManifestsIfNecessary();

    // Find the activation factory
    for (size_t index = 0; index < m_inprocModules.size(); ++index)
    {
        auto& inprocModule{ m_inprocModules[index] };

        auto acidThreadingModel{ inprocModule.Find(activatableClassId) };
        if (acidThreadingModel != MddCore::WinRT::ThreadingModel::Unknown)
        {
            RETURN_IF_FAILED(inprocModule.GetActivationFactory(className, iid, factory));
            threadingModel = acidThreadingModel;
            return S_OK;
        }
    }

    // Not found
    threadingModel = MddCore::WinRT::ThreadingModel::Unknown;
    *factory = nullptr;
    return S_OK;
}
CATCH_RETURN();
