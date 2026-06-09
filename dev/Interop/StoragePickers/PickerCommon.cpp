// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "shellapi.h"
#include <appmodel.h>
#include "PickerCommon.h"
#include "PickerLocalization.h"
#include <wil/resource.h>
#include "ShObjIdl.h"
#include "shobjidl_core.h"
#include <KnownFolders.h>
#include <shlguid.h>
#include <filesystem>
#include <format>
#include <utility>
#include <string_view>
#include <cwctype>
#include <vector>

namespace {

    GUID HashHStringToGuid(winrt::hstring const& input)
    {
        auto algorithm = winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(winrt::Windows::Security::Cryptography::Core::HashAlgorithmNames::Md5());

        auto buffer = winrt::Windows::Security::Cryptography::CryptographicBuffer::ConvertStringToBinary(input, winrt::Windows::Security::Cryptography::BinaryStringEncoding::Utf16LE);

        auto hash = algorithm.HashData(buffer);

        if (hash.Length() != sizeof(GUID))
        {
            throw winrt::hresult_error(E_FAIL, L"Invalid hash length");
        }

        winrt::com_array<uint8_t> resultBuffer(sizeof(GUID));
        winrt::Windows::Security::Cryptography::CryptographicBuffer::CopyToByteArray(hash, resultBuffer);
        GUID guid = *(reinterpret_cast<GUID*>(resultBuffer.data()));

        // Adjust the GUID to conform to version 3 UUID (MD5-based)
        guid.Data3 = (guid.Data3 & 0x0FFF) | 0x3000; // Set the version to 3
        guid.Data4[0] = (guid.Data4[0] & 0x3F) | 0x80; // Set variant to RFC 4122

        return guid;
    }

    winrt::com_ptr<IShellItem> GetKnownFolderFromId(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId pickerLocationId)
    {
        KNOWNFOLDERID knownFolderId;
        switch (pickerLocationId)
        {
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary:
            knownFolderId = FOLDERID_Documents;
            break;
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::ComputerFolder:
            knownFolderId = FOLDERID_ComputerFolder;
            break;
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Desktop:
            knownFolderId = FOLDERID_Desktop;
            break;
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Downloads:
            knownFolderId = FOLDERID_Downloads;
            break;
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::MusicLibrary:
            knownFolderId = FOLDERID_MusicLibrary;
            break;
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::PicturesLibrary:
            knownFolderId = FOLDERID_PicturesLibrary;
            break;
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::VideosLibrary:
            knownFolderId = FOLDERID_VideosLibrary;
            break;
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Objects3D:
            knownFolderId = FOLDERID_Objects3D;
            break;
        default:
            return nullptr;
        }

        auto knownFolderManager = winrt::create_instance<IKnownFolderManager>(CLSID_KnownFolderManager);

        winrt::com_ptr<IKnownFolder> knownFolder{};
        winrt::hresult hr = knownFolderManager->GetFolder(knownFolderId, knownFolder.put());
        if (!knownFolder)
        {
            knownFolderManager->GetFolder(FOLDERID_Documents, knownFolder.put());
        }
        if (!knownFolder)
        {
            return nullptr;
        }

        winrt::com_ptr<IShellItem> defaultFolder{};
        hr = knownFolder->GetShellItem(0, IID_PPV_ARGS(defaultFolder.put()));
        if (FAILED(hr))
        {
            return nullptr;
        }

        return defaultFolder;
    }

}

namespace {

