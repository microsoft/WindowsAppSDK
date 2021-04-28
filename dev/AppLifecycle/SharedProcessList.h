// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "SharedMemory.h"
#include "Association.h"

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{

#define MAX_INSTANCE_COUNT 512
    typedef DWORD SharedProcessListData[MAX_INSTANCE_COUNT];

    class SharedProcessList
    {
    public:
        void Init(const std::wstring& filename)
        {
            m_data.Open(filename);
            m_view = std::move(winrt::array_view<DWORD>(reinterpret_cast<SharedProcessListData>(*m_data.Get())));
        }

        void Insert(DWORD processId)
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

        void Remove(DWORD processId)
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

        DWORD Size()
        {
            return m_view.size();
        }

        DWORD operator[](int index)
        {
            return m_view[index];
        }

    private:
        SharedMemory<SharedProcessListData> m_data;
        winrt::array_view<DWORD> m_view;
    };
}
