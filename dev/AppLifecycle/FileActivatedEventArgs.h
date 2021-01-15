// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "ActivatedEventArgsBase.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::ApplicationModel::Activation;
    using namespace winrt::Windows::Storage;

    class FileActivatedEventArgs : public winrt::implements<FileActivatedEventArgs,
        ActivatedEventArgsBase, IFileActivatedEventArgs>
    {
    public:
        FileActivatedEventArgs(const std::wstring contractData)
        {
            if (contractData.empty())
            {
                throw std::invalid_argument("contractData");
            }

            m_kind = ActivationKind::File;

            auto delimPos = contractData.find_first_of(L",");
            m_verb = contractData.substr(0, delimPos);
            m_paths = contractData.substr(delimPos + 1);
            m_files = winrt::single_threaded_vector<IStorageItem>();

            // Currently we only support one file in the array, because the
            // activation method forces a new process for each item in the array.
            m_files.Append(StorageFile::GetFileFromPathAsync(m_paths.c_str()).get());
        }

        static IActivatedEventArgs CreateFromProtocol(IProtocolActivatedEventArgs const& protocolArgs)
        {
            auto query = protocolArgs.Uri().QueryParsed();
            std::wstring verb = query.GetFirstValueByName(L"Verb").c_str();
            std::wstring file = query.GetFirstValueByName(L"File").c_str();
            auto args = verb + L"," + file;
            return make<FileActivatedEventArgs>(args);
        }

        // IFileActivatedEventArgs
        IVectorView<IStorageItem> Files()
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
        IVector<IStorageItem> m_files;
    };
}
