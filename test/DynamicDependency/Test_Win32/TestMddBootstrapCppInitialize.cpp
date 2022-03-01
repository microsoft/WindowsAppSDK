// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#define WINDOWSAPPSDK_RELEASE_MAJORMINOR        0x00040001u
#define WINDOWSAPPSDK_RELEASE_VERSION_TAG_W     L"experimental1"
#define WINDOWSAPPSDK_RUNTIME_VERSION_UINT64    0x0004000107AF014DLLu

#include <unknwn.h>

#include <string>

#include <wil/resource.h>
#include <wil/result_macros.h>

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

    auto f1 = B::Initialize_failfast();
    auto f2 = B::Initialize_failfast(0x12345678);
    auto f3 = B::Initialize_failfast(0x12345678, L"versiontag");
    auto f4 = B::Initialize_failfast(0x12345678, L"versiontag", AM::PackageVersion(WINDOWSAPPSDK_RUNTIME_VERSION_UINT64));
    auto f5 = B::Initialize_failfast(0x12345678, L"versiontag", pv0);

    auto t1 = B::Initialize();
    auto t2 = B::Initialize(0x12345678);
    auto t3 = B::Initialize(0x12345678, L"versiontag");
    auto t4 = B::Initialize(0x12345678, L"versiontag", AM::PackageVersion(WINDOWSAPPSDK_RUNTIME_VERSION_UINT64));
    auto t5 = B::Initialize(0x12345678, L"versiontag", pv0);

    RETURN_IF_FAILED(B::Initialize_nothrow());
    RETURN_IF_FAILED(B::Initialize_nothrow(0x12345678));
    RETURN_IF_FAILED(B::Initialize_nothrow(0x12345678, L"versiontag"));
    RETURN_IF_FAILED(B::Initialize_nothrow(0x12345678, L"versiontag", AM::PackageVersion(WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)));
    RETURN_IF_FAILED(B::Initialize_nothrow(0x12345678, L"versiontag", pv0));

    return S_OK;
}
}
