// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "shared_memory.h"
#include "Association.h"

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{

#define MAX_INSTANCE_COUNT 512
    typedef DWORD InstanceListData[MAX_INSTANCE_COUNT];

    class InstanceList
    {
    public:
        void init(const std::wstring& filename)
        {
            m_data.open(filename);
            m_view = std::move(winrt::array_view<DWORD>(reinterpret_cast<InstanceListData>(*m_data.get())));
        }

        void insert(DWORD processId)
        {
            for (DWORD index = 0 ; index < m_view.size() ; index++)
            {
                THROW_HR_IF(E_UNEXPECTED, m_view[index] == processId);
                if (m_view[index] == 0)
                {
                    m_view[index] = processId;
                    return;
                }
            }

            THROW_HR(E_OUTOFMEMORY);
        }

        void remove(DWORD processId)
        {
            for (DWORD index = 0; index < m_view.size(); index++)
            {
                if (m_view[index] == processId)
                {
                    m_view[index] = 0;
                    return;
                }
            }

            return;
        }

        DWORD size()
        {
            return m_view.size();
        }

        DWORD operator[](int index)
        {
            return m_view[index];
        }

    private:
        shared_memory<InstanceListData> m_data;
        winrt::array_view<DWORD> m_view;
    };
}