    // Search immediate children of parentItem for the WSL item.
    // If found, make it visible via INameSpaceTreeControl::SetItemState.
    bool FindAndShowWslInChildren(winrt::com_ptr<IShellItem> const& wslItem, winrt::com_ptr<IShellItem> const& parentItem, winrt::com_ptr<INameSpaceTreeControl> const& nstc) noexcept
    {
        if (!parentItem || !wslItem || !nstc)
        {
            return false;
        }

        winrt::com_ptr<IEnumShellItems> enumItems;
        if (FAILED(parentItem->BindToHandler(nullptr, BHID_EnumItems, IID_PPV_ARGS(enumItems.put()))) || !enumItems)
        {
            return false;
        }

        winrt::com_ptr<IShellItem> childItem;
        ULONG fetched = 0;
        while (SUCCEEDED(enumItems->Next(1, childItem.put(), &fetched)) && fetched > 0)
        {
            if (childItem)
            {
                int order = 0;
                if (childItem->Compare(wslItem.get(), SICHINT_CANONICAL, &order) == S_OK && order == 0)
                {
                    nstc->SetItemState(childItem.get(), NSTCIS_EXPANDED, NSTCIS_EXPANDED);
                    return true;
                }
                childItem = nullptr;
            }
            fetched = 0;
        }

        return false;
    }

}

namespace PickerCommon {
    using namespace winrt;

    void CALLBACK WslNodeRevealer::PollTimerProc(HWND hwnd, UINT, UINT_PTR timerId, DWORD) noexcept
    {
        reinterpret_cast<WslNodeRevealer*>(timerId)->RevealWslNodeWhenReady(hwnd);
    }

    void WslNodeRevealer::RevealWslNodeWhenReady(HWND hwnd) noexcept
    {
        if (!m_nstc || !m_wslItem || ++m_pollCount >= s_maxPollCount)
        {
            KillTimer(hwnd, reinterpret_cast<UINT_PTR>(this));
            m_timerPending = false;
            m_nstc = nullptr;
            m_wslItem = nullptr;
            return;
        }

        winrt::com_ptr<IShellItemArray> roots;
        DWORD count = 0;
        if (SUCCEEDED(m_nstc->GetRootItems(roots.put())) && roots)
        {
            if (FAILED(roots->GetCount(&count)))
            {
                count = 0;
            }
        }

        // Wait until at least one root node has loaded.
        if (count == 0)
        {
            return;
        }

        KillTimer(hwnd, reinterpret_cast<UINT_PTR>(this));
        m_timerPending = false;

        // Search for the WSL node in the immediate children of each root node.
        for (DWORD i = 0; i < count; i++)
        {
            winrt::com_ptr<IShellItem> rootItem;
            if (SUCCEEDED(roots->GetItemAt(i, rootItem.put())) && rootItem)
            {
                if (FindAndShowWslInChildren(m_wslItem, rootItem, m_nstc))
                {
                    break;
                }
            }
        }

        m_nstc = nullptr;
        m_wslItem = nullptr;
        m_pollCount = 0;
    }

    void WslNodeRevealer::CancelPendingReveal() noexcept
    {
        if (m_timerPending)
        {
            KillTimer(m_timerHwnd, reinterpret_cast<UINT_PTR>(this));
            m_timerPending = false;
            m_timerHwnd = nullptr;
        }
        m_nstc = nullptr;
        m_wslItem = nullptr;
        m_pollCount = 0;
    }

    // IFileDialogEvents::OnFolderChange is called when the dialog is opened.
    // https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ifiledialogevents-onfolderchange
    IFACEMETHODIMP WslNodeRevealer::OnFolderChange(IFileDialog* pfd) noexcept
    {
        if (!m_revealed)
        {
            m_revealed = true;
            TryStartReveal(pfd); // best-effort; ignore failure so the picker always opens
        }
        return S_OK;
    }

