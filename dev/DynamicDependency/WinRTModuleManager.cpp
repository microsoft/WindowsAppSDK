// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "WinRTModuleManager.h"

std::vector<std::unique_ptr<MddCore::WinRTPackage>> MddCore::WinRTModuleManager::s_winrtPackages;

ABI::Windows::Foundation::ThreadingType MddCore::WinRTModuleManager::GetThreadingType(
    HSTRING className)
{
    auto threadingModel{ MddCore::WinRTModuleManager::GetThreadingModel(className) };
    THROW_HR_IF(REGDB_E_CLASSNOTREG, threadingModel == MddCore::WinRT::ThreadingModel::Unknown);

    ABI::Windows::Foundation::ThreadingType threadingType{};
    THROW_IF_FAILED(ToThreadingType(threadingModel, threadingType));
    return threadingType;
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
    std::unique_ptr<MddCore::WinRTPackage>& winrtPackage)
{
    if (index < s_winrtPackages.size())
    {
        s_winrtPackages.insert(s_winrtPackages.begin() + index, std::move(winrtPackage));
    }
    else
    {
        s_winrtPackages.push_back(std::move(winrtPackage));
    }
}
