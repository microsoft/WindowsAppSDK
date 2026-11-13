// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <LogController.h>
#include <TerminalVelocityFeatures-ApplicationData.h>
#include <initializer_list>
#include <string_view>

namespace Test::ApplicationData::Tests
{
    class UnpackagedApplicationDataContextTests
    {
    public:
        BEGIN_TEST_CLASS(UnpackagedApplicationDataContextTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::Microsoft::Windows::Storage::ApplicationData::Feature_ApplicationDataUnpackagedContext::IsEnabled())
            {
                RunScenario(L"disabled");
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Unpackaged context APIs are experimental.");
            }
            return true;
        }

        struct ContextResource
        {
            PCWSTR name;
            const void* data{};
            DWORD size{};
        };

        void RunScenario(PCWSTR scenario, std::initializer_list<ContextResource> resources = {},
                         HRESULT expectedFailure = S_OK)
        {
            GUID id{};
            VERIFY_SUCCEEDED(::CoCreateGuid(&id));
            wchar_t idString[39]{};
            VERIFY_ARE_NOT_EQUAL(0, ::StringFromGUID2(id, idString, ARRAYSIZE(idString)));
            const auto directory{ std::filesystem::temp_directory_path() /
                                  (std::wstring{ L"WindowsAppSDK.ApplicationDataContext." } + idString) };
            const auto executable{ directory / L"ApplicationDataContextTestApp.exe" };
            const std::initializer_list<PCWSTR> files{
                L"ApplicationDataContextTestApp.exe", L"Wex.Common.dll", L"Wex.Logger.dll", L"Wex.Communication.dll" };
            VERIFY_IS_TRUE(std::filesystem::create_directory(directory));
            auto cleanup{ wil::scope_exit([&]
            {
                for (const auto file : files)
                {
                    ::DeleteFileW((directory / file).c_str());
                }
                ::RemoveDirectoryW(directory.c_str());
            }) };
            const auto source{ ::Test::FileSystem::GetSolutionOutDirPath() /
                               L"ApplicationDataContextTestApp" };
            for (const auto file : files)
            {
                VERIFY_WIN32_BOOL_SUCCEEDED(::CopyFileW((source / file).c_str(), (directory / file).c_str(), TRUE));
            }
            if (resources.size() != 0)
            {
                const auto update{ ::BeginUpdateResourceW(executable.c_str(), FALSE) };
                VERIFY_IS_NOT_NULL(update);
                auto discard{ wil::scope_exit([&] { ::EndUpdateResourceW(update, TRUE); }) };
                for (const auto& resource : resources)
                {
                    VERIFY_WIN32_BOOL_SUCCEEDED(::UpdateResourceW(update, L"ApplicationDataContext", resource.name,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), const_cast<void*>(resource.data), resource.size));
                }
                discard.release();
                VERIFY_WIN32_BOOL_SUCCEEDED(::EndUpdateResourceW(update, FALSE));
            }

