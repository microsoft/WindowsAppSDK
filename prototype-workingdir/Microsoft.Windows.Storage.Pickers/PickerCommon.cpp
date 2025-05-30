// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "PickerCommon.h"
#include <wil/resource.h>
#include "ShObjIdl.h"
#include <KnownFolders.h>

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
        case winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId::HomeGroup:
            knownFolderId = FOLDERID_HomeGroup;
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


    winrt::hstring FormatExtensionWithWildcard(winrt::hstring extension)
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

    winrt::hstring JoinExtensions(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> extensions)
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
        auto hr = shellItem->GetDisplayName(SIGDN_FILESYSPATH, filePath.put());

        // Returns the item's file system path if it has one
        if (FAILED(hr))
        {
            /* Only items that report SFGAO_FILESYSTEM have a file system path.
               When an item does not have a file system path, for instance, "This PC",
               the call to IShellItem::GetDisplayName(SIGDN_FILESYSPATH, [out] LPWSTR *ppszName ) will fail.
               In this case, we return an empty string.
            */
            return winrt::hstring{};
        }

        return winrt::hstring{ filePath.get() };
    }

    /// <summary>
    /// Capture and processing pickers filter inputs and convert them into Common Item Dialog's accepting type, for FileOpenPicker
    /// </summary>
    /// <param name="buffer">temp buffer to hold dynamically transformed strings</param>
    /// <param name="filters">winrt style filters</param>
    /// <returns>result Coomon Item Dialog style filters, note only raw pointers here,
    /// they are valid up to lifetime of buffer
    /// </returns>
    std::vector<COMDLG_FILTERSPEC> CaptureFilterSpec(std::vector<winrt::hstring>& buffer, winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters)
    {
        size_t resultSize = filters.Size() + 1;
        buffer.clear();
        buffer.reserve(resultSize * static_cast<size_t>(2));

        std::wstring allFilesExtensionList;
        for (const auto& filter : filters)
        {
            auto ext = FormatExtensionWithWildcard(filter);
            buffer.push_back(L"");
            buffer.push_back(ext);

            allFilesExtensionList.reserve(allFilesExtensionList.length() + ext.size() + 1);
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
            buffer.push_back(L"");
            buffer.push_back(L"*");
        }
        else if (filters.Size() == 1 && allFilesExtensionList == L"*")
        {
            // when there're only one filter "*", set filter to All Files *.* (override the values pushed above)
            buffer[0] = L"";
            buffer[1] = L"*";
            resultSize = 1;
        }
        else
        {
            buffer.push_back(L"");
            buffer.push_back(allFilesExtensionList.c_str());
        }

        std::vector<COMDLG_FILTERSPEC> result{ resultSize };
        for (size_t i = 0; i < resultSize; i++)
        {
            result.at(i) = { buffer.at(i * 2).c_str(), buffer.at(i * 2 + 1).c_str() };
        }

        return result;
    }

    /// <summary>
    /// Capture and processing pickers filter inputs and convert them into Common Item Dialog's accepting type, for FileSavePicker
    /// </summary>
    /// <param name="buffer">temp buffer to hold dynamically transformed strings</param>
    /// <param name="filters">winrt style filters</param>
    /// <returns>result Coomon Item Dialog style filters, note only raw pointers here,
    /// they are valid up to lifetime of buffer
    /// </returns>
    std::vector<COMDLG_FILTERSPEC> CaptureFilterSpec(std::vector<winrt::hstring>& buffer, winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> filters)
    {
        std::vector<COMDLG_FILTERSPEC> result(filters.Size());
        buffer.clear();
        buffer.reserve(filters.Size() * static_cast<size_t>(2));

        for (const auto& filter : filters)
        {
            buffer.push_back(filter.Key());
            auto extensionList = JoinExtensions(filter.Value().GetView());
            buffer.push_back(extensionList);
        }
        for (size_t i = 0; i < filters.Size(); i++)
        {
            result.at(i) = { buffer.at(i * 2).c_str(), buffer.at(i * 2 + 1).c_str() };
        }

        if (result.empty())
        {
            result.push_back({ L"", L"*.*" });
        }
        return result;
    }

    void PickerParameters::ConfigureDialog(winrt::com_ptr<IFileDialog> dialog)
    {
        if (!IsHStringNullOrEmpty(CommitButtonText))
        {
            check_hresult(dialog->SetOkButtonLabel(CommitButtonText.c_str()));
        }

        if (!IsHStringNullOrEmpty(SettingsIdentifierId))
        {
            auto guid = HashHStringToGuid(SettingsIdentifierId);
            check_hresult(dialog->SetClientGuid(guid));
        }

        auto defaultFolder = GetKnownFolderFromId(PickerLocationId);
        if (defaultFolder != nullptr)
        {
            check_hresult(dialog->SetDefaultFolder(defaultFolder.get()));
        }

        check_hresult(dialog->SetFileTypes((UINT)FileTypeFilterPara.size(), FileTypeFilterPara.data()));
    }
}
