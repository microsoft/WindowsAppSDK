// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

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

#include <MddBootstrap.h>

#include <Wex.Logger.h>
#include <WexString.h>
#include <WexTestClass.h>
#include <LogController.h>

namespace TB = ::Test::Bootstrap;
namespace TF = ::Test::FileSystem;

wil::unique_hmodule Setup();
void Dump();
HRESULT VerifyRoActivateInstance();
HRESULT VerifyRoGetActivationFactory();
HRESULT Test_Activation();
HRESULT Test_Metadata();
bool IsTaefLoggingEnabled();
HRESULT TaefInitializeLogging(const std::wstring& taefConnectionData);
void TaefLog(PCWSTR message);
void LogError(PCWSTR message);
void LogComment(PCWSTR message);
int Help();
HRESULT ParseCommandLine(int argc, wchar_t* argv[], std::wstring& taefConnectionData, bool& testActivation, bool& testMetadata);

// Setup our logging to route through our calling TAEF test's log
// See https://www.osgwiki.com/wiki/WexLogger#Remote_Logging_From_Child_Processes
// or https://docs.microsoft.com/en-us/windows-hardware/drivers/taef/wexlogger#remote-logging-from-child-processes
std::wstring g_taefConnectionData{};

wil::unique_hmodule Setup()
{
    Dump();

#if !defined(MICROSOFT_WINDOWSAPPSDK_SELFCONTAINED)
    LogComment(WEX::Common::String().Format(L"::TB::SetupBootstrap()..."));
    ::TB::SetupBootstrap();
    LogComment(WEX::Common::String().Format(L"::TB::SetupBootstrap(): Done"));
#if 0 //DELETEME
    const auto majorMinor{ ::Microsoft::WindowsAppSDK::Release::MajorMinor };
    const auto versionTag{ ::Microsoft::WindowsAppSDK::Release::VersionTag };
    const ::Microsoft::Windows::ApplicationModel::PackageVersion minVersion{ ::Microsoft::WindowsAppSDK::Runtime::Version::UInt64 };
    const auto options{ MddBootstrap::InitializeOptions::OnError_FailFast |
                        MddBootstrap::InitializeOptions::OnError_DebugBreak_IfDebuggerAttached };
    const auto message{ WEX::Common::String().Format(L"Bootstrap.Initialize(0x%08X, '%s', %s, 0x%X)",
                                                     majorMinor, !versionTag ? L"<null>" : versionTag, minVersion.ToString().c_str(), options) };
    LogComment(message);
    const auto hr{ MddBootstrap::InitializeNoThrow(majorMinor, versionTag, minVersion, options) };
    LogComment(WEX::Common::String().Format(L"%s: 0x%X", static_cast<PCWSTR>(message), hr));
    THROW_IF_FAILED_MSG(hr, "%ls", static_cast<PCWSTR>(message));
#endif //DELETEME
#endif

    const auto dllFilename{ L"Microsoft.WindowsAppRuntime.dll" };
    wil::unique_hmodule dll{ LoadLibraryExW(dllFilename, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH) };
    const auto lastError{ GetLastError() };
    LogComment(WEX::Common::String().Format(L"LoadLibraryEx('%s'): %p  LastError:0x%X", dllFilename, dll.get(), lastError));
    THROW_HR_IF_NULL(HRESULT_FROM_WIN32(lastError), dll);
    auto moduleFileName{ wil::GetModuleFileNameW(dll.get()) };
    LogComment(WEX::Common::String().Format(L"ModuleFileName: %s", moduleFileName.get()));
    return dll;
}

