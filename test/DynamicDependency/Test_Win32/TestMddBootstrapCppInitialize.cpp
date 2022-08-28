// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#define WINDOWSAPPSDK_RELEASE_MAJORMINOR        0x00040001u
#define WINDOWSAPPSDK_RELEASE_VERSION_TAG_W     L"experimental1"
#define WINDOWSAPPSDK_RUNTIME_VERSION_UINT64    0x0004000107AF014DLLu

#include <unknwn.h>

#include <string>

#include <winrt/base.h>

#include <MddBootstrap.h>

// NOTE: These are compile-time tests to verify syntax. Do not actually run them.
namespace Test::DynamicDependency::Bootstrap::CPP
{
namespace AM = ::Microsoft::Windows::ApplicationModel;
namespace B { using namespace AM::DynamicDependency::Bootstrap; }

HRESULT TestCompile()
{
    AM::PackageVersion pv0;
    AM::PackageVersion pv1(uint16_t(1));
    AM::PackageVersion pv2(1u, 2u);
    AM::PackageVersion pv3(1u, 2u, 3u);
    AM::PackageVersion pv4(1u, 2u, 3u, 4u);
    AM::PackageVersion pv5(11110ull);
    AM::PackageVersion pv6(0x0001000200030004u);
    AM::PackageVersion pv7(0x0001000200030004ul);
    AM::PackageVersion pv8(0x0001000200030004ull);

    B::InitializeOptions opt0{};
    B::InitializeOptions opt1{ B::InitializeOptions::None };
    B::InitializeOptions opt2{ B::InitializeOptions::OnError_DebugBreak |
                               B::InitializeOptions::OnError_DebugBreak_IfDebuggerAttached |
                               B::InitializeOptions::OnError_FailFast |
                               B::InitializeOptions::OnNoMatch_ShowUI |
                               B::InitializeOptions::OnPackageIdentity_NOOP
    };

    auto f1 = B::InitializeFailFast();
    auto f2 = B::InitializeFailFast(0x12345678);
    auto f3 = B::InitializeFailFast(0x12345678, L"versiontag");
    auto f4 = B::InitializeFailFast(0x12345678, L"versiontag", AM::PackageVersion(WINDOWSAPPSDK_RUNTIME_VERSION_UINT64));
    auto f5 = B::InitializeFailFast(0x12345678, L"versiontag", pv0);
    auto f6 = B::InitializeFailFast(0x12345678, L"versiontag", pv0, opt0);
    auto f7 = B::InitializeFailFast(0x12345678, L"versiontag", pv0, opt1);
    auto f8 = B::InitializeFailFast(0x12345678, L"versiontag", pv0, opt2);

    auto t1 = B::Initialize();
    auto t2 = B::Initialize(0x12345678);
    auto t3 = B::Initialize(0x12345678, L"versiontag");
    auto t4 = B::Initialize(0x12345678, L"versiontag", AM::PackageVersion(WINDOWSAPPSDK_RUNTIME_VERSION_UINT64));
    auto t5 = B::Initialize(0x12345678, L"versiontag", pv0);
    auto t6 = B::Initialize(0x12345678, L"versiontag", pv0, opt0);
    auto t7 = B::Initialize(0x12345678, L"versiontag", pv0, opt1);
    auto t8 = B::Initialize(0x12345678, L"versiontag", pv0, opt2);

    const auto h1{ B::InitializeNoThrow() };
    (void)h1; // Ignore 'warning C4189:...: local variable is initialized but not referenced
    const auto h2{ B::InitializeNoThrow(0x12345678) };
    (void)h2; // Ignore 'warning C4189:...: local variable is initialized but not referenced
    const auto h3{ B::InitializeNoThrow(0x12345678, L"versiontag") };
    (void)h3; // Ignore 'warning C4189:...: local variable is initialized but not referenced
    const auto h4{ B::InitializeNoThrow(0x12345678, L"versiontag", AM::PackageVersion(WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)) };
    (void)h4; // Ignore 'warning C4189:...: local variable is initialized but not referenced
    const auto h5{ B::InitializeNoThrow(0x12345678, L"versiontag", pv0) };
    (void)h5; // Ignore 'warning C4189:...: local variable is initialized but not referenced
    const auto h6{ B::InitializeNoThrow(0x12345678, L"versiontag", pv0, opt0) };
    (void)h6; // Ignore 'warning C4189:...: local variable is initialized but not referenced
    const auto h7{ B::InitializeNoThrow(0x12345678, L"versiontag", pv0, opt1) };
    (void)h7; // Ignore 'warning C4189:...: local variable is initialized but not referenced
    const auto h8{ B::InitializeNoThrow(0x12345678, L"versiontag", pv0, opt2) };
    (void)h8; // Ignore 'warning C4189:...: local variable is initialized but not referenced

    return S_OK;
}
}
