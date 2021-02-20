#pragma once

template <typename T>
class shared_memory
{
public:
    shared_memory() {}

	void open(std::wstring name)
	{
        // TODO: Security descriptor
        m_file = wil::unique_handle(CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(T), name.c_str()));
        THROW_LAST_ERROR_IF_NULL(m_file);

        bool created = (GetLastError() == ERROR_ALREADY_EXISTS) ? false : true;
        if (created)
        {
            m_access = FILE_MAP_READ | FILE_MAP_WRITE;
        }
        else
        {
            m_access = FILE_MAP_ALL_ACCESS;
        }

        m_view.reset(reinterpret_cast<T*>(MapViewOfFile(m_file.get(), m_access, 0, 0, sizeof(T))));
        THROW_LAST_ERROR_IF_NULL(m_view);

        if (created)
        {
            memset(m_view.get(), 0, sizeof(T));
        }
	}

    T* get()
    {
        return m_view.get();
    }

    DWORD get_access_level()
    {
        return m_access;
    }

    T* operator->()
    {
        return m_view.get();
    }

private:
    DWORD m_access = 0;
	std::wstring m_name;
	wil::unique_handle m_file;
	wil::unique_mapview_ptr<T> m_view;
};

