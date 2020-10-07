/*
* Copyright (c) Microsoft Corporation. All rights reserved.
*
* This File was generated using the VisualTAEF C++ Project Wizard.
* Class Name: DCPPHelixTest
*/
#include "StdAfx.h"
#include <WexTestClass.h>
#include <winuser.h>

using namespace WEX::Logging;
using namespace WEX::TestExecution;
// Global variables

// The main window class name.
static TCHAR szWindowClass[] = L"DesktopApp";

// The string that appears in the application's title bar.
static TCHAR szTitle[] = L"Windows Desktop Test Application";

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProc(LPVOID lpParameter);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = L"Hello, Windows desktop!";
    POINTER_INFO pointerInfo;
    WORD wPointerId = 0;
    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // Application is laid out as "Hello, Windows desktop!"
        // in the top left corner here.
        TextOut(hdc,
            5, 5,
            greeting, 23);
        // End application specific layout section.

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_POINTERDOWN:
        Log::Comment(L"Inject touch down successfully");
        wPointerId = LOWORD(wParam);
        VERIFY_WIN32_BOOL_SUCCEEDED(GetPointerInfo(wPointerId, &pointerInfo));
        VERIFY_ARE_EQUAL(pointerInfo.ptPixelLocation.x, 300);
        VERIFY_ARE_EQUAL(pointerInfo.ptPixelLocation.y, 200);
        break;
    case WM_POINTERUP:
        Log::Comment(L"Inject touch up Successfully");
        wPointerId = LOWORD(wParam);
        VERIFY_WIN32_BOOL_SUCCEEDED(GetPointerInfo(wPointerId, &pointerInfo));
        VERIFY_ARE_EQUAL(pointerInfo.ptPixelLocation.x, 300);
        VERIFY_ARE_EQUAL(pointerInfo.ptPixelLocation.y, 200);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

DWORD WINAPI ThreadProc(LPVOID /*lpParameter*/)
{
    WNDCLASSEX wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.lpszClassName = szWindowClass;

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            L"Call to RegisterClassEx failed!",
            L"Windows Desktop Test",
            NULL);

        return 1;
    }

    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 100,
        NULL,
        NULL,
        GetModuleHandle(nullptr),
        NULL
    );
    VERIFY_IS_NOT_NULL(hWnd);

    if (!hWnd)
    {
        MessageBox(NULL,
            L"Call to CreateWindow failed!",
            L"Windows Desktop Test",
            NULL);

        return 1;
    }

    ShowWindow(hWnd, SW_MAXIMIZE);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

namespace ProjectReunionHelix
{
    class HelixTest
    {
        BEGIN_TEST_CLASS(HelixTest)
            TEST_CLASS_PROPERTY(L"Owner", L"jorvan@microsoft.com")
            END_TEST_CLASS()
            BEGIN_TEST_METHOD(HelixPassedTest)
            TEST_METHOD_PROPERTY(L"Owner", L"jorvan@microsoft.com")
            TEST_METHOD_PROPERTY(L"RunAs", L"InteractiveUser")
            END_TEST_METHOD()
            BEGIN_TEST_METHOD(HelixFailedTest)
            TEST_METHOD_PROPERTY(L"Owner", L"jorvan@microsoft.com")
            END_TEST_METHOD()
    };

    void HelixTest::HelixPassedTest()
    {
        // Create win32 app.
        ::CreateThread(
            nullptr /* lpThreadAttributes */,
            0 /* dwStackSize */,
            ThreadProc,
            nullptr,
            0 /* dwCreationFlags */,
            nullptr);

        // Give application window enough time to setup and showup.
        Sleep(3000);

        VERIFY_WIN32_BOOL_SUCCEEDED(InitializeTouchInjection(10, TOUCH_FEEDBACK_DEFAULT));
        POINTER_TOUCH_INFO touchDown = { 0 };
        POINTER_TOUCH_INFO touchUp = { 0 };
        touchDown.pointerInfo.pointerType = touchUp.pointerInfo.pointerType = PT_TOUCH;
        touchDown.pointerInfo.pointerId = touchUp.pointerInfo.pointerId = 5;
        touchDown.pointerInfo.ptPixelLocation.x = touchUp.pointerInfo.ptPixelLocation.x = 300;
        touchDown.pointerInfo.ptPixelLocation.y = touchUp.pointerInfo.ptPixelLocation.y = 200;
        touchDown.pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INCONTACT | POINTER_FLAG_INRANGE;
        touchUp.pointerInfo.pointerFlags = POINTER_FLAG_UP;
        // Inject a dummy input to awake the window
        VERIFY_WIN32_BOOL_SUCCEEDED(InjectTouchInput(1, &touchDown));
        Sleep(20);
        VERIFY_WIN32_BOOL_SUCCEEDED(InjectTouchInput(1, &touchUp));
        Sleep(200);
        // Inject touch input
        VERIFY_WIN32_BOOL_SUCCEEDED(InjectTouchInput(1, &touchDown));
        Sleep(20);
        VERIFY_WIN32_BOOL_SUCCEEDED(InjectTouchInput(1, &touchUp));

        // Give window message enough time to execute and pop up result
        Sleep(2000);
    }
    void HelixTest::HelixFailedTest()
    {
        // Fail the test to enable the error saved files
        VERIFY_ARE_EQUAL(1, 2);
        Sleep(1000);
    }
} /* namespace DCPPHelix */
