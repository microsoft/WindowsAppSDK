// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(WINRTMODULEMANAGER_H)
#define WINRTMODULEMANAGER_H

#include <WinRTPackage.h>

namespace MddCore
{
class WinRTModuleManager
{
public:
    static ABI::Windows::Foundation::ThreadingType GetThreadingType(
        HSTRING className);

    static MddCore::WinRT::ThreadingModel GetThreadingModel(
        HSTRING className);

    static void* GetActivationFactory(
        HSTRING className,
        REFIID iid);

    static void Add(
        const std::wstring& packageId,
        MddCore::WinRTPackage& winrtPackage);

private:
    static std::vector<MddCore::WinRTPackage> s_winrtPackages;
};
}

#endif // WINRTMODULEMANAGER_H
