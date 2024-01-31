// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <LogController.h>

namespace TB = ::Test::Bootstrap;

#ifdef MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE
#pragma message("MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE is defined")
constexpr bool c_buildIsBootstrapAutoInitialize{ true };
#else
#pragma message("MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE is NOT defined")
constexpr bool c_buildIsBootstrapAutoInitialize{};
#endif

#ifdef MICROSOFT_WINDOWSAPPSDK_SELFCONTAINED
#pragma message("MICROSOFT_WINDOWSAPPSDK_SELFCONTAINED is defined")
constexpr bool c_buildIsSelfContained{ true };
#else
#pragma message("MICROSOFT_WINDOWSAPPSDK_SELFCONTAINED is NOT defined")
constexpr bool c_buildIsSelfContained{};
#endif

#ifdef MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE
#pragma message("MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE is defined")
constexpr bool c_buildIsUndockedRegFreeWinRTAutoInitialize{ true };
#else
#pragma message("MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE is NOT defined")
constexpr bool c_buildIsUndockedRegFreeWinRTAutoInitialize{};
#endif

#ifdef MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE_LOADLIBRARY
#pragma message("MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE_LOADLIBRARY is defined")
constexpr bool c_buildIsUndockedRegFreeWinRTAutoInitializeLoadLibrary{ true };
#else
#pragma message("MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE_LOADLIBRARY is NOT defined")
constexpr bool c_buildIsUndockedRegFreeWinRTAutoInitializeLoadLibrary{};
#endif

namespace Test::UndockedRegFreeWinRT
{
    class WinAppSDKIsSelfContained
    {
    public:
        BEGIN_TEST_CLASS(WinAppSDKIsSelfContained)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE is%s defined\n", c_buildIsBootstrapAutoInitialize ? L"" : L" NOT"));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"MICROSOFT_WINDOWSAPPSDK_SELFCONTAINED is%s defined\n", c_buildIsSelfContained ? L"" : L" NOT"));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE is%s defined\n", c_buildIsUndockedRegFreeWinRTAutoInitialize ? L"" : L" NOT"));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE_LOADLIBRARY is%s defined\n", c_buildIsUndockedRegFreeWinRTAutoInitializeLoadLibrary ? L"" : L" NOT"));

            ::TB::SetupPackages();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::CleanupPackages();
            return true;
        }

        TEST_METHOD(Activation)
        {
            // Setup logging so the child process can log its results through our TAEF log
            // See https://www.osgwiki.com/wiki/WexLogger#Remote_Logging_From_Child_Processes
            // or https://docs.microsoft.com/en-us/windows-hardware/drivers/taef/wexlogger#remote-logging-from-child-processes
            WEX::Common::NoThrowString taefConnectionData;
            VERIFY_SUCCEEDED(WEX::Logging::RemoteLogController::GenerateConnectionData(taefConnectionData));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"RemoteLogController:ConnectionData: %s", static_cast<PCWSTR>(taefConnectionData)));

            auto executable{ GetTargetExecutable() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"TargetExecutable %s", executable.c_str()));

            // NOTE: CreateProcess("foo.exe", "bar") and CreateProcess(NULL, "foo.exe bar") produce very different child behavior
            //
            //       CreateProcess("foo.exe", "bar") and in child process...
            //           GetCommandLine(): "bar"
            //                  main argc: 1
            //               main argv[0]: "bar"
            //               main argv[1]: N/A
            //
            //       CreateProcess(NULL, "foo.exe bar") and in child process...
            //           GetCommandLine(): "foo.exe bar"
            //                  main argc: 2
            //               main argv[0]: "foo.exe"
            //               main argv[1]: "bar"
            // To ensure expected behavior we'll do the latter.

            const auto cmdLine{ std::wstring(executable) + L" --taef:connectiondata=" + static_cast<PCWSTR>(taefConnectionData) };
            PWSTR commandLine{ const_cast<PWSTR>(cmdLine.c_str()) };
            STARTUPINFOW startupInfo{ sizeof(startupInfo) };
            wil::unique_process_information processInformation;
            WEX::Logging::Log::Comment(L"Creating test process...");
            VERIFY_WIN32_BOOL_SUCCEEDED(CreateProcessW(nullptr, commandLine, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &startupInfo, &processInformation),
                WEX::Common::String().Format(L"Executable: %s", executable.c_str()));

            VERIFY_SUCCEEDED(WEX::Logging::RemoteLogController::InitializeLogging(taefConnectionData));

            const auto rc{ WaitForSingleObject(processInformation.hProcess, INFINITE) };
            VERIFY_ARE_EQUAL(WAIT_OBJECT_0, rc);
            DWORD exitCode{};
            VERIFY_WIN32_BOOL_SUCCEEDED(GetExitCodeProcess(processInformation.hProcess, &exitCode));
            VERIFY_ARE_EQUAL(0u, exitCode, WEX::Common::String().Format(L"ExitCode: 0x%X", exitCode));
        }

    private:
        std::filesystem::path GetTargetExecutable() const
        {
            const auto dllFilename{ L"URFW_WinAppSDK.dll" };
            const auto dllPath{ GetModulePath(dllFilename) };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"DllPath(%s): %s", dllFilename, dllPath.c_str()));

            auto target{ dllPath.parent_path() / L"URFW_ExeUsingWinAppSDK\\URFW_ExeUsingWinAppSDK.exe" };
            return target;
        }

        std::filesystem::path GetModulePath(PCWSTR dllFilename) const
        {
            if (!dllFilename)
            {
                return GetExePath();
            }

            wil::unique_hmodule dll{ LoadLibraryExW(dllFilename, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH) };
            VERIFY_IS_NOT_NULL(dll, WEX::Common::String().Format(L"LoadLibraryEx('%s'): %p", dllFilename, dll.get()));
            auto moduleFileName{ wil::GetModuleFileNameW(dll.get()) };
            VERIFY_IS_NOT_NULL(moduleFileName, WEX::Common::String().Format(L"ModuleFileName: %s", moduleFileName.get()));
            return std::filesystem::path{ moduleFileName.get() }.parent_path();
        }

        std::filesystem::path GetExePath() const
        {
            const auto exeFileName{ GetExecutable() };
            return exeFileName.parent_path();
        }

        std::filesystem::path GetExecutable() const
        {
            std::filesystem::path exeFileName{ wil::GetModuleFileNameW().get() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"ExeFileName: %s", exeFileName.c_str()));
            return exeFileName;
        }
    };
}
