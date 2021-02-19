#pragma once

template <typename T>
class shared_memory
{
public:
    shared_memory() {}

    void open(std::wstring name)
    {
        m_size = sizeof(T);

        std::wstring mutexName = name + L"_Mutex";
        m_mutex.create(mutexName.c_str(), CREATE_MUTEX_INITIAL_OWNER, MUTEX_ALL_ACCESS);
        bool createdMutex = (GetLastError() != ERROR_ALREADY_EXISTS);

        wil::mutex_release_scope_exit releaseOnExit;
        if (createdMutex)
        {
            releaseOnExit = m_mutex.ReleaseMutex_scope_exit();
        }
        else
        {
            releaseOnExit = m_mutex.acquire();
        }

        // TODO: Security descriptor
        m_file = wil::unique_handle(CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, m_size, name.c_str()));
        THROW_LAST_ERROR_IF_NULL(m_file);

        bool createdFile = (GetLastError() != ERROR_ALREADY_EXISTS);
        assert(createdMutex == createdFile);

        if (createdFile)
        {
            m_access = FILE_MAP_READ | FILE_MAP_WRITE;
        }
        else
        {
            m_access = FILE_MAP_ALL_ACCESS; // TODO: I can't remember why I did it this way.  Go with least privs and see what breaks and why.  Then document.
        }

        m_view.reset(reinterpret_cast<T*>(MapViewOfFile(m_file.get(), m_access, 0, 0, m_size)));
        THROW_LAST_ERROR_IF_NULL(m_view);

        if (createdFile)
        {
            memset(m_view.get(), 0, m_size);
        }
    }

    DWORD size()
    {
        return m_size;
    }

    DWORD get_access_level()
    {
        return m_access;
    }

    T* get()
    {
        return m_view.get();
    }

    T* operator->()
    {
        return m_view.get();
    }

    std::tuple<wil::mutex_release_scope_exit, T*>& get_locked()
    {
        return { std::move(m_mutex.acquire()), get() };
    }

private:
    DWORD m_size{ 0 };
    DWORD m_access{ 0 };
	std::wstring m_name;
    wil::unique_mutex m_mutex;
	wil::unique_handle m_file;
	wil::unique_mapview_ptr<T> m_view;
};

