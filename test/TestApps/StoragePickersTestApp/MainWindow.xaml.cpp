#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <roapi.h>
#include <filesystem>
#include <sstream>
#include <iomanip>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::StoragePickersTestApp::implementation
{
    // Get the directory where the EXE is located
    std::wstring GetApplicationDirectory()
    {
        wchar_t path[MAX_PATH];
        DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
        if (length == 0 || length == MAX_PATH)
        {
            throw winrt::hresult_error(HRESULT_FROM_WIN32(GetLastError()), L"Failed to get module filename");
        }
        std::filesystem::path exePath(path);
        return exePath.parent_path().wstring();
    }

    // Cached module handle
    static HMODULE s_hRuntimeModule = nullptr;
    typedef HRESULT(__stdcall* PFN_DllGetActivationFactory)(HSTRING, IActivationFactory**);
    static PFN_DllGetActivationFactory s_dllGetActivationFactory = nullptr;

    void EnsureRuntimeLoaded()
    {
        if (s_hRuntimeModule == nullptr)
        {
            std::wstring dllPath = GetApplicationDirectory() + L"\\Microsoft.WindowsAppRuntime.dll";
            s_hRuntimeModule = LoadLibraryExW(dllPath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
            if (!s_hRuntimeModule)
            {
                DWORD error = GetLastError();
                std::wstringstream ss;
                ss << L"Failed to load " << dllPath << L" (error: " << error << L")";
                throw winrt::hresult_error(HRESULT_FROM_WIN32(error), ss.str());
            }

            s_dllGetActivationFactory = reinterpret_cast<PFN_DllGetActivationFactory>(
                GetProcAddress(s_hRuntimeModule, "DllGetActivationFactory"));
            
            if (!s_dllGetActivationFactory)
            {
                std::wstringstream ss;
                ss << L"Failed to get DllGetActivationFactory from " << dllPath;
                throw winrt::hresult_error(HRESULT_FROM_WIN32(GetLastError()), ss.str());
            }
        }
    }

    // Helper to manually activate FileOpenPicker from our local Microsoft.WindowsAppRuntime.dll
    winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker CreateFileOpenPicker(
        winrt::Microsoft::UI::WindowId const& windowId)
    {
        EnsureRuntimeLoaded();

        // Get the activation factory for FileOpenPicker
        winrt::hstring className{ L"Microsoft.Windows.Storage.Pickers.FileOpenPicker" };
        winrt::com_ptr<IActivationFactory> baseFactory;
        HRESULT hr = s_dllGetActivationFactory(
            static_cast<HSTRING>(winrt::get_abi(className)), 
            baseFactory.put());
        
        if (FAILED(hr))
        {
            std::wstringstream ss;
            ss << L"DllGetActivationFactory failed (0x" << std::hex << static_cast<unsigned int>(hr) << L")";
            throw winrt::hresult_error(hr, ss.str());
        }

        // Query for IFileOpenPickerFactory using try_as
        auto pickerFactory = baseFactory.try_as<winrt::Microsoft::Windows::Storage::Pickers::IFileOpenPickerFactory>();
        
        if (!pickerFactory)
        {
            throw winrt::hresult_error(E_NOINTERFACE, L"Failed to get IFileOpenPickerFactory interface");
        }
        
        // Create the FileOpenPicker with the WindowId
        return pickerFactory.CreateInstance(windowId);
    }

    winrt::fire_and_forget MainWindow::OnPickFileClick(Windows::Foundation::IInspectable const& /*sender*/, RoutedEventArgs const& /*args*/)
    {
        auto strongThis = get_strong();

        try
        {
            // Create FileOpenPicker manually using our local DLL
            auto picker = CreateFileOpenPicker(this->AppWindow().Id());
            
            // Add file type filters
            picker.FileTypeFilter().Append(L"*");
            
            // Pick a single file
            auto result = co_await picker.PickSingleFileAsync();
            
            if (result)
            {
                FilePathTextBox().Text(result.Path());
            }
            else
            {
                FilePathTextBox().Text(L"No file selected (cancelled)");
            }
        }
        catch (winrt::hresult_error const& ex)
        {
            FilePathTextBox().Text(L"Error: " + ex.message());
        }
        catch (...)
        {
            FilePathTextBox().Text(L"Unknown error occurred");
        }
    }
}