void Dump()
{
    LogComment(WEX::Common::String().Format(L"MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE is%s defined\n", c_buildIsBootstrapAutoInitialize ? L"" : L" NOT"));
    LogComment(WEX::Common::String().Format(L"MICROSOFT_WINDOWSAPPSDK_SELFCONTAINED is%s defined\n", c_buildIsSelfContained ? L"" : L" NOT"));
    LogComment(WEX::Common::String().Format(L"MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE is%s defined\n", c_buildIsUndockedRegFreeWinRTAutoInitialize ? L"" : L" NOT"));
    LogComment(WEX::Common::String().Format(L"MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE_LOADLIBRARY is%s defined\n", c_buildIsUndockedRegFreeWinRTAutoInitializeLoadLibrary ? L"" : L" NOT"));

    auto pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH") };
    auto pathEnvironmentVariableString{ !pathEnvironmentVariable ? L"<null>" : pathEnvironmentVariable.get() };
    LogComment(WEX::Common::String().Format(L"PATH: %s\n", pathEnvironmentVariableString));

    wchar_t currentDirectory[1024]{};
    auto currentDirectoryLength{ GetCurrentDirectoryW(ARRAYSIZE(currentDirectory), currentDirectory) };
    THROW_LAST_ERROR_IF(currentDirectoryLength == 0);
    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), currentDirectoryLength > ARRAYSIZE(currentDirectory));
    LogComment(WEX::Common::String().Format(L"CurrentDirectory: %s", currentDirectory));

    auto exeFileName{ wil::GetModuleFileNameW() };
    LogComment(WEX::Common::String().Format(L"ExeFileName: %s", exeFileName.get()));
}

HRESULT VerifyRoActivateInstance() try
{
    LogComment(L"Verify:RoActivateInstance...");

    // Keep in sync with app.manifest
    PCWSTR acids[]{
        L"Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions",
        L"Microsoft.Windows.Management.Deployment.PackageSet"
    };
    for (auto acid : acids)
    {
        LogComment(WEX::Common::String().Format(L"ACID: %s", acid));
        auto hacid{ wil::make_unique_string<wil::unique_hstring>(acid) };
        wil::com_ptr_nothrow<IInspectable> inspectable;
        const auto hr{ RoActivateInstance(hacid.get(), &inspectable) };
        LogComment(WEX::Common::String().Format(L"  HRESULT: 0x%X  Ptr: %p  RoActivateInstance: %s", hr, inspectable.get(), acid));
        RETURN_IF_FAILED_MSG(hr, "RoActivateInstance: %ls", acid);
    }

    LogComment(L"Verify:RoActivateInstance...OK!");
    return S_OK;
}
CATCH_RETURN()

HRESULT VerifyRoGetActivationFactory() try
{
    LogComment(L"Verify:RoGetAtivationFactory...");

    PCWSTR factoryAcids[]{
        L"Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency",
        L"Microsoft.Windows.Management.Deployment.PackageDeploymentManager"
    };
    for (auto acid : factoryAcids)
    {
        LogComment(WEX::Common::String().Format(L"ACID: %s", acid));
        auto hacid{ wil::make_unique_string<wil::unique_hstring>(acid) };
        wil::com_ptr_nothrow<IInspectable> inspectable;
        const auto hr{ RoGetActivationFactory(hacid.get(), __uuidof(inspectable), (void**)&inspectable) };
        LogComment(WEX::Common::String().Format(L"  HRESULT: 0x%X  Ptr: %p  RoGetActivationFactory: %s", hr, inspectable.get(), acid));
        RETURN_IF_FAILED_MSG(hr, "RoGetActivationFactory: %ls", acid);
    }

    LogComment(L"Verify:RoGetAtivationFactory...OK!");
    return S_OK;
}
CATCH_RETURN()

HRESULT Test_Activation() try
{
    LogComment(L"Test_Activation...");
    RETURN_IF_FAILED(VerifyRoActivateInstance());
    RETURN_IF_FAILED(VerifyRoGetActivationFactory());
    LogComment(L"Test_Activation...OK!");
    return S_OK;
}
CATCH_RETURN()

