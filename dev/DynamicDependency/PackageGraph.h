// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(PACKAGEGRAPH_H)
#define PACKAGEGRAPH_H

#include <MsixDynamicDependency.h>

#include <PackageGraphNode.h>

namespace MddCore
{
enum class Architecture : int32_t // per PACKAGE_ID.processorArchitecture
{
    X86 = winrt::Windows::System::ProcessorArchitecture::X86,               // 0 = PROCESSOR_ARCHITECTURE_INTEL
    X64 = winrt::Windows::System::ProcessorArchitecture::X64,               // 9 = PROCESSOR_ARCHITECTURE_AMD64
    Arm = winrt::Windows::System::ProcessorArchitecture::Arm,               // 5 = PROCESSOR_ARCHITECTURE_ARM
    Arm64 = winrt::Windows::System::ProcessorArchitecture::Arm64,           // 12 = PROCESSOR_ARCHITECTURE_ARM64
    X86OnArm64 = winrt::Windows::System::ProcessorArchitecture::X86OnArm64, // 14 = PROCESSOR_ARCHITECTURE_IA32_ON_ARM64
    Neutral = winrt::Windows::System::ProcessorArchitecture::Neutral,       // 11 = PROCESSOR_ARCHITECTURE_NEUTRAL
    Unknown = winrt::Windows::System::ProcessorArchitecture::Unknown,       // 0xFFFF = PROCESSOR_ARCHITECTURE_UNKNOWN
};

std::unique_lock<std::mutex> AcquirePackageGraphLock();

typedef LONG (WINAPI * GetCurrentPackageInfo2Function)(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count);

HRESULT GetCurrentPackageInfo2(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count,
    GetCurrentPackageInfo2Function getCurrentPackageInfo2) noexcept;

UINT32 SerializePackageInfoToBuffer(
    const UINT32 flags,
    const PackagePathType packagePathType,
    const UINT32 bufferLength,
    BYTE* buffer,
    const std::vector<MddCore::PackageGraphNode*>& matchingPackageInfo,
    const UINT32 dynamicPackagesCount,
    const PACKAGE_INFO* staticPackageInfo,
    const UINT32 staticPackagesCount);

void SerializeStringToBuffer(
    const UINT32 bufferLength,
    BYTE*& buffer,
    UINT32& bufferNeeded,
    PWSTR& to,
    PCWSTR from);

HRESULT ResolvePackageDependency(
    PCWSTR packageDependencyId,
    wil::unique_process_heap_string& packageFullName);

HRESULT ResolvePackageDependency(
    PCWSTR packageDependencyId,
    MddAddPackageDependencyOptions options,
    wil::unique_process_heap_string& packageFullName);

HRESULT IsPackageABetterFitPerArchitecture(
    PCWSTR bestFit,
    PCWSTR packageFullName,
    bool& isBetterFit);

bool IsPackageABetterFitPerArchitecture(
    PCWSTR bestFit,
    Architecture bestFitArchitecture,
    Architecture packageFullNameArchitecture);

HRESULT PackageArchitectureFromFullName(
    PCWSTR packageFullName,
    Architecture& architecture);

Architecture GetCurrentArchitecture();

HRESULT AddToPackageGraph(
    PCWSTR packageFullName,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    MDD_PACKAGEDEPENDENCY_CONTEXT& context);

HRESULT RemoveFromPackageGraph(MDD_PACKAGEDEPENDENCY_CONTEXT context);
}

#endif // PACKAGEGRAPH_H
