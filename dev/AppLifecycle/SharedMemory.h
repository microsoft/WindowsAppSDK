// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

template <typename T>
struct DynamicSharedMemory
{
    size_t size{ 0 };
    T data{ 0 };
};

template <typename T>
class SharedMemory
{
public:
    SharedMemory() {}

    bool Open(const std::wstring& name, size_t size)
    {
        m_name = name;

        // OpenInternal needs to account for "size" member of DynamicSharedMemory struct.
        auto createdFile = OpenInternal(size + sizeof(size_t));
        if (createdFile)
        {
            Clear();

            // We only store size of the request.
            m_view.get()->size = size;
        }
        else
        {
            // file already exists, reopen with stored size.
            auto newSize = m_view.get()->size;
            m_view.reset();
            m_file.reset();

            // OpenInternal needs to account for "size" member of DynamicSharedMemory struct.
            OpenInternal(newSize + sizeof(size_t));
        }

        return createdFile;
    }

    bool Open(const std::wstring& name)
    {
        return Open(name, sizeof(T));
    }

    void Clear()
    {
        // Clear only the data portion, not the size.
        // and Size() accounts for only requested size. See comment in Open().
        memset(Get(), 0, Size());
    }

    void Resize(size_t size)
    {
        auto name = m_name;
        Reset();

        m_name = name;

        // OpenInternal needs to account for "size" member of DynamicSharedMemory struct.
        OpenInternal(size + sizeof(size_t));
        m_view.get()->size = size;
    }

    const size_t Size()
    {
        return m_view.get()->size;
    }

    T* Get()
    {
        return &m_view.get()->data;
    }

    T* operator->()
    {
        return Get();
    }

    void Reset()
    {
        m_name.erase();
        m_view.reset();
        m_file.reset();
    }

    bool IsValid()
    {
        return (m_name.size() != 0);
    }

protected:
    bool OpenInternal(size_t size)
    {
        m_file = wil::unique_handle(CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, static_cast<DWORD>(size), m_name.c_str()));
        THROW_LAST_ERROR_IF_NULL(m_file);

        bool createdFile = (GetLastError() != ERROR_ALREADY_EXISTS);
        m_view.reset(reinterpret_cast<DynamicSharedMemory<T>*>(MapViewOfFile(m_file.get(), FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, size)));
        THROW_LAST_ERROR_IF_NULL(m_view);

        return createdFile;
    }

	std::wstring m_name;
	wil::unique_handle m_file;
	wil::unique_mapview_ptr<DynamicSharedMemory<T>> m_view;
};
