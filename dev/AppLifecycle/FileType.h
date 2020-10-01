// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "AssocCommon.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    class FileType
    {
    public:
        FileType(std::wstring extension)
        {
            if (extension.empty() || extension.at(0) != L'.')
            {
                throw winrt::hresult_invalid_argument();
            }

            m_extension = extension;
            Load();
        }

        ~FileType()
        {
            Save();
        }

        void Load();
        void Save();

        std::wstring Extension() { return m_extension; }

        std::wstring DefaultProgId() { return m_defaultProgId; }
        void DefaultProgId(const std::wstring value) { m_defaultProgId = value; }

        std::list<std::pair<std::wstring, std::wstring>> OpenWithProgIds() { return m_openWithProgIds; }
        void OpenWithProgIds(std::list<std::pair<std::wstring, std::wstring>> values) { m_openWithProgIds = values; }

    private:
        FileType() = delete;

        std::wstring m_extension;
        std::wstring m_defaultProgId;
        std::list<std::pair<std::wstring, std::wstring>> m_openWithProgIds;
    };
}

