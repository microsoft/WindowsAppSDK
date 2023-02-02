// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <KozaniManager_h.h>
#include "winrt/Microsoft.Kozani.ManagerRuntime.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace KozaniManagerTestPackage
{
    constexpr PCWSTR c_PackageDirName = L"KozaniManager";
    constexpr PCWSTR c_PackageFullName = L"KozaniManager_1.0.0.0_neutral__8wekyb3d8bbwe";
}

namespace Test::KozaniManagerRuntimeTests
{
    struct MyKozaniStatusCallback : winrt::implements<MyKozaniStatusCallback, IKozaniStatusCallback, winrt::Windows::Foundation::IInspectable>
    {
#pragma region IKozaniStatusCallback_methods
        STDMETHODIMP OnActivated(DWORD pid)
        {
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"IKozaniStausCallback::OnActivated is called. pid = %u", pid));
            m_isActivated = true;
            return S_OK;
        }

        STDMETHODIMP OnActivationFailed(
            DWORD errorCode,
            PCWSTR errorMessage)
        {
            WEX::Logging::Log::Comment(
                WEX::Common::String().Format(L"IKozaniStausCallback::OnActivationFailed is called. errorCode = 0x%x, errorMessage: %s",
                    errorCode, errorMessage));
            m_isActivationFailed = true;
            return S_OK;
        }

        STDMETHODIMP OnClosed()
        {
            WEX::Logging::Log::Comment(L"IKozaniStausCallback::OnClosed is called.");
            m_isClosed = true;
            return S_OK;
        }
#pragma endregion IKozaniStatusCallback_methods

        bool IsActivated()
        {
            return m_isActivated;
        }

        bool IsActivationFailed()
        {
            return m_isActivationFailed;
        }

        bool IsClosed()
        {
            return m_isClosed;
        }

    private:
        bool m_isActivated{};
        bool m_isActivationFailed{};
        bool m_isClosed{};
    };

    class KozaniManagerRuntimeTests
    {
    public:
        BEGIN_TEST_CLASS(KozaniManagerRuntimeTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            ::TB::Setup();
            ::TP::AddPackage(KozaniManagerTestPackage::c_PackageDirName, KozaniManagerTestPackage::c_PackageFullName);
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TP::RemovePackageIfNecessary(KozaniManagerTestPackage::c_PackageFullName);
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(ActivateRemoteApplication_Launch)
        {
            auto runtimeManager{ winrt::Microsoft::Kozani::ManagerRuntime::ManagerRuntimeManager::Create() };
            auto statusCallback{ winrt::make_self<MyKozaniStatusCallback>() };

            runtimeManager.ActivateRemoteApplication(winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch,
                L"Microsoft.WindowsCalculator_8wekyb3d8bbwe!App", L"c:\\data\\connection.rdp", L"c:\\data\\additionalSettings.txt",
                nullptr,    // IActivatedEventArgs
                statusCallback.as<winrt::Windows::Foundation::IInspectable>());

            VERIFY_IS_TRUE(statusCallback->IsActivated(), L"IKozaniStausCallback::OnActivated() should have been called.");
        }
    };
}