            const auto runtime{ ::Test::FileSystem::GetWindowsAppRuntimeDllAbsoluteFilename() };
            WEX::Common::NoThrowString connectionData;
            VERIFY_SUCCEEDED(WEX::Logging::RemoteLogController::GenerateConnectionData(connectionData));
            std::wstring command{ static_cast<PCWSTR>(WEX::Common::String().Format(L"\"%s\" %s \"%s\" %08X %s\"%s\"",
                executable.c_str(), scenario, runtime.c_str(), static_cast<unsigned int>(expectedFailure),
                WEX::Logging::c_szWexLoggerRemoteConnectionData, static_cast<PCWSTR>(connectionData))) };
            STARTUPINFOW startup{ sizeof(startup) };
            wil::unique_process_information process;
            VERIFY_WIN32_BOOL_SUCCEEDED(::CreateProcessW(executable.c_str(), command.data(), nullptr, nullptr, FALSE,
                0, nullptr, nullptr, &startup, &process));
            auto stopChild{ wil::scope_exit([&]
            {
                if (::WaitForSingleObject(process.hProcess, 0) == WAIT_TIMEOUT)
                {
                    ::TerminateProcess(process.hProcess, ERROR_TIMEOUT);
                    ::WaitForSingleObject(process.hProcess, 10000);
                }
            }) };
            VERIFY_SUCCEEDED(WEX::Logging::RemoteLogController::InitializeLogging(connectionData));
            VERIFY_ARE_EQUAL(static_cast<DWORD>(WAIT_OBJECT_0), ::WaitForSingleObject(process.hProcess, 60000));
            DWORD exitCode{};
            VERIFY_WIN32_BOOL_SUCCEEDED(::GetExitCodeProcess(process.hProcess, &exitCode));
            VERIFY_ARE_EQUAL(0u, exitCode, WEX::Common::String().Format(L"Scenario %s exited with 0x%08X", scenario, exitCode));
        }

        TEST_METHOD(ResourceContext)
        {
            RunScenario(L"resources");
            RunScenario(L"late-set");
        }

        TEST_METHOD(ApiContextValidationAndSetOnce)
        {
            RunScenario(L"setter");
        }

        TEST_METHOD(MissingContextAndRetry)
        {
            constexpr HRESULT missing{ HRESULT_FROM_WIN32(ERROR_RESOURCE_NOT_PRESENT) };
            RunScenario(L"failure", {{ L"ApplicationData.Publisher" }, { L"ApplicationData.Product" }}, missing);
            for (const auto name : { L"ApplicationData.Publisher", L"ApplicationData.Product" })
            {
                RunScenario(L"failure", {{ name }}, missing);
                constexpr wchar_t empty[]{ L"" };
                RunScenario(L"failure", {{ name, empty, sizeof(empty) }}, missing);
            }
        }

        TEST_METHOD(MalformedContextAndOverride)
        {
            for (const auto name : { L"ApplicationData.Publisher", L"ApplicationData.Product" })
            {
                constexpr BYTE oddLength[]{ 'A', 0, 0 };
                constexpr wchar_t unterminated[]{ L'A' };
                constexpr wchar_t invalidName[]{ L"foo\\bar" };
                RunScenario(L"failure", {{ name, oddLength, sizeof(oddLength) }}, E_UNEXPECTED);
                RunScenario(L"failure", {{ name, unterminated, sizeof(unterminated) }}, E_UNEXPECTED);
                RunScenario(L"failure", {{ name, invalidName, sizeof(invalidName) }}, E_INVALIDARG);
                RunScenario(L"setter", {{ name, unterminated, sizeof(unterminated) }});
            }
        }

        TEST_METHOD(EmbeddedNulContext)
        {
            for (const auto name : { L"ApplicationData.Publisher", L"ApplicationData.Product" })
            {
                const auto scenario{ std::wstring_view{ name } == L"ApplicationData.Publisher" ? L"publisher-prefix" : L"product-prefix" };
                constexpr wchar_t embeddedNul[]{ L"Good\0Bad" };
                constexpr wchar_t trailingData[]{ L"Good\0\0" };
                constexpr wchar_t emptyPrefix[]{ L"\0Good" };
                RunScenario(scenario, {{ name, embeddedNul, sizeof(embeddedNul) }});
                RunScenario(scenario, {{ name, trailingData, sizeof(trailingData) }});
                RunScenario(L"failure", {{ name, emptyPrefix, sizeof(emptyPrefix) }}, HRESULT_FROM_WIN32(ERROR_RESOURCE_NOT_PRESENT));
            }
        }

        TEST_METHOD(ConcurrentSettersAndReaders)
        {
            RunScenario(L"concurrent");
        }

        TEST_METHOD(ContextRetainsRuntime)
        {
            RunScenario(L"lifetime");
        }
    };
}