    HRESULT WslNodeRevealer::TryStartReveal(IFileDialog* pfd) noexcept
    {
        winrt::com_ptr<IServiceProvider> sp;
        RETURN_IF_FAILED(pfd->QueryInterface(IID_PPV_ARGS(sp.put())));

        winrt::com_ptr<IShellBrowser> sb;
        RETURN_IF_FAILED(sp->QueryService(SID_STopLevelBrowser, IID_PPV_ARGS(sb.put())));

        winrt::com_ptr<IServiceProvider> sbSp;
        RETURN_IF_FAILED(sb->QueryInterface(IID_PPV_ARGS(sbSp.put())));

        winrt::com_ptr<INameSpaceTreeControl> nstc;
        RETURN_IF_FAILED(sbSp->QueryService(IID_INameSpaceTreeControl, IID_PPV_ARGS(nstc.put())));

        // Resolve the WSL root shell item, falling back from \\wsl.localhost to \\wsl$.
        winrt::com_ptr<IShellItem> wslItem;
        if (FAILED(SHCreateItemFromParsingName(L"\\\\wsl.localhost", nullptr, IID_PPV_ARGS(wslItem.put()))))
        {
            RETURN_IF_FAILED(SHCreateItemFromParsingName(L"\\\\wsl$", nullptr, IID_PPV_ARGS(wslItem.put())));
        }

        // Obtain the dialog's HWND so we can attach the timer to it.
        // SetTimer with a non-NULL hWnd uses the supplied nIDEvent as-is (letting us
        // recover `this` in PollTimerProc) and synthesizes WM_TIMER via the window's
        // message loop rather than posting to the thread queue, so KillTimer is atomic.
        winrt::com_ptr<IOleWindow> oleWindow;
        RETURN_IF_FAILED(pfd->QueryInterface(IID_PPV_ARGS(oleWindow.put())));
        HWND dialogHwnd = nullptr;
        RETURN_IF_FAILED(oleWindow->GetWindow(&dialogHwnd));
        RETURN_HR_IF_NULL(E_FAIL, dialogHwnd);

        m_nstc = nstc;
        m_wslItem = wslItem;
        m_pollCount = 0;
        m_timerHwnd = dialogHwnd;
        m_timerPending = SetTimer(m_timerHwnd, reinterpret_cast<UINT_PTR>(this), s_pollIntervalMs, PollTimerProc) != 0;
        if (!m_timerPending)
        {
            m_timerHwnd = nullptr;
        }

        return S_OK;
    }

    bool IsHStringNullOrEmpty(winrt::hstring value)
    {
        return value.empty();
    }

    winrt::hstring GetPathFromShellItem(winrt::com_ptr<IShellItem> shellItem)
    {
        wil::unique_cotaskmem_string filePath;
        check_hresult(shellItem->GetDisplayName(SIGDN_FILESYSPATH, filePath.put()));
        return winrt::hstring{ filePath.get() };
    }

