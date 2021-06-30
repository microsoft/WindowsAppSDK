// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "ActivatedEventArgsBase.h"

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::ApplicationModel::Activation;
    using namespace winrt::Windows::Storage;

    constexpr PCWSTR c_fileContractId = L"Windows.File";

    class FileActivatedEventArgs : public winrt::implements<FileActivatedEventArgs, IFileActivatedEventArgs, ActivatedEventArgsBase,
        IInternalValueMarshalable>
    {
    public:
        FileActivatedEventArgs(const std::wstring verb, const std::wstring file, const bool delayVerification = false)
        {
            if (verb.empty())
            {
                throw std::invalid_argument("verb");
            }

            if (file.empty())
            {
                throw std::invalid_argument("file");
            }

            m_kind = ActivationKind::File;
            m_verb = std::move(verb);
            m_path = std::move(file);
            m_files = winrt::single_threaded_vector<IStorageItem>();

            // There is a scenario where we just want to create an object to serialize it.  In that situation
            // skipping verification allows for template variables to be used.  Example: %1 may be used when
            // using serialization to generate the encoded arguments for a file type association.
            if (!delayVerification)
            {
                // Currently we only support one file in the array, because the
                // activation method forces a new process for each item in the array.
                m_files.Append(StorageFile::GetFileFromPathAsync(m_path.c_str()).get());
            }
        }

        static winrt::Windows::Foundation::IInspectable Deserialize(winrt::Windows::Foundation::Uri const& uri)
        {
            auto query = uri.QueryParsed();
            auto verb = std::wstring(query.GetFirstValueByName(L"Verb"));
            auto file = std::wstring(query.GetFirstValueByName(L"File"));
            return make<FileActivatedEventArgs>(verb, file);
        }

        // IInternalValueMarshalable
        winrt::Windows::Foundation::Uri Serialize()
        {
            auto uri = GenerateEncodedLaunchUri(L"App", c_fileContractId);
            uri += L"&Verb=" + m_verb + std::wstring(L"&File=") + m_path;
            return winrt::Windows::Foundation::Uri(uri);
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
        std::wstring m_path;
        IVector<IStorageItem> m_files;
    };
}
