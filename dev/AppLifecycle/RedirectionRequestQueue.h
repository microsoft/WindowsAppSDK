// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once
#include "SharedMemory.h"
#include "RedirectionRequest.h"
#include <guiddef.h>
#include <FrameworkUdk/Containment.h>

// Bug 60972838: [1.8.6 servicing] Fix SharedMemory redirection queue and add telemetry events (PR#6127)
#define WINAPPSDK_CHANGEID_60972838 60972838, WinAppSDK_1_8_6

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    constexpr size_t c_queueSize = 4096;

    class RedirectionRequestQueue
    {
        struct QueueItem
        {
            bool inUse{ false };
            size_t next{ 0 };
            GUID id{ 0 };
        };

        // NOTE: SharedMemory layout
        // In shared memory, we store headpointer (sizeof(size_t)) followed by c_queueSize QueueItems.
        // But shared memory also stores the above requested size (head + queue) at the beginning of the memory
        //      See SharedMemory.h:
        //          Result of MapViewOfFile() is stored in m_view, which is of type DynamicSharedMemory<T>*.
        //          DynamicSharedMemory has a "size" member at the beginning, followed by "data" member.
        // m_data.Get() returns pointer to "data" member of above DynamicSharedMemory. This is our "usable" region i.e. head + queue.
        // So the overall layout in memory can be represented as below:
        // | DynamicSharedMemory.size |-------------------------- DynamicSharedMemory.data ---------------------------|
        //
        //                              m_data.Get() (start of head pointer storage)
        //                              v
        // | DynamicSharedMemory.size | head pointer | QueueItem[0] | QueueItem[1] | ... | QueueItem[c_queueSize - 1] |
        //                                             ^
        //                                             m_dataStart (first QueueItem in shared memory)

    public:
        void Init(const std::wstring& name)
        {
            m_name = name;

            if (!WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_60972838>())
            {
                // Legacy layout: head pointer + queue using pointer size for header
                m_data.Open(name, (sizeof(QueueItem) * 4096) + sizeof(QueueItem*));
#pragma warning(suppress: 6305) // PREFast does not know m_data.Get() is compatible with sizeof(size_t)
                m_dataStart = reinterpret_cast<QueueItem*>(m_data.Get() + sizeof(size_t));
                return;
            }

            // We store the head pointer at the beginning of the memory, and then items in the queue after.
            auto headPointerSizeInBytes = sizeof(size_t);
            auto queueSizeInBytes = sizeof(QueueItem) * c_queueSize;

            auto totalSharedMemoryDataSizeInBytes = queueSizeInBytes + headPointerSizeInBytes;

            m_data.Open(name, totalSharedMemoryDataSizeInBytes);

            auto sharedMemoryBase = reinterpret_cast<std::byte*>(m_data.Get());
            auto queueStartInSharedMemory = sharedMemoryBase + headPointerSizeInBytes;
            m_dataStart = reinterpret_cast<QueueItem*>(queueStartInSharedMemory);
        }

        void Enqueue(const GUID& itemId)
        {
            auto newItem = AllocateItem();
            auto cur = GetHead();

            if (cur != nullptr)
            {
                // Zero is never a valid offset, as the offset 0 is our head pointer offset.
                while (cur->next != 0)
                {
                    cur = FromOffset(cur->next);
                }
            }

            if (cur == nullptr)
            {
                // Enqueueing head.
                cur = newItem;
                SetHead(newItem);
            }
            else
            {
                // Appending to the queue.
                cur->next = ToOffset(newItem);
            }

            newItem->inUse = true;
            newItem->id = itemId;
            newItem->next = 0;
        }

        GUID Dequeue()
        {
            auto head = GetHead();
            if (head != nullptr)
            {
                SetHead(FromOffset(head->next));

                head->inUse = false;
                head->next = 0;

                return head->id;
            }

            return GUID_NULL;
        }

    private:
        size_t GetBaseAddress()
        {
            return reinterpret_cast<size_t>(m_data.Get());
        }

        QueueItem* FromOffset(size_t offset)
        {
            if (offset == 0)
            {
                return nullptr;
            }

            return reinterpret_cast<QueueItem*>(GetBaseAddress() + offset);
        }

        size_t ToOffset(QueueItem* item)
        {
            size_t offset{ 0 };
            if (item != nullptr)
            {
                offset = reinterpret_cast<size_t>(item) - GetBaseAddress();
            }
            return offset;
        }

        QueueItem* GetHead()
        {
            void** head = reinterpret_cast<void**>(m_data.Get());
            if (*head == nullptr)
            {
                return nullptr;
            }

            return FromOffset(reinterpret_cast<size_t>(*head));
        }

        void SetHead(QueueItem* value)
        {
            // Store as offset, since it's a pointer into shared memory.
            void** head = reinterpret_cast<void**>(m_data.Get());
            (*head) = reinterpret_cast<void*>(ToOffset(value));
        }

        QueueItem* AllocateItem()
        {
            if (!WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_60972838>())
            {
#pragma warning(suppress: 6305) // PREFast does not know upperBounds computed in byte count so compatible with sizeof(QueueItem)
                QueueItem* upperBounds = reinterpret_cast<QueueItem*>(m_data.Get()) + m_data.Size();
                auto cur = m_dataStart;

#pragma warning(suppress: 6305) // PREFast does not know cur computed in byte count so compatible with sizeof(QueueItem)
                while (cur < (upperBounds - sizeof(QueueItem)) && cur->inUse)
                {
#pragma warning(suppress: 6305)
                    cur += sizeof(QueueItem);
                }

#pragma warning(suppress: 6305)
                THROW_HR_IF(E_OUTOFMEMORY, cur >= (upperBounds - sizeof(QueueItem)));
                return cur;
            }

            // m_dataStart points to the first QueueItem in the shared memory.
            // The total size of the queue is c_queueSize items.
            // m_dataStart + c_queueSize will point to one past the end of the queue.
            // For example, if c_queueSize is 4, and m_dataStart is at address 0x22506a80010
            // then m_dataStart + c_queueSize is at address 0x0000022506a80090.
            // Valid items are at:
            //    0x0000022506a80010, 0x0000022506a80030, 0x0000022506a80050, 0x0000022506a80070
            // Since cur is of type QueueItem*, incrementing it moves by sizeof(QueueItem) in below loop.
            QueueItem* upperBounds = m_dataStart + c_queueSize;
            auto cur = m_dataStart;

            while (cur < upperBounds && cur->inUse)
            {
                cur++; // cur is of type QueueItem*, so ++ moves by sizeof(QueueItem).
            }

            THROW_HR_IF(E_OUTOFMEMORY, cur >= upperBounds);
            return cur;
        }

        std::wstring m_name;
        QueueItem* m_dataStart{ nullptr }; // First "QueueItem" in the shared memory after the head pointer.
        SharedMemory<size_t> m_data;
    };
}
