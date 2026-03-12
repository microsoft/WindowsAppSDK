// Validates Base package binplacement behavior for different configurations.
// EXPECT_NO_DLLS: No DLLs expected alongside the exe.
// EXPECT_BOOTSTRAP: Bootstrap DLL MUST be present alongside the exe.
#include <windows.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

int main()
{
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    fs::path exeDir = fs::path(exePath).parent_path();

    std::wcout << L"BasePackageTestCpp output dir: " << exeDir.wstring() << std::endl;

    std::vector<std::wstring> foundDlls;
    for (const auto& entry : fs::directory_iterator(exeDir))
    {
        if (entry.is_regular_file())
        {
            auto ext = entry.path().extension().wstring();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::towlower);
            if (ext == L".dll")
            {
                foundDlls.push_back(entry.path().filename().wstring());
            }
        }
    }

    std::wcout << L"DLLs found: " << foundDlls.size() << std::endl;
    for (const auto& dll : foundDlls)
    {
        std::wcout << L"  " << dll << std::endl;
    }

    int exitCode = 0;

#ifdef EXPECT_NO_DLLS
    std::wcout << L"\n[Expecting: no DLLs]" << std::endl;
    if (!foundDlls.empty())
    {
        std::wcerr << L"FAIL: No DLLs should be present alongside a SelfContained/Packaged exe." << std::endl;
        exitCode = 1;
    }
    else
    {
        std::wcout << L"PASS: No DLLs found alongside the exe." << std::endl;
    }
#elif defined(EXPECT_BOOTSTRAP)
    std::wcout << L"\n[Expecting: bootstrap DLL present]" << std::endl;
    bool foundBootstrap = false;
    for (const auto& dll : foundDlls)
    {
        auto lower = dll;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::towlower);
        if (lower == L"microsoft.windowsappruntime.bootstrap.dll")
        {
            foundBootstrap = true;
            break;
        }
    }
    if (!foundBootstrap)
    {
        std::wcerr << L"FAIL: Microsoft.WindowsAppRuntime.Bootstrap.dll not found alongside exe." << std::endl;
        exitCode = 1;
    }
    else
    {
        std::wcout << L"PASS: Bootstrap DLL is present as expected." << std::endl;
    }
#endif

    return exitCode;
}
