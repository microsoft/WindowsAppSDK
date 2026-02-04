// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "StoragePickersActivation.h"
#include <filesystem>
#include <roapi.h>
#include <wil/result_macros.h>

namespace StoragePickersTestApp
{
    // Static member initialization
    HMODULE StoragePickersActivation::s_hRuntimeModule = nullptr;
    void* StoragePickersActivation::s_dllGetActivationFactory = nullptr;

    namespace
    {
        std::wstring GetApplicationDirectory()
        {
            wchar_t path[MAX_PATH];
            DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
            THROW_LAST_ERROR_IF(length == 0 || length == MAX_PATH);
            return std::filesystem::path(path).parent_path().wstring();
        }

        using PFN_DllGetActivationFactory = HRESULT(__stdcall*)(HSTRING, ::IActivationFactory**);
    }

    void StoragePickersActivation::EnsureRuntimeLoaded()
    {
        if (s_hRuntimeModule != nullptr)
        {
            return;
        }

        // Load our locally-built Microsoft.WindowsAppRuntime.dll (not the system one)
        std::wstring dllPath = GetApplicationDirectory() + L"\\Microsoft.WindowsAppRuntime.dll";
        s_hRuntimeModule = LoadLibraryExW(dllPath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
        THROW_LAST_ERROR_IF_NULL_MSG(s_hRuntimeModule, "Failed to load local Microsoft.WindowsAppRuntime.dll");

        s_dllGetActivationFactory = GetProcAddress(s_hRuntimeModule, "DllGetActivationFactory");
        THROW_LAST_ERROR_IF_NULL_MSG(s_dllGetActivationFactory, "Failed to get DllGetActivationFactory");
    }

    template<typename TFactory, typename TPicker>
    TPicker StoragePickersActivation::CreatePicker(
        winrt::Microsoft::UI::WindowId const& windowId, 
        const wchar_t* className)
    {
        EnsureRuntimeLoaded();

        // Get the activation factory
        winrt::hstring activatableClassId{ className };
        winrt::com_ptr<::IActivationFactory> baseFactory;
        
        auto getFactory = reinterpret_cast<PFN_DllGetActivationFactory>(s_dllGetActivationFactory);
        HRESULT hr = getFactory(
            static_cast<HSTRING>(winrt::get_abi(activatableClassId)),
            baseFactory.put());
        THROW_IF_FAILED_MSG(hr, "DllGetActivationFactory failed for %ls", className);

        // Query for the specific factory interface
        auto factory = baseFactory.try_as<TFactory>();
        THROW_HR_IF_NULL_MSG(E_NOINTERFACE, factory, "Failed to get factory interface for %ls", className);

        // Create the picker instance
        return factory.CreateInstance(windowId);
    }

    winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker 
    StoragePickersActivation::CreateFileOpenPicker(winrt::Microsoft::UI::WindowId const& windowId)
    {
        return CreatePicker<
            winrt::Microsoft::Windows::Storage::Pickers::IFileOpenPickerFactory,
            winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker>(
                windowId, L"Microsoft.Windows.Storage.Pickers.FileOpenPicker");
    }

    winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker 
    StoragePickersActivation::CreateFileSavePicker(winrt::Microsoft::UI::WindowId const& windowId)
    {
        return CreatePicker<
            winrt::Microsoft::Windows::Storage::Pickers::IFileSavePickerFactory,
            winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker>(
                windowId, L"Microsoft.Windows.Storage.Pickers.FileSavePicker");
    }

    winrt::Microsoft::Windows::Storage::Pickers::FolderPicker 
    StoragePickersActivation::CreateFolderPicker(winrt::Microsoft::UI::WindowId const& windowId)
    {
        return CreatePicker<
            winrt::Microsoft::Windows::Storage::Pickers::IFolderPickerFactory,
            winrt::Microsoft::Windows::Storage::Pickers::FolderPicker>(
                windowId, L"Microsoft.Windows.Storage.Pickers.FolderPicker");
    }
}
