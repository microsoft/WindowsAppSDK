// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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

private:
    static MddCore::WinRT::ThreadingModel GetThreadingModel(
        HSTRING className);

public:
    static void* GetActivationFactory(
        HSTRING className,
        REFIID iid);

    static void Insert(
        size_t index,
        std::shared_ptr<MddCore::WinRTPackage>& winrtPackage);

private:
    static std::recursive_mutex s_lock;
    static std::vector<std::shared_ptr<MddCore::WinRTPackage>> s_winrtPackages;
};
}

#endif // WINRTMODULEMANAGER_H
