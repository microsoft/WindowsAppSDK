#include "pch.h"
#include "PickerCommon.h"
#include <wil/resource.h>
#include "ShObjIdl.h"
#include <shobjidl_core.h>
#include "winrt/Microsoft.Storage.Pickers.h"
#include <KnownFolders.h>

namespace {
	bool IsHStringNullOrEmpty(winrt::hstring value) {
		// TODO: proper handling of null string reference?
		return value.empty();
	}

	// TODO: rewrite use WinRT APIs https://learn.microsoft.com/en-us/uwp/api/windows.security.cryptography.core.hashalgorithmprovider?view=winrt-26100
	GUID HashHStringToGuid(winrt::hstring const& input)
	{
		// Convert the hstring to bytes (UTF-16LE encoding)
		const BYTE* data = reinterpret_cast<const BYTE*>(input.data());
		DWORD dataSize = static_cast<DWORD>(input.size() * sizeof(wchar_t));

		// Acquire a cryptographic provider context
		wil::unique_hcryptprov cryptProv;
		THROW_IF_WIN32_BOOL_FALSE(CryptAcquireContextW(&cryptProv, nullptr, nullptr, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT));

		// Create an MD5 hash object
		wil::unique_hcrypthash hash;
		THROW_IF_WIN32_BOOL_FALSE(CryptCreateHash(cryptProv.get(), CALG_MD5, 0, 0, &hash));

		// Hash the data
		THROW_IF_WIN32_BOOL_FALSE(CryptHashData(hash.get(), data, dataSize, 0));

		// Get the hash value
		BYTE hashValue[16]; // MD5 hash is 16 bytes
		DWORD hashSize = sizeof(hashValue);
		THROW_IF_WIN32_BOOL_FALSE(CryptGetHashParam(hash.get(), HP_HASHVAL, hashValue, &hashSize, 0));

		// Copy the hash into a GUID
		GUID guid;
		memcpy(&guid, hashValue, sizeof(GUID));

		// TODO: Need to modify genreated bit patterns to fit GUID specification
		// like need to specify some bits to make it a valid GUID (maybe v3 or v5)
		return guid;
	}

	// TODO: use better winrt implementations?
	// Challenge: currently winrt based Storage.KnownFolder APIs does not provide all location id we need
	winrt::com_ptr<IShellItem> GetKnownFolderFromId(winrt::Microsoft::Storage::Pickers::PickerLocationId pickerLocationId) {
		KNOWNFOLDERID knownFolderId;
		switch (pickerLocationId)
		{
		case winrt::Microsoft::Storage::Pickers::PickerLocationId::DocumentsLibrary:
			knownFolderId = FOLDERID_Documents;
			break;
		case winrt::Microsoft::Storage::Pickers::PickerLocationId::ComputerFolder:
			knownFolderId = FOLDERID_ComputerFolder;
			break;
		case winrt::Microsoft::Storage::Pickers::PickerLocationId::Desktop:
			knownFolderId = FOLDERID_Desktop;
			break;
		case winrt::Microsoft::Storage::Pickers::PickerLocationId::Downloads:
			knownFolderId = FOLDERID_Downloads;
			break;
		case winrt::Microsoft::Storage::Pickers::PickerLocationId::HomeGroup:
			knownFolderId = FOLDERID_HomeGroup;
			break;
		case winrt::Microsoft::Storage::Pickers::PickerLocationId::MusicLibrary:
			knownFolderId = FOLDERID_MusicLibrary;
			break;
		case winrt::Microsoft::Storage::Pickers::PickerLocationId::PicturesLibrary:
			knownFolderId = FOLDERID_PicturesLibrary;
			break;
		case winrt::Microsoft::Storage::Pickers::PickerLocationId::VideosLibrary:
			knownFolderId = FOLDERID_VideosLibrary;
			break;
		case winrt::Microsoft::Storage::Pickers::PickerLocationId::Objects3D:
			knownFolderId = FOLDERID_Objects3D;
			break;
		default:
			return nullptr;
		}

		auto knownFolderManager = winrt::create_instance<IKnownFolderManager>(CLSID_KnownFolderManager);
		winrt::com_ptr<IKnownFolder> knownFolder;
		winrt::check_hresult(knownFolderManager->GetFolder(knownFolderId, knownFolder.put()));
		winrt::com_ptr<IShellItem> defaultFolder;
		winrt::check_hresult(knownFolder->GetShellItem(0, IID_PPV_ARGS(defaultFolder.put())));
		return defaultFolder;
	}
}


namespace PickerCommon {

	using namespace winrt;

	void ConfigureDialogCommon(
		winrt::com_ptr<IFileOpenDialog> dialog,
		winrt::hstring commitButtonText,
		winrt::hstring settingIdentifierId,
		winrt::Microsoft::Storage::Pickers::PickerLocationId pickerLocationId
	) {
		if (!IsHStringNullOrEmpty(commitButtonText))
		{
			check_hresult(dialog->SetOkButtonLabel(commitButtonText.c_str()));
		}

		if (!IsHStringNullOrEmpty(settingIdentifierId)) {
			auto guid = HashHStringToGuid(settingIdentifierId);
			check_hresult(dialog->SetClientGuid(guid));
		}


		auto defaultFolder = GetKnownFolderFromId(pickerLocationId);
		if (defaultFolder != nullptr) {
			check_hresult(dialog->SetFolder(defaultFolder.get()));
			check_hresult(dialog->SetDefaultFolder(defaultFolder.get()));
		}
	}

	// TODO: better way to convert ShellItem a StorageFile without relying on path?.
	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> CreateStorageFileFromShellItem(winrt::com_ptr<IShellItem> shellItem)
	{
		wil::unique_cotaskmem_string filePath;
		check_hresult(shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath));
		auto& result = co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(filePath.get());
		co_return result;
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFolder> CreateStorageFolderFromShellItem(winrt::com_ptr<IShellItem> shellItem)
	{
		wil::unique_cotaskmem_string filePath;
		check_hresult(shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath));
		auto& result = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(filePath.get());
		co_return result;
	}
}