HRESULT VerifyApiInformationIsContractPresent() try
{
    LogComment(L"Verify:ApiInformation.IsContractPresent...");

#if 0 //DELETEME
    auto apiInformationStatics{
        wil::GetActivationFactory<
            ABI::Windows::Foundation::Metadata::IApiInformationStatics>(
                RuntimeClass_Windows_Foundation_Metadata_ApiInformation) };
#endif //DELETEME

    struct Contracts
    {
        PCWSTR name;
        uint16_t majorVersion;
    } contracts[]{
        { L"Windows.Foundation.UniversalApiContract",                                        1 },
        { L"Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract", 1 },
        { L"Microsoft.Windows.AppLifecycle.AppLifecycleContract",                            1 },
        { L"Microsoft.Windows.AppLifecycle.AppLifecycleContract",                            2 },
        { L"Microsoft.Windows.Management.Deployment.PackageDeploymentContract",              1 }
    };
    for (auto contract : contracts)
    {
        LogComment(WEX::Common::String().Format(L"Contract: %s v%hu", contract.name, contract.majorVersion));
        const winrt::hstring contractName{ contract.name };
        boolean found{};
        HRESULT hr{};
        try
        {
#if 1
            BOOL present{};
            hr = LOG_IF_FAILED(::RoIsApiContractMajorVersionPresent(contract.name, contract.majorVersion, &present));
            found = !!present;
#else
            found = winrt::Windows::Foundation::Metadata::ApiInformation::IsApiContractPresent(contractName, contract.majorVersion);
#endif
            if (found)
            {
                LogComment(WEX::Common::String().Format(L"  HRESULT: 0x%X  Found  IsContractPresent: %s v%hu", hr, contract.name, contract.majorVersion));
            }
            else
            {
                LogError(WEX::Common::String().Format(L"  HRESULT: 0x%X  **NOT-FOUND**  IsContractPresent: %s v%hu", hr, contract.name, contract.majorVersion));
            }
#if 0 //DELETEME
            const auto hr{ apiInformationStatics->IsApiContractPresentByMajor(contractName.get(), contract.majorVersion, &found) };
#endif //DELETEME
        }
        catch (winrt::hresult_error& e)
        {
            hr = e.code();
            LogError(WEX::Common::String().Format(L"  HRESULT: 0x%X  IsContractPresent: %s v%hu", hr, contract.name, contract.majorVersion));
        }
        RETURN_IF_FAILED_MSG(hr, "ApiInformation.IsContractPresent: %ls v%hu", contract.name, contract.majorVersion);
        RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !found, "ApiInformation.IsContractPresent: %ls v%hu", contract.name, contract.majorVersion);
    }

    LogComment(L"Verify:ApiInformation.IsContractPresent...OK!");
    return S_OK;
}
CATCH_RETURN()

HRESULT VerifyApiInformationIsTypePresent() try
{
    LogComment(L"Verify:ApiInformation.IsTypePresent...");

#if 0 //DELETEME
    auto apiInformationStatics{
        wil::GetActivationFactory<
            ABI::Windows::Foundation::Metadata::IApiInformationStatics>(
                RuntimeClass_Windows_Foundation_Metadata_ApiInformation) };
#endif //DELETEME

    PCWSTR types[]{
        L"Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions",
        L"Microsoft.Windows.System.EnvironmentManager",
        L"Microsoft.Windows.Management.Deployment.PackageDeploymentManager"
    };
    for (auto type : types)
    {
        LogComment(WEX::Common::String().Format(L"Type: %s", type));
        const winrt::hstring htype{ type };
        boolean found{};
        HRESULT hr{};
        try
        {
            found = winrt::Windows::Foundation::Metadata::ApiInformation::IsTypePresent(htype);
            if (found)
            {
                LogComment(WEX::Common::String().Format(L"  HRESULT: 0x%X  Found  IsTypePresent: %s", hr, type));
            }
            else
            {
                LogError(WEX::Common::String().Format(L"  HRESULT: 0x%X  **NOT-FOUND**  IsTypePresent: %s", hr, type));
            }
#if 0 //DELETEME
            const auto hr{ apiInformationStatics->IsTypePresent(htype.get(), &found) };
#endif //DELETEME
        }
        catch (winrt::hresult_error& e)
        {
            hr = e.code();
            LogError(WEX::Common::String().Format(L"  HRESULT: 0x%X  IsTypePresent: %s", hr, type));
        }
        RETURN_IF_FAILED_MSG(hr, "ApiInformation.IsTypePresent: %ls", type);
        RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !found, "ApiInformation.IsTypePresent: %ls", type);
    }

    LogComment(L"Verify:ApiInformation.IsTypePresent...OK!");
    return S_OK;
}
CATCH_RETURN()

