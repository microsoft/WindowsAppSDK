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
        const std::wstring& packageGraphNodeId,
        const std::wstring& packagePath) :
        m_packageGraphNodeId(packageGraphNodeId),
        m_packagePath(packagePath)
    {
    }

    ~WinRTPackage() = default;

    MddCore::WinRT::ThreadingModel GetThreadingModel(
        const std::wstring& className);

    void* GetActivationFactory(
        const std::wstring& className,
        REFIID iid);

private:
    void ParseManifestsIfNecessary();

    void ParseAppxManifest();

    void ParseAppxManifest_InProcessServer(
        IXmlReader* xmlReader,
        const std::filesystem::path& filename);

private:
    std::wstring m_packageGraphNodeId;
    std::wstring m_packagePath;
    std::vector<WinRTInprocModule> m_inprocModules;
    bool m_manifestsParsed{};
};
}

#endif // WINRTPACKAGE_H
