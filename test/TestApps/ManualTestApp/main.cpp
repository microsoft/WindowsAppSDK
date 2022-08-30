// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"

using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::Windows::AppLifecycle;

using namespace std::chrono;
using namespace AppModel::Identity;

HWND g_window = NULL;
wchar_t g_windowClass[] = L"TestWndClass"; // the main window class name
IVector<AppInstance> g_instances;

ATOM _RegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool NeedDynamicDependencies()
{
    return !IsPackagedProcess();
}

HRESULT BootstrapInitialize()
{
    if (!NeedDynamicDependencies())
    {
        return S_OK;
    }

    constexpr PCWSTR c_PackageNamePrefix{ L"WindowsAppRuntime.Test.DDLM" };
    constexpr PCWSTR c_PackagePublisherId{ L"8wekyb3d8bbwe" };
    constexpr PCWSTR c_FrameworkPackageFamilyName = L"Microsoft.WindowsAppRuntime.Framework-4.1_8wekyb3d8bbwe";
    constexpr PCWSTR c_MainPackageFamilyName = L"WindowsAppRuntime.Test.DynDep.DataStore-4.1_8wekyb3d8bbwe";
    RETURN_IF_FAILED(MddBootstrapTestInitialize(c_PackageNamePrefix, c_PackagePublisherId, c_FrameworkPackageFamilyName, c_MainPackageFamilyName));

    // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
    const UINT32 c_Version_MajorMinor{ 0x00040001 };
    const PACKAGE_VERSION minVersion{};
    RETURN_IF_FAILED(MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));

    return S_OK;
}

void BootstrapShutdown()
{
    if (!NeedDynamicDependencies())
    {
        return;
    }

    MddBootstrapShutdown();
}

IAsyncAction WaitForActivations()
{
    co_await 120000s;
    co_return;
}

void OnActivated(const winrt::Windows::Foundation::IInspectable&, const AppActivationArguments& args)
{
    if (args.Kind() == ExtendedActivationKind::Launch)
    {
        auto launchArgs = args.Data().as<ILaunchActivatedEventArgs>();
        wprintf(L"Activated via redirection with args: %s\n", launchArgs.Arguments().c_str());
    }

    SetForegroundWindow(g_window);
}

int main()
{
    init_apartment();

    THROW_IF_FAILED(BootstrapInitialize());

    bool isSingleInstanced = false;
    std::wstring key{ L"derp.txt" };
    AppInstance::Activated_revoker token;

    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    if (args.Kind() == ExtendedActivationKind::File)
    {
        auto fileArgs = args.Data().as<winrt::Windows::ApplicationModel::Activation::FileActivatedEventArgs>();
        key = fileArgs.Files().GetAt(0).Path();
        isSingleInstanced = true;
    }

    if (args.Kind() == ExtendedActivationKind::Launch)
    {
        auto launchArgs = args.Data().as<winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs>();
        std::wstring cmdLine{ launchArgs.Arguments() };
        auto c_testFileExtension{ L".alt" };
        if (cmdLine.rfind(L"/reg") != 0)
        {
            ActivationRegistrationManager::RegisterForFileTypeActivation({ c_testFileExtension },
                L"logo", L"Windows App SDK AppLifecycle Test File", { L"open" }, L"");
        }
        else if (cmdLine.rfind(L"/unreg") != 0)
        {
            ActivationRegistrationManager::UnregisterForFileTypeActivation({ c_testFileExtension }, L"");
        }
    }

    AppInstance keyInstance = AppInstance::FindOrRegisterForKey(key.c_str());
    if (isSingleInstanced && !keyInstance.IsCurrent())
    {
        keyInstance.RedirectActivationToAsync(args).get();
    }
    else
    {
        AppInstance thisInstance = AppInstance::GetCurrent();
        token = thisInstance.Activated(auto_revoke, [&thisInstance](const auto& sender, const AppActivationArguments& args)
            {
                OnActivated(sender, args);
            });

        auto hInstance = GetModuleHandle(NULL);
        _RegisterClass(hInstance);

        // Perform application initialization:
        if (!InitInstance(hInstance, SW_SHOWDEFAULT))
        {
            return 1;
        }

        // Main message loop:
        MSG msg;
        BOOL msgRet;
        while ((msgRet = GetMessage(&msg, NULL, 0, 0)) != 0)
        {
            if (msgRet == -1)
            {
                return (int)GetLastError();
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    BootstrapShutdown();
    return 0;
}

void RunGetInstancesTest()
{
    g_instances = AppInstance::GetInstances();
}

void RunRegisterKeyTest()
{
    auto instance = AppInstance::FindOrRegisterForKey(L"foo");
    THROW_IF_NULL_ALLOC(instance);
}

void RunUnregisterKeyTest()
{
    AppInstance::GetCurrent().UnregisterKey();
}

ATOM _RegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex = {};

    wcex.cbSize = sizeof(wcex);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.lpszClassName = g_windowClass;
    wcex.lpszMenuName = MAKEINTRESOURCE(IDM_FILE_MENU);

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    g_window = CreateWindow(g_windowClass, L"App Lifecycle Manual Test Application", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!g_window)
    {
        return FALSE;
    }

    ShowWindow(g_window, nCmdShow);
    UpdateWindow(g_window);
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDM_FILE_EXIT:
            PostQuitMessage(0);
            break;

        case IDM_FILE_GETINSTANCES:
            RunGetInstancesTest();
            break;

        case IDM_FILE_REGISTERINSTANCE:
            RunRegisterKeyTest();
            break;

        case IDM_FILE_UNREGISTERINSTANCE:
            RunUnregisterKeyTest();
            break;
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
