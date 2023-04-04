// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <iostream>
#include <KozaniManager_h.h>
#include "winrt/Microsoft.Kozani.ManagerRuntime.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace KozaniManagerTestPackage
{
    constexpr PCWSTR c_PackageDirName = L"KozaniManager";
    constexpr PCWSTR c_PackageFullName = L"KozaniManager_1.0.0.0_neutral__8wekyb3d8bbwe";
}

namespace Test::KozaniManagerRuntime::ManualTests
{
    enum KozaniStatus
    {
        None = 0,
        Activated = 1,
        Failed = 2,
        Closed = 3
    };

    struct MyKozaniStatusCallback : winrt::implements<MyKozaniStatusCallback, IKozaniStatusCallback, winrt::Windows::Foundation::IInspectable>
    {
        MyKozaniStatusCallback(std::wstring& aumid)
        {
            m_aumid = aumid;
            m_eventStatusUpdate.create();
        }

#pragma region IKozaniStatusCallback_methods
        STDMETHODIMP OnActivated(DWORD pid, boolean isNewInstance)
        {
            WEX::Logging::Log::Comment(WEX::Common::String().Format(
                L"\nIKozaniStausCallback::OnActivated is called. Remote app aumid = %s, pid = %u, isNewInstance = %s", 
                m_aumid.c_str(), pid, isNewInstance ? L"true" : L"false"));
            m_status = KozaniStatus::Activated;
            m_eventStatusUpdate.SetEvent();
            return S_OK;
        }

        STDMETHODIMP OnActivationFailed(
            DWORD errorCode,
            PCWSTR errorMessage)
        {
            WEX::Logging::Log::Comment(
                WEX::Common::String().Format(L"\nIKozaniStausCallback::OnActivationFailed is called. Remote app aumid = %s, errorCode = 0x%x, errorMessage: %s",
                    m_aumid.c_str(), errorCode, errorMessage));
            m_status = KozaniStatus::Failed;
            m_eventStatusUpdate.SetEvent();
            return S_OK;
        }

        STDMETHODIMP OnClosed()
        {
            WEX::Logging::Log::Comment(L"\nIKozaniStausCallback::OnClosed is called. Remote app aumid = %s", m_aumid.c_str());
            m_status = KozaniStatus::Closed;
            m_eventStatusUpdate.SetEvent();
            return S_OK;
        }
#pragma endregion IKozaniStatusCallback_methods

        bool WaitForStatusUpdate(DWORD timeout)
        {
            return m_eventStatusUpdate.wait(timeout);
        }

        KozaniStatus GetStatus()
        {
            return m_status;
        }

    private:
        std::wstring m_aumid;
        KozaniStatus m_status{};
        wil::unique_event m_eventStatusUpdate;
    };

    class KozaniManagerRuntimeManualTests
    {
    private:
        bool m_testsEnabled{};

    public:
        BEGIN_TEST_CLASS(KozaniManagerRuntimeManualTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            // To run manual tests, add the following commandline paramater to te.exe: /p:EnableManualTests=true
            HRESULT hr{ WEX::TestExecution::RuntimeParameters::TryGetValue(L"EnableManualTests", m_testsEnabled) };
            if (hr == HRESULT_FROM_WIN32(ERROR_NOT_FOUND) || !m_testsEnabled)
            {
                WEX::Logging::Log::Comment(L"Skipped ClassSetup - manual tests not enabled.");
                return true;
            }

            ::TB::Setup();
            ::TP::AddPackageIfNecessary(KozaniManagerTestPackage::c_PackageDirName, KozaniManagerTestPackage::c_PackageFullName);

            if (FAILED(RegisterDVCPluginIfNeeded()))
            {
                return false;
            }
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            if (!m_testsEnabled)
            {
                WEX::Logging::Log::Comment(L"Skipped ClassCleanup - manual tests not enabled.");
                return true;
            }

            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(InteractiveRemoteAppLaunch)
        {
            if (!m_testsEnabled)
            {
                WEX::Logging::Log::Comment(L"Skipped InteractiveRemoteAppLaunch - manual tests not enabled.");
                return;
            }

            std::cout << "\n\n\n\nThis app allows you to launch remote apps.\n";
            auto runtimeManager{ winrt::Microsoft::Kozani::ManagerRuntime::ManagerRuntimeManager::Create() };

            while (true)
            {
                std::cout << "Enter command (launch or quit): ";
                std::string command;
                std::cin >> command;

                if (command == "launch")
                {
                    std::cout << "Enter AUMID of the remote app to launch (eg., Microsoft.WindowsCalculator_8wekyb3d8bbwe!App): ";
                    std::wstring aumid;
                    std::wcin >> aumid;
                    std::cout << "Enter full path of the connection RDP file: ";
                    std::wstring rdpFullPath;
                    std::wcin >> rdpFullPath;

                    // Special handling of path wrapped with "" (like paths from "Copy path" menu of file explorer) - remove the "".
                    if (rdpFullPath.front() == L'\"')
                    {
                        rdpFullPath.erase(rdpFullPath.begin());
                    }
                    if (rdpFullPath.back() == L'\"')
                    {
                        rdpFullPath.pop_back();
                    }

                    auto statusCallback{ winrt::make_self<MyKozaniStatusCallback>(aumid) };

                    try
                    {
                        runtimeManager.ActivateRemoteApplication(
                            winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch,
                            aumid.c_str(), rdpFullPath.c_str(), winrt::param::hstring(),
                            nullptr,    // IActivatedEventArgs
                            statusCallback.as<winrt::Windows::Foundation::IInspectable>());
                    }
                    catch (winrt::hresult_error& e)
                    {
                        WEX::Logging::Log::Error(WEX::Common::String().Format(
                            L"\nActivateRemoteApplication failed. errorCode = 0x%x, errorMessage: %s",
                            e.code(), e.message().c_str()));

                        continue;
                    }

                    const DWORD waitTime = 20 * 1000;
                    bool wait{};
                    do
                    {
                        std::cout << "Waiting for remote app activation to finish. Time out in " << waitTime / 1000 << " seconds\n";
                        if (!statusCallback->WaitForStatusUpdate(waitTime))
                        {
                            std::cout << "Wait timed out. App activation takes too long to finish.\n";
                            bool askYesOrNo{};
                            do
                            {
                                std::cout << "Continue to wait? (y/n) ";
                                char yesOrNo{};
                                std::cin >> yesOrNo;
                                switch (yesOrNo)
                                {
                                    case 'y':
                                        wait = true;
                                        askYesOrNo = false;
                                        break;

                                    case 'n':
                                        wait = false;
                                        askYesOrNo = false;
                                        break;

                                    default:
                                        askYesOrNo = true;
                                }
                            }
                            while (askYesOrNo);
                        }
                        else
                        {
                            wait = false;
                            if (statusCallback->GetStatus() == KozaniStatus::Activated)
                            {

                            }
                        }
                    }
                    while (wait);
                }
                else if (command == "close")
                {

                }
                else if (command == "quit")
                {
                    break;
                }
                else
                {
                    std::cout << "Invalid command!\n";
                }
            }
        }
    };
}