HRESULT Test_Metadata() try
{
    LogComment(L"Test_Metadata...");
    RETURN_IF_FAILED(VerifyApiInformationIsContractPresent());
    RETURN_IF_FAILED(VerifyApiInformationIsTypePresent());
    LogComment(L"Test_Metadata...OK!");
    return S_OK;
}
CATCH_RETURN()

bool IsTaefLoggingEnabled()
{
    return !g_taefConnectionData.empty();
}

HRESULT TaefInitializeLogging(const std::wstring& taefConnectionData)
{
    wprintf(L"TAEFConnectionData: %s\n", taefConnectionData.c_str());
    if (taefConnectionData.empty())
    {
        return S_OK;
    }

    auto taefEnvironmentVariableCommand{ WEX::Common::String(WEX::Logging::c_szWexLoggerRemoteConnectionData).Append(taefConnectionData.c_str()) };
    PCWSTR c_environmentVariable{ L"urfw_exeusingwinappsdk_cmd" };
    wprintf(L"Setting environment variable %s=%s\n", c_environmentVariable, static_cast<PCWSTR>(taefEnvironmentVariableCommand));
    RETURN_IF_WIN32_BOOL_FALSE(::SetEnvironmentVariableW(c_environmentVariable, taefEnvironmentVariableCommand));

    g_taefConnectionData = taefConnectionData;
    RETURN_IF_FAILED(WEX::Logging::LogController::InitializeLogging(g_taefConnectionData.c_str()));
    return S_OK;
}

void TaefLog(PCWSTR message)
{
    if (IsTaefLoggingEnabled())
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"URFW_EXE: %s", message));
    }
}

void LogError(PCWSTR message)
{
    std::fputws(WEX::Common::String().Format(L"%s\n", message), stdout);
    TaefLog(message);
}

void LogComment(PCWSTR message)
{
    std::fputws(WEX::Common::String().Format(L"%s\n", message), stdout);
    TaefLog(message);
}

int Help()
{
    wprintf(L"Usage: URFW_ExeUsingWinAppSDK.exe [options] [test [test...]]\n"
            L"options:\n"
            L"                     --help, -? ==> Display help\n"
            L"   --taef:connectiondata=<data> ==> TAEF connection data for remote logging\n"
            L"                             -- ==> End options\n"
            L"test (omit to run all):\n"
            L"  Activation\n"
            L"  Metadata\n");
    ExitProcess(1);
}

