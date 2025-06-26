// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "FolderPicker.g.h"
#include "PickerCommon.h"
#include "StoragePickersTelemetryHelper.h"
#include <shobjidl.h>

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    // Event handler to track folder navigation in the dialog
    class FolderDialogEventHandler : public IFileDialogEvents
    {
    public:
        FolderDialogEventHandler() : m_refCount(1) {}

        // IUnknown methods
        STDMETHODIMP QueryInterface(REFIID riid, void** ppv) override
        {
            if (riid == IID_IUnknown || riid == IID_IFileDialogEvents)
            {
                *ppv = static_cast<IFileDialogEvents*>(this);
                AddRef();
                return S_OK;
            }
            *ppv = nullptr;
            return E_NOINTERFACE;
        }

        STDMETHODIMP_(ULONG) AddRef() override
        {
            return InterlockedIncrement(&m_refCount);
        }

        STDMETHODIMP_(ULONG) Release() override
        {
            ULONG count = InterlockedDecrement(&m_refCount);
            if (count == 0)
            {
                delete this;
            }
            return count;
        }

        // IFileDialogEvents methods
        STDMETHODIMP OnFileOk(IFileDialog*) override { return S_OK; }
        STDMETHODIMP OnFolderChanging(IFileDialog*, IShellItem*) override { return S_OK; }

        STDMETHODIMP OnFolderChange(IFileDialog* pfd) override
        {
            // Capture the current folder when user navigates
            if (pfd)
            {
                pfd->GetFolder(m_lastBrowsedFolder.put());
            }
            return S_OK;
        }

        STDMETHODIMP OnSelectionChange(IFileDialog*) override { return S_OK; }
        STDMETHODIMP OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE*) override { return S_OK; }
        STDMETHODIMP OnTypeChange(IFileDialog*) override { return S_OK; }
        STDMETHODIMP OnOverwrite(IFileDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*) override { return S_OK; }

        winrt::com_ptr<IShellItem> GetLastBrowsedFolder() const { return m_lastBrowsedFolder; }

    private:
        ULONG m_refCount;
        winrt::com_ptr<IShellItem> m_lastBrowsedFolder;
    };

    struct FolderPicker : FolderPickerT<FolderPicker>
    {
        FolderPicker(winrt::Microsoft::UI::WindowId const& windowId);

        winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode ViewMode();
        void ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value);

        hstring SettingsIdentifier();
        void SettingsIdentifier(hstring const& value);

        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId SuggestedStartLocation();
        void SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value);

        hstring CommitButtonText();
        void CommitButtonText(hstring const& value);

        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFolderResult> PickSingleFolderAsync();

    private:
        winrt::Microsoft::UI::WindowId m_windowId{};

        PickerViewMode m_viewMode{ PickerViewMode::List };
        hstring m_settingsIdentifier{};
        PickerLocationId m_suggestedStartLocation{ PickerLocationId::Unspecified };
        hstring m_commitButtonText{};
        StoragePickersTelemetryHelper m_telemetryHelper{};

        // Static member to persist folder context across instances
        static winrt::com_ptr<IShellItem> s_lastBrowsedFolder;

        void CaptureParameters(PickerCommon::PickerParameters& parameters);
    };
}
namespace winrt::Microsoft::Windows::Storage::Pickers::factory_implementation
{
    struct FolderPicker : FolderPickerT<FolderPicker, implementation::FolderPicker>
    {
    };
}
