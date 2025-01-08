#include "pch.h"
#include "PickerCommon.h"
#include <wil/resource.h>
#include "ShObjIdl.h"
#include <KnownFolders.h>

namespace {

    GUID HashHStringToGuid(winrt::hstring const& input)
    {
        auto algorithmProvider = winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(winrt::Windows::Security::Cryptography::Core::HashAlgorithmNames::Md5());

        auto buffer = winrt::Windows::Security::Cryptography::CryptographicBuffer::ConvertStringToBinary(input, winrt::Windows::Security::Cryptography::BinaryStringEncoding::Utf16LE);

        auto hash = algorithmProvider.HashData(buffer);

        if (hash.Length() != 16)
        {
            throw winrt::hresult_error(E_FAIL, L"Invalid hash length");
        }

        winrt::com_array<uint8_t> resultBuffer{};
        winrt::Windows::Security::Cryptography::CryptographicBuffer::CopyToByteArray(hash, resultBuffer);
        GUID guid = *(reinterpret_cast<GUID*>(resultBuffer.data()));

        // TODO: verify bit pattern code from copilot is correct to fit spec
        // Adjust the GUID to conform to version 3 UUID (MD5-based)
        guid.Data3 = (guid.Data3 & 0x0FFF) | 0x3000; // Set the version to 3
        guid.Data4[0] = (guid.Data4[0] & 0x3F) | 0x80; // Set variant to RFC 4122

        return guid;
    }

    // TODO: use better winrt implementations?
    // Challenge: currently winrt based Storage.KnownFolder APIs does not provide all location id we need
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
        winrt::check_hresult(knownFolderManager->GetFolder(knownFolderId, knownFolder.put()));
        winrt::com_ptr<IShellItem> defaultFolder{};
        winrt::check_hresult(knownFolder->GetShellItem(0, IID_PPV_ARGS(defaultFolder.put())));
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
        // TODO: proper handling of null string reference?
        return value.empty();
    }


    // TODO: better way to convert ShellItem a StorageFile without relying on path?.
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> CreateStorageFileFromShellItem(winrt::com_ptr<IShellItem> shellItem)
    {
        wil::unique_cotaskmem_string filePath;
        check_hresult(shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath));
        co_return co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(filePath.get());
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFolder> CreateStorageFolderFromShellItem(winrt::com_ptr<IShellItem> shellItem)
    {
        wil::unique_cotaskmem_string filePath;
        check_hresult(shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath));
        co_return co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(filePath.get());
    }

    std::vector<COMDLG_FILTERSPEC> CaptureFilterSpec(std::vector<winrt::hstring>& buffer, winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters)
    {
        std::vector<COMDLG_FILTERSPEC> result(filters.Size());
        buffer.clear();
        buffer.reserve(filters.Size() * (size_t)2);
        for (auto filter : filters)
        {
            auto ext = FormatExtensionWithWildcard(filter);
            buffer.push_back(filter);
            buffer.push_back(ext);
        }
        for (size_t i = 0; i < filters.Size(); i++)
        {
            result.at(i) = { buffer.at(i * 2).c_str(), buffer.at(i * 2 + 1).c_str() };
        }

        if (result.size() == 0)
        {
            result.push_back({ L"All Files", L"*.*" });
        }
        return result;
    }

    std::vector<COMDLG_FILTERSPEC> CaptureFilterSpec(std::vector<winrt::hstring>& buffer, winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> filters)
    {
        std::vector<COMDLG_FILTERSPEC> result(filters.Size());
        buffer.clear();
        buffer.reserve(filters.Size() * (size_t)2);

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

        if (result.size() == 0)
        {
            result.push_back({ L"All Files", L"*.*" });
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
            check_hresult(dialog->SetFolder(defaultFolder.get()));
            check_hresult(dialog->SetDefaultFolder(defaultFolder.get()));
        }

        check_hresult(dialog->SetFileTypes(FileTypeFilterPara.size(), FileTypeFilterPara.data()));
    }
}
