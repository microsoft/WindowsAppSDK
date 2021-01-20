// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(WINRTMODULEMANAGER_H)
#define WINRTMODULEMANAGER_H

#include "WinRTPackage.h"

namespace MddCore
{
class WinRTModuleManager
{
public:
    static bool GetThreadingType(
        HSTRING className,
        ABI::Windows::Foundation::ThreadingType& threadingType);

    static MddCore::WinRT::ThreadingModel GetThreadingModel(
        HSTRING className);

    static void* GetActivationFactory(
        HSTRING className,
        REFIID iid);

    static void Insert(
        size_t index,
        std::shared_ptr<MddCore::WinRTPackage>& winrtPackage);

private:
    static std::mutex s_lock;
    static std::vector<std::shared_ptr<MddCore::WinRTPackage>> s_winrtPackages;
};
}

#endif // WINRTMODULEMANAGER_H
