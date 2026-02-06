// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <winrt/Microsoft.Windows.Storage.Pickers.h>
#include <winrt/Microsoft.UI.Windowing.h>

namespace StoragePickersTestApp
{
    /// <summary>
    /// Helper class for activating Storage Pickers from the locally-built WindowsAppRuntime DLL.
    /// 
    /// This is necessary because the test app uses a shipped WindowsAppSDK NuGet for WinUI,
    /// but needs to test Storage Pickers from the local repo build. Since Storage Pickers
    /// isn't in the shipped NuGet, we manually load the activation factory from our local DLL.
    /// </summary>
    class StoragePickersActivation
    {
    public:
        /// <summary>
        /// Creates a FileOpenPicker instance using the locally-built WindowsAppRuntime DLL.
        /// </summary>
        /// <param name="windowId">The window ID to associate with the picker.</param>
        /// <returns>A FileOpenPicker instance.</returns>
        static winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker CreateFileOpenPicker(
            winrt::Microsoft::UI::WindowId const& windowId);

        /// <summary>
        /// Creates a FileSavePicker instance using the locally-built WindowsAppRuntime DLL.
        /// </summary>
        /// <param name="windowId">The window ID to associate with the picker.</param>
        /// <returns>A FileSavePicker instance.</returns>
        static winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker CreateFileSavePicker(
            winrt::Microsoft::UI::WindowId const& windowId);

        /// <summary>
        /// Creates a FolderPicker instance using the locally-built WindowsAppRuntime DLL.
        /// </summary>
        /// <param name="windowId">The window ID to associate with the picker.</param>
        /// <returns>A FolderPicker instance.</returns>
        static winrt::Microsoft::Windows::Storage::Pickers::FolderPicker CreateFolderPicker(
            winrt::Microsoft::UI::WindowId const& windowId);

    private:
        static void EnsureRuntimeLoaded();
        
        template<typename TFactory, typename TPicker>
        static TPicker CreatePicker(winrt::Microsoft::UI::WindowId const& windowId, const wchar_t* className);

        static HMODULE s_hRuntimeModule;
        static void* s_dllGetActivationFactory;
    };
}