    winrt::com_ptr<IShellItem> TryParseFolderItem(winrt::hstring const& folderPathStr)
    {
        std::filesystem::path folderPath(folderPathStr.c_str());
        if (folderPath.empty())
        {
            return nullptr;
        }

        if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath))
        {
            return nullptr;
        }

        winrt::com_ptr<IShellItem> shellItem;
        HRESULT hr = SHCreateItemFromParsingName(folderPath.c_str(), nullptr, IID_PPV_ARGS(shellItem.put()));
        if (SUCCEEDED(hr))
        {
            return shellItem;
        }

        return nullptr;
    }

    void ValidateViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value)
    {
        switch (value)
        {
        case winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::List:
        case winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode::Thumbnail:
            return;
        default:
            throw winrt::hresult_invalid_argument(
                PickerLocalization::GetStoragePickersLocalizationText(InvalidViewModeLocalizationKey));
            break;
        }
    }

    void ValidateSuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value)
    {
        switch (value)
        {
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary:
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::ComputerFolder:
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Desktop:
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Downloads:
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::MusicLibrary:
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::PicturesLibrary:
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::VideosLibrary:
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Objects3D:
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::Unspecified:
            return;
        default:
            throw winrt::hresult_invalid_argument(
                PickerLocalization::GetStoragePickersLocalizationText(InvalidSuggestedStartLocationLocalizationKey));
            break;
        }
    }

    void ValidateStringNoEmbeddedNulls(winrt::hstring const& value)
    {
        if (value.empty())
        {
            return;
        }

        for (size_t i = 0; i < value.size(); i++)
        {
            if (value[i] == L'\0')
            {
                throw winrt::hresult_invalid_argument(
                    PickerLocalization::GetStoragePickersLocalizationText(StringNoEmbeddedNullsLocalizationKey));
            }
        }
    }

    void ValidateSingleFileTypeFilterElement(winrt::hstring const& filter)
    {
        if (filter == L"*")
        {
            return; // "*" is a valid filter, stands for "All Files"
        }

        if (filter.empty() || (filter[0] != L'.'))
        {
            throw winrt::hresult_invalid_argument(
                PickerLocalization::GetStoragePickersLocalizationText(ImproperFileExtensionLocalizationKey));
        }

        for (size_t i = 1; i < filter.size(); i++)
        {
            if (filter[i] == L'.' || filter[i] == L'*' || filter[i] == L'?')
            {
                throw winrt::hresult_invalid_argument(
                    PickerLocalization::GetStoragePickersLocalizationText(ImproperFileExtensionLocalizationKey));
            }
        }

        ValidateStringNoEmbeddedNulls(filter);
    }

    void ValidateSuggestedFileName(winrt::hstring const& suggestedFileName)
    {
        if (suggestedFileName.size() > MAX_PATH)
        {
            throw winrt::hresult_invalid_argument(
                PickerLocalization::GetStoragePickersLocalizationText(MaxSaveFileLengthExceededLocalizationKey));
        }

        ValidateStringNoEmbeddedNulls(suggestedFileName);
    }

    void ValidateFolderPath(winrt::hstring const& path, std::string const& propertyName)
    {
        if (path.empty())
        {
            // allow empty path.
            return;
        }

        ValidateStringNoEmbeddedNulls(path);

        auto pathObj = std::filesystem::path(path.c_str());
        if (!pathObj.is_absolute())
        {
            throw std::invalid_argument(propertyName);
        }

        // The method SHSimpleIDListFromPath does syntax check on the path string.
        wil::unique_cotaskmem_ptr<ITEMIDLIST> pidl{ SHSimpleIDListFromPath(path.c_str()) };
        if (!pidl)
        {
            throw std::invalid_argument(propertyName);
        }
    }

    void ValidateInitialFileTypeIndex(int const& value)
    {
        if (value < DefaultInitialFileTypeIndex)
        {
            throw winrt::hresult_invalid_argument(
                PickerLocalization::GetStoragePickersLocalizationText(InvalidInitialFileTypeIndexLocalizationKey));
        }
    }

    winrt::hstring PickerParameters::FormatExtensionWithWildcard(winrt::hstring extension)
    {
        if (!extension.empty() && extension[0] == L'*')
        {
            return extension;
        }
        else
        {
            return L"*" + extension;
        }
    }

    winrt::hstring PickerParameters::JoinExtensions(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> extensions)
    {
        winrt::hstring result;
        bool first = true;
        for (const auto& ext : extensions)
        {
            if (first)
            {
                result = FormatExtensionWithWildcard(ext);
                first = false;
            }
            else
            {
                result = result + L";" + FormatExtensionWithWildcard(ext);
            }
        }
        return result;
    }

    void PickerParameters::CaptureFilterSpecData(
        winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> fileTypeFilterView,
        winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> fileTypeChoicesView,
        int initialFileTypeIndex)
    {
        InitialFileTypeIndex = initialFileTypeIndex;

        // The FileTypeChoices takes precedence over FileTypeFilter if both are provided.
        if (fileTypeChoicesView && fileTypeChoicesView.Size() > 0)
        {
            CaptureFilterSpec(fileTypeChoicesView);
            if (InitialFileTypeIndex > static_cast<int>(FileTypeFilterParams.size() - 1))
            {
                throw winrt::hresult_invalid_argument(
                    PickerLocalization::GetStoragePickersLocalizationText(InvalidInitialFileTypeIndexLocalizationKey));
            }
            return;
        }

        if (fileTypeFilterView && fileTypeFilterView.Size() > 0)
        {
            CaptureFilterSpec(fileTypeFilterView);
            if (InitialFileTypeIndex > static_cast<int>(FileTypeFilterParams.size() - 1))
            {
                throw winrt::hresult_invalid_argument(
                    PickerLocalization::GetStoragePickersLocalizationText(InvalidInitialFileTypeIndexLocalizationKey));
            }
            return;
        }

        // Even if no filters provided, we still need to set filter to All Files *.*
        auto emptyFilters = winrt::single_threaded_vector<winrt::hstring>();
        CaptureFilterSpec(emptyFilters.GetView());
    }

    /// <summary>
    /// Capture and processing pickers filter inputs and convert them into Common Item Dialog's accepting type, for FileOpenPicker
    /// </summary>
    /// <param name="filters">winrt style filters</param>
    void PickerParameters::CaptureFilterSpec(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters)
    {
        size_t resultSize = filters.Size() + 1;   // A vector input will have unioned All Files category appended.
        FileTypeFilterData.clear();
        FileTypeFilterData.reserve(resultSize * static_cast<size_t>(2));

        std::wstring allFilesExtensionList;
        allFilesExtensionList.reserve(resultSize * 8); // a typical extension takes 6-7 chars, like "*.txt;" and "*.docx;"
        for (const auto& filter : filters)
        {
            auto ext = FormatExtensionWithWildcard(filter);
            FileTypeFilterData.push_back(ext);
            FileTypeFilterData.push_back(ext);

            allFilesExtensionList += ext;
            allFilesExtensionList += L";";
        }

        if (!allFilesExtensionList.empty())
        {
            allFilesExtensionList.pop_back(); // Remove the last semicolon
        }

        if (filters.Size() == 0)
        {
            // when filters not defined, set filter to All Files *.*
            FileTypeFilterData.push_back(AllFilesText);
            FileTypeFilterData.push_back(L"*");
        }
        else if (filters.Size() == 1 && allFilesExtensionList == L"*")
        {
            // when there're only one filter "*", set filter to All Files *.* (override the values pushed above)
            FileTypeFilterData[0] = AllFilesText;
            FileTypeFilterData[1] = L"*";
            resultSize = 1;
        }
        else
        {
            FileTypeFilterData.push_back(AllFilesText);
            FileTypeFilterData.push_back(allFilesExtensionList.c_str());
        }

        FileTypeFilterParams.clear();
        FileTypeFilterParams.reserve(resultSize);
        for (size_t i = 0; i < resultSize; i++)
        {
            FileTypeFilterParams.push_back({ FileTypeFilterData.at(i * 2).c_str(), FileTypeFilterData.at(i * 2 + 1).c_str() });
        }

        if (InitialFileTypeIndex == DefaultInitialFileTypeIndex)
        {
            // If no valid InitialFileTypeIndex specified, focus the last one ("All Files" - the auto-added unioned category)
            InitialFileTypeIndex = static_cast<int>(resultSize) - 1;
        }
    }

    /// <summary>
    /// Capture and processing pickers filter inputs and convert them into Common Item Dialog's accepting type, for FileSavePicker
    /// </summary>
    /// <param name="filters">winrt style filters</param>
    void PickerParameters::CaptureFilterSpec(winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> filters)
    {
        size_t resultSize = filters.Size();
        FileTypeFilterData.clear();
        FileTypeFilterData.reserve(filters.Size() * static_cast<size_t>(2));

        for (const auto& filter : filters)
        {
            FileTypeFilterData.push_back(filter.Key());
            auto extensionList = JoinExtensions(filter.Value().GetView());
            FileTypeFilterData.push_back(extensionList);
        }

        if (filters.Size() == 0)
        {
            // when filters not defined, set filter to All Files *.*
            FileTypeFilterData.push_back(AllFilesText);
            FileTypeFilterData.push_back(L"*");
            resultSize = 1;
        }

        FileTypeFilterParams.clear();
        FileTypeFilterParams.reserve(resultSize);
        for (size_t i = 0; i < resultSize; i++)
        {
            FileTypeFilterParams.push_back({ FileTypeFilterData.at(i * 2).c_str(), FileTypeFilterData.at(i * 2 + 1).c_str() });
        }
    }

    winrt::hstring PickerParameters::TryGetAppUserModelId()
    {
        wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
        UINT32 appUserModelIdSize{ _countof(appUserModelId) };

        auto hr{GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId) };
        if (SUCCEEDED(hr))
        {
            return winrt::hstring{ appUserModelId };
        }

        return {};
    }

    winrt::hstring PickerParameters::TryGetProcessFullPath()
    {
        wil::unique_cotaskmem_string module;
        auto hr{ LOG_IF_FAILED(wil::GetModuleFileNameW(nullptr, module)) };
        if (SUCCEEDED(hr))
        {
            return winrt::hstring{ module.get() };
        }

        return {};
    }

    void PickerParameters::ConfigureDialog(winrt::com_ptr<IFileDialog> dialog)
    {
        if (!IsHStringNullOrEmpty(CommitButtonText))
        {
            check_hresult(dialog->SetOkButtonLabel(CommitButtonText.c_str()));
        }

        if (!IsHStringNullOrEmpty(Title))
        {
            check_hresult(dialog->SetTitle(Title.c_str()));
        }

        winrt::com_ptr<IShellItem> defaultFolder{};

        // The SuggestedStartFolder takes precedence over SuggestedStartLocation if both are provided.
        if (!IsHStringNullOrEmpty(SuggestedStartFolder))
        {
            defaultFolder = TryParseFolderItem(SuggestedStartFolder);
        }

        if (!defaultFolder)
        {
            defaultFolder = GetKnownFolderFromId(SuggestedStartLocation);
        }

        if (defaultFolder)
        {
            check_hresult(dialog->SetDefaultFolder(defaultFolder.get()));
        }

        // SuggestedFolder takes precedence over SuggestedStartFolder/SuggestedStartLocation if both are provided.
        if (!IsHStringNullOrEmpty(SuggestedFolder))
        {
            if (auto folderItem = TryParseFolderItem(SuggestedFolder))
            {
                check_hresult(dialog->SetFolder(folderItem.get()));
            }
        }

        if (FileTypeFilterParams.size() > 0)
        {
            check_hresult(dialog->SetFileTypes(static_cast<UINT>(FileTypeFilterParams.size()), FileTypeFilterParams.data()));

            if (InitialFileTypeIndex != DefaultInitialFileTypeIndex && InitialFileTypeIndex < static_cast<int>(FileTypeFilterParams.size()))
            {
                check_hresult(dialog->SetFileTypeIndex(InitialFileTypeIndex + 1)); // COMDLG file type index is 1-based
            }
        }

        if (!IsHStringNullOrEmpty(SettingsIdentifier))
        {
            auto appDistinctString = TryGetAppUserModelId();
            if (appDistinctString.empty())
            {
                appDistinctString = TryGetProcessFullPath();
            }
            if (!appDistinctString.empty())
            {
                auto clientId = HashHStringToGuid(appDistinctString + L"|" + SettingsIdentifier);
                check_hresult(dialog->SetClientGuid(clientId));
            }
            else
            {
                throw winrt::hresult_invalid_argument(
                    PickerLocalization::GetStoragePickersLocalizationText(InvalidAppIdForSettingsIdentifierLocalizationKey));
            }
        }

    }

    /// <summary>
    /// Configure the FileSaveDialog, this is only for FileSavePicker.
    /// </summary>
    /// <param name="dialog"></param>
    void PickerParameters::ConfigureFileSaveDialog(winrt::com_ptr<IFileSaveDialog> dialog)
    {
        if (!IsHStringNullOrEmpty(SuggestedFileName))
        {
            check_hresult(dialog->SetFileName(SuggestedFileName.c_str()));
        }

        if (!ShowOverwritePrompt)
        {
            FILEOPENDIALOGOPTIONS options{};
            check_hresult(dialog->GetOptions(&options));
            options = static_cast<FILEOPENDIALOGOPTIONS>(options & ~FOS_OVERWRITEPROMPT);
			check_hresult(dialog->SetOptions(options));
        }

    }
}
