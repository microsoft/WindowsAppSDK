// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "ActivatedEventArgsBase.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::ApplicationModel::Activation;

    class FileActivatedEventArgs : public winrt::implements<FileActivatedEventArgs,
        ActivatedEventArgsBase, IFileActivatedEventArgs,
        IFileActivatedEventArgsWithCallerPackageFamilyName,
        IFileActivatedEventArgsWithNeighboringFiles>
    {
    public:
        FileActivatedEventArgs([[maybe_unused]] const std::wstring contractData)
        {
            m_kind = ActivationKind::File;
        }

        // IFileActivatedEventArgs
        IVectorView<Windows::Storage::IStorageItem> Files()
        {
            return nullptr;
        }

        winrt::hstring Verb()
        {
            return L"";
        }

        // IFileActivatedEventArgsWithCallerPackageFamilyName
        winrt::hstring CallerPackageFamilyName()
        {
            return L""; // TODO: Implement!
        }

        // IFileActivatedEventArgsWithNeighboringFiles
        winrt::Windows::Storage::Search::StorageFileQueryResult NeighboringFilesQuery()
        {
            return { nullptr }; // TODO: Implement!
        }

    private:
    };
}
