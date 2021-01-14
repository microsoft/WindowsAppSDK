// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "WinRTPackage.h"

MddCore::WinRT::ThreadingModel MddCore::WinRTPackage::GetThreadingModel(
    const std::wstring& activatableClassId)
{
    // Load the WinRT definitions (if necessary)
    ParseManifestsIfNecessary();

    // Find the activation factory
    if (!m_inprocModules.empty())
    {
        for (size_t index = 0; index < m_inprocModules.size(); ++index)
        {
            auto& inprocModule{ m_inprocModules[index] };

            auto threadingModel{ inprocModule.Find(activatableClassId) };
            if (threadingModel != MddCore::WinRT::ThreadingModel::Unknown)
            {
                return threadingModel;
            }
        }
    }

    // Not found
    return MddCore::WinRT::ThreadingModel::Unknown;
}

void* MddCore::WinRTPackage::GetActivationFactory(
    const std::wstring& activatableClassId,
    REFIID iid)
{
    // Load the WinRT definitions (if necessary)
    ParseManifestsIfNecessary();

    // Find the activation factory
    if (!m_inprocModules.empty())
    {
        for (size_t index = 0; index < m_inprocModules.size(); ++index)
        {
            auto& inprocModule{ m_inprocModules[index] };

            auto threadingModel{ inprocModule.Find(activatableClassId) };
            if (threadingModel != MddCore::WinRT::ThreadingModel::Unknown)
            {
                //TODO
                //RETURN_IF_FAILED(inprocModule.GetActivationFactory(className, iid, factory));
                return inprocModule;
            }
        }
    }

    // Not found
    return nullptr;
}

void MddCore::WinRTPackage::ParseManifestsIfNecessary()
{
    if (m_manifestsParsed)
    {
        return;
    }

    // Reset the list (in case of previous attempt and failure)
    m_inprocModules.clear();

    // Parse the packages' manifest
    ParseAppxManifest();
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
void MddCore::WinRTPackage::ParseAppxManifest()
{
    std::filesystem::path filename{ m_packagePath };
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
void MddCore::WinRTPackage::ParseAppxManifest_InProcessServer(
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
