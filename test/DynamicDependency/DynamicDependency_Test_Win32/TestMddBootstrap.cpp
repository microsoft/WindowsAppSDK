// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MddBootstrap.h>

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test::DynamicDependency
{
    TEST_CLASS(BootstrapTests)
    {
    public:

        TEST_CLASS_INITIALIZE(Setup)
        {
            // CppUnitTest initializes COM as STA before we get called
            // But we don't need (or want) STA, and we do want MTA. We can't
            // stop CppUnitTest from initializing COM but we can uninitialize
            // it and (re)initialize it as MTA. Don't think of it as crude
            // and brutish but rather 'thinking outside the box'...
            COM::CoSuperInitialize();

            // We need to find Microsoft.ProjectReunion.Bootstrap.dll.
            // Normally it's colocated with the application (i.e. same dir as the exe)
            // but that's not true of our test project (a dll) in our build environment
            // (different directories). So we'll explicitly find and load it so the
            // rest of our test is fine
            auto bootstrapDllAbsoluteFilename{ TF::GetBootstrapAbsoluteFilename() };
            wil::unique_hmodule bootstrapDll(LoadLibrary(bootstrapDllAbsoluteFilename.c_str()));
            const auto lastError{ GetLastError() };
            Assert::IsNotNull(bootstrapDll.get());

            TP::RemovePackage_MainSidecar();
            TP::RemovePackage_ProjectReunionFramework();
            TP::AddPackage_ProjectReunionFramework();
            TP::AddPackage_MainSidecar();

            m_bootstrapDll = std::move(bootstrapDll);
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            m_bootstrapDll.reset();

            TP::RemovePackage_MainSidecar();
            TP::RemovePackage_ProjectReunionFramework();

            winrt::uninit_apartment();
        }

        TEST_METHOD(Initialize_ClassNotFound)
        {
            const GUID doesNotExist{};
            Assert::AreEqual(REGDB_E_CLASSNOTREG, MddBootstrapInitialize(doesNotExist));
        }

        TEST_METHOD(Initialize)
        {
            Assert::AreEqual(S_OK, MddBootstrapInitialize(Test::Packages::MainSidecar::c_MyLifetimeManagerClsid));

            MddBootstrapShutdown();
        }

        TEST_METHOD(ShutdownWithoutInitialize)
        {
            MddBootstrapShutdown();
            MddBootstrapShutdown();
        }

    private:
        static wil::unique_hmodule m_bootstrapDll;
    };
}

wil::unique_hmodule Test::DynamicDependency::BootstrapTests::m_bootstrapDll;
