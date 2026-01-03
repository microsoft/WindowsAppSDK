// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once
#include "SharedMemory.h"
#include "RedirectionRequest.h"
#include <guiddef.h>

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    constexpr size_t c_queueSize = 4;

    class RedirectionRequestQueue
    {
        struct QueueItem
        {
            bool inUse{ false };
            size_t next{ 0 };
            GUID id{ 0 };
        };


    public:
        void Init(const std::wstring& name)
        {
            __debugbreak();
            m_name = name;

            // We store the head pointer at the beginning of the memory, and then items in the queue after.
            auto headPointerSizeInBytes = sizeof(size_t);
            auto queueSizeInBytes = sizeof(QueueItem) * c_queueSize;

            auto totalSharedMemoryDataSizeInBytes = queueSizeInBytes + headPointerSizeInBytes;

            m_data.Open(name, totalSharedMemoryDataSizeInBytes);

// TBR? #pragma warning(suppress: 6305) // C6305: PREFast does not know m_data.Get() is compatible with "sizeof(size_t)".
            auto sharedMemoryBase = reinterpret_cast<std::byte*>(m_data.Get());
            auto queueStartInSharedMemory = sharedMemoryBase + headPointerSizeInBytes;
            m_dataStart = reinterpret_cast<QueueItem*>(queueStartInSharedMemory);
        }

        void Enqueue(const GUID& itemId)
        {
            //__debugbreak();
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
            //__debugbreak();
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
            __debugbreak();
            QueueItem* upperBounds = m_dataStart + c_queueSize;
            auto cur = m_dataStart;

            while (cur < upperBounds && cur->inUse)
            {
                cur++;
            }

            THROW_HR_IF(E_OUTOFMEMORY, cur >= upperBounds);
            return cur;
        }

        std::wstring m_name;
        QueueItem* m_dataStart{ nullptr }; // First "QueueItem" in the shared memory after the head pointer.
        SharedMemory<size_t> m_data;
    };
}
