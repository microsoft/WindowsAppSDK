// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <KozaniManager_h.h>
#include "winrt/Microsoft.Kozani.ManagerRuntime.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace KozaniManagerTestPackage
{
    constexpr PCWSTR c_PackageDirName{ L"KozaniManager" };
    constexpr PCWSTR c_PackageFullName{ L"KozaniManager_1.0.0.0_neutral__8wekyb3d8bbwe" };
}

HRESULT RegisterDVCPluginIfNeeded()
{
    PCWSTR subkey{ L"Software\\Microsoft\\Terminal Server Client\\Default\\AddIns\\KozaniDVC" };
    PCWSTR keyname{ L"Name" };

    wil::unique_hkey key;
    const LSTATUS result{ ::RegOpenKey(HKEY_CURRENT_USER, subkey, &key) };
    if (result == ERROR_SUCCESS)
    {
        WEX::Logging::Log::Comment(L"DVC plugin key already exists!");
        return S_OK;
    }

    PCWSTR kozaniDvcClientClsid{ L"ed202fc8-ee21-4bf2-9681-23a8e97be9f3" };
    WCHAR regCommand[MAX_PATH];
    swprintf_s(regCommand, L"add \"HKCU\\%s\" /v %s /t REG_SZ /d {%s}", subkey, keyname, kozaniDvcClientClsid);
    const HINSTANCE hInst{ ShellExecute(nullptr, nullptr, L"reg.exe", regCommand, nullptr, SW_SHOW) };
    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"ShellExecute reg add finished with code: %d", hInst));

    if ((int)hInst > 32)
    {
        WEX::Logging::Log::Comment(L"Successfully created DVC plugin key!");
    }
    else
    {
        const HRESULT hr{ HRESULT_FROM_WIN32(reinterpret_cast<DWORD>(hInst)) };
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"ShellExecute failed with: 0x%x", hr));
        return hr;
    }

    return S_OK;
}

namespace Test::KozaniManagerRuntimeTests
{
    struct MyKozaniStatusCallback : winrt::implements<MyKozaniStatusCallback, IKozaniStatusCallback, winrt::Windows::Foundation::IInspectable>
    {
#pragma region IKozaniStatusCallback_methods
        STDMETHODIMP OnActivated(DWORD pid, boolean isNewInstance)
        {
            WEX::Logging::Log::Comment(WEX::Common::String().Format(
                L"IKozaniStausCallback::OnActivated is called. pid = %u, isNewInstance = %s", pid, isNewInstance ? L"true" : L"false"));
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
            ::TP::RemovePackageIfNecessary(KozaniManagerTestPackage::c_PackageFullName);
            ::TB::Setup();
            ::TP::AddPackage(KozaniManagerTestPackage::c_PackageDirName, KozaniManagerTestPackage::c_PackageFullName);
            
            if (FAILED(RegisterDVCPluginIfNeeded()))
            {
                return false;
            }
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TP::RemovePackageIfNecessary(KozaniManagerTestPackage::c_PackageFullName);
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(ActivateRemoteApplication_NegativeTests)
        {
            auto runtimeManager{ winrt::Microsoft::Kozani::ManagerRuntime::ManagerRuntimeManager::Create() };
            auto statusCallback{ winrt::make_self<MyKozaniStatusCallback>() };

            WEX::Common::String testDeploymentDir;
            VERIFY_SUCCEEDED(WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", testDeploymentDir));

            // Negative test case 1: connection RDP file does not exist.
            try
            {
                runtimeManager.ActivateRemoteApplication(winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch,
                    L"Microsoft.WindowsCalculator_8wekyb3d8bbwe!App", L"Non-existing.rdp", 0, 
                    nullptr,    // IActivatedEventArgs
                    statusCallback.as<winrt::Windows::Foundation::IInspectable>(),
                    L"additionalSettings.txt");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(e.code().value, HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));
            }

            // Negative test case 2: connection RDP file does not contain connection Id.
            try
            {
                std::filesystem::path rdpFullPath((const wchar_t*)testDeploymentDir);
                rdpFullPath.append(L"MissingConnectionId.rdp");

                runtimeManager.ActivateRemoteApplication(winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch,
                    L"Microsoft.WindowsCalculator_8wekyb3d8bbwe!App", rdpFullPath.c_str(), 0, 
                    nullptr,    // IActivatedEventArgs
                    statusCallback.as<winrt::Windows::Foundation::IInspectable>(),
                    L"additionalSettings.txt");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(e.code().value, E_INVALIDARG);
            }
        }

        TEST_METHOD(ActivateRemoteApplication_Launch)
        {
            auto runtimeManager{ winrt::Microsoft::Kozani::ManagerRuntime::ManagerRuntimeManager::Create() };
            auto statusCallback{ winrt::make_self<MyKozaniStatusCallback>() };

            WEX::Common::String testDeploymentDir;
            VERIFY_SUCCEEDED(WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", testDeploymentDir));
            std::filesystem::path rdpFullPath((const wchar_t*)testDeploymentDir);
            rdpFullPath.append(L"connection.rdp");

            runtimeManager.ActivateRemoteApplication(winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch,
                L"Microsoft.WindowsCalculator_8wekyb3d8bbwe!App", rdpFullPath.c_str(), 0, 
                nullptr,    // IActivatedEventArgs
                statusCallback.as<winrt::Windows::Foundation::IInspectable>(),
                winrt::param::hstring());
        }
    };
}
