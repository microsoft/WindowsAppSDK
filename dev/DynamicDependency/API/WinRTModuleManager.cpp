// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "WinRTModuleManager.h"

std::recursive_mutex MddCore::WinRTModuleManager::s_lock;
std::vector<std::shared_ptr<MddCore::WinRTPackage>> MddCore::WinRTModuleManager::s_winrtPackages;

bool MddCore::WinRTModuleManager::GetThreadingType(
    HSTRING className,
    ABI::Windows::Foundation::ThreadingType& threadingType)
{
    auto lock{ std::unique_lock<std::recursive_mutex>(s_lock) };

    auto threadingModel{ MddCore::WinRTModuleManager::GetThreadingModel(className) };
    if (threadingModel == MddCore::WinRT::ThreadingModel::Unknown)
    {
        return false;
    }

    THROW_IF_FAILED(ToThreadingType(threadingModel, threadingType));
    return true;

}

MddCore::WinRT::ThreadingModel MddCore::WinRTModuleManager::GetThreadingModel(
    HSTRING className)
{
    if (!s_winrtPackages.empty())
    {
        std::wstring activatableClassId{ WindowsGetStringRawBuffer(className, nullptr) };
        for (auto& winrtPackage : s_winrtPackages)
        {
            auto threadingModel{ winrtPackage->GetThreadingModel(activatableClassId) };
            if (threadingModel != MddCore::WinRT::ThreadingModel::Unknown)
            {
                return threadingModel;
            }
        }
    }
    return MddCore::WinRT::ThreadingModel::Unknown;
}

void* MddCore::WinRTModuleManager::GetActivationFactory(
    HSTRING className,
    REFIID iid)
{
    auto lock{ std::unique_lock<std::recursive_mutex>(s_lock) };

    if (!s_winrtPackages.empty())
    {
        std::wstring activatableClassId{ WindowsGetStringRawBuffer(className, nullptr) };
        for (auto& winrtPackage : s_winrtPackages)
        {
            auto factory{ winrtPackage->GetActivationFactory(className, activatableClassId, iid) };
            if (factory)
            {
                return factory;
            }
        }
    }
    return nullptr;
}

void MddCore::WinRTModuleManager::Insert(
    size_t index,
    std::shared_ptr<MddCore::WinRTPackage>& winrtPackage)
{
    auto lock{ std::unique_lock<std::recursive_mutex>(s_lock) };

    if (index < s_winrtPackages.size())
    {
        s_winrtPackages.insert(s_winrtPackages.begin() + index, std::move(winrtPackage));
    }
    else
    {
        s_winrtPackages.push_back(std::move(winrtPackage));
    }
}