HRESULT ParseCommandLine(int argc, wchar_t* argv[], std::wstring& taefConnectionData, bool& testActivation, bool& testMetadata)
{
    int argn = 1;
    std::wstring arg;
    for (; argn < argc; ++argn)
    {
        arg = argv[argn];
        if (arg[0] != L'-')
        {
            break;
        }
        if (arg == L"--")
        {
            ++argn;
            break;
        }
        else if ((arg == L"--help") || (arg == L"-?"))
        {
            Help();
        }
        else if (arg.rfind(L"--taef:connectiondata=", 0) == 0)
        {
            const auto c_taefConnectionDataLength{ ARRAYSIZE(L"--taef:connectiondata=") - 1 };
            taefConnectionData = arg.substr(c_taefConnectionDataLength);

            // We expect valid TAEF connection data e.g. "{LogManagerGuid=4E46F9E4-B8A3-4258-B5DF-20A959332795,LogSessionId=1}"
            if (taefConnectionData.empty() || (taefConnectionData[0] != L'{'))
            {
                wprintf(L"ERROR: Invalid parameter argv[%d]: %s, aborting...\n", argn, arg.c_str());
                ExitProcess(LOG_HR_MSG(E_INVALIDARG, "argv[%d]: %s", argn, arg.c_str()));
            }
        }
        else
        {
            wprintf(L"ERROR: Invalid parameter argv[%d]: %s, aborting...\n", argn, arg.c_str());
            ExitProcess(LOG_HR_MSG(E_INVALIDARG, "argv[%d]: %s", argn, arg.c_str()));
        }
    }

    if (argn >= argc)
    {
        testActivation = true;
        testMetadata = true;
    }
    else
    {
        for (; argn < argc; ++argn)
        {
            PCWSTR argp{ argv[argn] };
            if (CompareStringOrdinal(argp, -1, L"Activation", -1, TRUE) == CSTR_EQUAL)
            {
                testActivation = true;
            }
            else if (CompareStringOrdinal(argp, -1, L"Metadata", -1, TRUE) == CSTR_EQUAL)
            {
                testMetadata = true;
            }
            else
            {
                wprintf(L"ERROR: Invalid parameter argv[%d]: %s, aborting...\n", argn, argp);
                ExitProcess(LOG_HR_MSG(E_INVALIDARG, "argv[%d]: %s", argn, argp));
            }
        }
    }
    return S_OK;
}

int wmain(int argc, wchar_t *argv[]) try
{
    PCWSTR commandLine{ ::GetCommandLineW() };
    wprintf(L"CommandLine: %s\n", (!commandLine ? L"<null>" : commandLine));
    for (int argn = 0; argn < argc; ++argn)
    {
        wprintf(L"argv[%d]: %s\n", argn, argv[argn]);
    }

    WCHAR envvalue[1024]{};
    ::GetEnvironmentVariableW(L"urfw_exeusingwinappsdk_cmd", envvalue, ARRAYSIZE(envvalue));
    wprintf(L"env: %s\n", envvalue);

    wil::SetResultLoggingCallback([](wil::FailureInfo const& failure) noexcept
    {
        constexpr std::size_t sizeOfLogMessageWithNul{ 2048 };
        wchar_t logMessage[sizeOfLogMessageWithNul]{};
        if (SUCCEEDED(wil::GetFailureLogString(logMessage, sizeOfLogMessageWithNul, failure)))
        {
            LogError(logMessage);
        }
    });

	auto roinit{ wil::RoInitialize() };

    std::wstring taefConnectionData;
    bool testActivation{};
    bool testMetadata{};
	RETURN_IF_FAILED(ParseCommandLine(argc, argv, taefConnectionData, testActivation, testMetadata));

    RETURN_IF_FAILED(TaefInitializeLogging(taefConnectionData));
    auto taefFinalizeLogging = wil::scope_exit([&]
    {
            if (IsTaefLoggingEnabled())
            {
                (void)LOG_IF_FAILED(WEX::Logging::LogController::FinalizeLogging());
            }
    });

	auto dll{ Setup() };

    if (testActivation)
    {
        RETURN_IF_FAILED(Test_Activation());
    }
    if (testMetadata)
    {
        RETURN_IF_FAILED(Test_Metadata());
    }

#if !defined(MICROSOFT_WINDOWSAPPSDK_SELFCONTAINED)
    LogComment(WEX::Common::String().Format(L"::TB::CleanupBootstrap()..."));
    ::TB::CleanupBootstrap();
    LogComment(WEX::Common::String().Format(L"::TB::SetupBootstrap(): Done"));
#endif

    LogComment(WEX::Common::String().Format(L"Success!"));
    return 0;
}
CATCH_RETURN()
