// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(WINRTPACKAGE_H)
#define WINRTPACKAGE_H

#include <xmllite.h>

#include "WinRTInprocModule.h"

namespace MddCore
{
class WinRTPackage
{
public:
    WinRTPackage() = default;

    WinRTPackage(
        MDD_PACKAGEDEPENDENCY_CONTEXT context,
        const std::wstring& packagePath) :
        m_context(context),
        m_packagePath(packagePath)
    {
    }

    WinRTPackage(WinRTPackage&& other) :
        m_context(std::move(other.m_context)),
        m_packagePath(std::move(other.m_packagePath)),
        m_manifestsParsed(std::move(other.m_manifestsParsed))
    {
        for (auto& inprocModule : other.m_inprocModules)
        {
            m_inprocModules.push_back(std::move(inprocModule));
        }
    }

    ~WinRTPackage() = default;

    MddCore::WinRT::ThreadingModel GetThreadingModel(
        const std::wstring& activatableClassId);

    void* GetActivationFactory(
        HSTRING className,
        const std::wstring& activatableClassId,
        REFIID iid);

private:
    void ParseManifestsIfNecessary();

    void ParseAppxManifest();

    void ParseAppxManifest_InProcessServer(
        IXmlReader* xmlReader,
        const std::filesystem::path& filename);

private:
    MDD_PACKAGEDEPENDENCY_CONTEXT m_context{};
    std::wstring m_packagePath;
    std::vector<WinRTInprocModule> m_inprocModules;
    bool m_manifestsParsed{};
};
}

#endif // WINRTPACKAGE_H
