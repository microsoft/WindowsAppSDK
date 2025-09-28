// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "shellapi.h"
#include "PickerCommon.h"
#include "PickerLocalization.h"
#include <wil/resource.h>
#include "ShObjIdl.h"
#include "shobjidl_core.h"
#include <KnownFolders.h>
#include <filesystem>
#include <format>
#include <utility>
#include <string_view>
#include <cwctype>


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

namespace PickerCommon {
    using namespace winrt;

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

        for (int i = 0; i < value.size(); i++)
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

        for (int i = 1; i < filter.size(); i++)
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

    void ValidateFolderPath(winrt::hstring const& path, std::wstring_view argumentName)
    {
        if (path.empty())
        {
            // allow empty path.
            return;
        }

        ValidateStringNoEmbeddedNulls(path);

        std::wstring pathString{ path };
        auto pathObj = std::filesystem::path(pathString);
        if (!pathObj.is_absolute())
        {
            throw std::invalid_argument(argumentName);
        }

        constexpr std::wstring_view invalidCharacters{ L"<>\"|?*" };

        bool hasExtendedPrefix = false;
        size_t startIndex = 0;
        if (pathString.size() >= 4 && pathString[0] == L'\\' && pathString[1] == L'\\' &&
            (pathString[2] == L'?' || pathString[2] == L'.') && pathString[3] == L'\\')
        {
            hasExtendedPrefix = true;
            startIndex = 4; // Skip the extended path prefix
        }

        auto isDriveSpecifier = [&](size_t index)
        {
            if (!hasExtendedPrefix)
            {
                return index == 1 && std::iswalpha(pathString[0]);
            }

            return (index == 5 && std::iswalpha(pathString[4]));
        };

        for (size_t i = startIndex; i < pathString.size(); ++i)
        {
            wchar_t currentChar = pathString[i];

            if (currentChar == L':')
            {
                if (isDriveSpecifier(i))
                {
                    continue;
                }
            }

            if (invalidCharacters.find(currentChar) != std::wstring_view::npos)
            {
                throw std::invalid_argument(argumentName);
            }
        }

        constexpr size_t MaxComponentLength = 255;
        bool isFirstComponent = true;
        for (auto const& component : pathObj)
        {
            auto nativeComponent = component.native();
            if (nativeComponent.empty())
            {
                continue;
            }

            if (isFirstComponent)
            {
                isFirstComponent = false;
                continue; // Skip root name (e.g., "C:" or "\\server\share")
            }

            if (nativeComponent == L"\\" || nativeComponent == L"/")
            {
                continue; // Skip root directory separators
            }

            if (nativeComponent.size() > MaxComponentLength)
            {
                throw std::invalid_argument(argumentName);
            }
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
        winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> fileTypeChoicesView)
    {
        // The FileTypeChoices takes precedence over FileTypeFilter if both are provided.
        if (fileTypeChoicesView && fileTypeChoicesView.Size() > 0)
        {
            CaptureFilterSpec(fileTypeChoicesView);
            return;
        }

        if (fileTypeFilterView && fileTypeFilterView.Size() > 0)
        {
            CaptureFilterSpec(fileTypeFilterView);
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
            FileTypeFilterData.push_back(L"");
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

        FileTypeFilterPara.clear();
        FileTypeFilterPara.reserve(resultSize);
        for (size_t i = 0; i < resultSize; i++)
        {
            FileTypeFilterPara.push_back({ FileTypeFilterData.at(i * 2).c_str(), FileTypeFilterData.at(i * 2 + 1).c_str() });
        }
    }

    /// <summary>
    /// Capture and processing pickers filter inputs and convert them into Common Item Dialog's accepting type, for FileSavePicker
    /// </summary>
    /// <param name="filters">winrt style filters</param>
    void PickerParameters::CaptureFilterSpec(winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> filters)
    {
        size_t resultSize = filters.Size() + 1;

        FileTypeFilterData.clear();
        FileTypeFilterData.reserve(resultSize * static_cast<size_t>(2));
        if (resultSize == 1)
        {
            FileTypeFilterData.push_back(AllFilesText);
            FileTypeFilterData.push_back(L"*");
        }
        else
        {
            std::vector<winrt::hstring> unionedExtensionVector{};
            unionedExtensionVector.reserve(filters.Size());
            
            for (const auto& filter : filters)
            {
                FileTypeFilterData.push_back(filter.Key());
                auto singleCategoryExtensions = JoinExtensions(filter.Value().GetView());
                FileTypeFilterData.push_back(singleCategoryExtensions);
                unionedExtensionVector.push_back(singleCategoryExtensions);
            }

            auto unionedExtensions = JoinExtensions(unionedExtensionVector.GetView());
            FileTypeFilterData.push_back(AllFilesText);
            FileTypeFilterData.push_back(unionedExtensions);
        }

        FileTypeFilterPara.clear();
        FileTypeFilterPara.reserve(resultSize);
        for (size_t i = 0; i < resultSize; i++)
        {
            FileTypeFilterPara.push_back({ FileTypeFilterData.at(i * 2).c_str(), FileTypeFilterData.at(i * 2 + 1).c_str() });
        }
    }

    void PickerParameters::ConfigureDialog(winrt::com_ptr<IFileDialog> dialog)
    {
        if (!IsHStringNullOrEmpty(CommitButtonText))
        {
            check_hresult(dialog->SetOkButtonLabel(CommitButtonText.c_str()));
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

        if (FileTypeFilterPara.size() > 0)
        {
            check_hresult(dialog->SetFileTypes((UINT)FileTypeFilterPara.size(), FileTypeFilterPara.data()));
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

    }
}
