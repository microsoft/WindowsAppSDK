// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "ActivatedEventArgsBase.h"

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::ApplicationModel::Activation;

    class FileActivatedEventArgs : public winrt::implements<FileActivatedEventArgs,
        ActivatedEventArgsBase, IFileActivatedEventArgs>
    {
    public:
        FileActivatedEventArgs([[maybe_unused]] const std::wstring contractData)
        {
            if (contractData.empty())
            {
                throw std::invalid_argument("contractData");
            }

            m_kind = ActivationKind::File;

            auto delimPos = contractData.find_first_of(L",");
            m_verb = contractData.substr(0, delimPos);
            m_paths = contractData.substr(delimPos + 1);
            m_files = winrt::single_threaded_vector<winrt::Windows::Storage::IStorageItem>();

            //  TODO: Support multiple files?
            m_files.Append(winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(m_paths.c_str()).get());

        }

        // IFileActivatedEventArgs
        IVectorView<Windows::Storage::IStorageItem> Files()
        {
            return m_files.GetView();
        }

        winrt::hstring Verb()
        {
            return m_verb.c_str();
        }

    private:
        std::wstring m_verb;
        std::wstring m_paths;
        IVector<winrt::Windows::Storage::IStorageItem> m_files;
    };
}
