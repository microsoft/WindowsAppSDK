// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <map>
#include <shared_mutex>

namespace impl
{
    template <typename T>
    inline T default_value()
    {
        if constexpr (std::is_constructible_v<T, std::nullptr_t>)
        {
            // Handles classes where we'd otherwise get activation
            return T{ nullptr };
        }
        else
        {
            return T{};
        }
    }

    template <typename KeyT, typename ValueT>
    struct KeyValuePair : winrt::implements<KeyValuePair<KeyT, ValueT>, collections::IKeyValuePair<KeyT, ValueT>>
    {
        KeyValuePair(KeyT key, ValueT value) :
            m_key(std::move(key)),
            m_value(std::move(value))
        {
        }

        KeyT Key()
        {
            return m_key;
        }

        ValueT Value()
        {
            return m_value;
        }

    private:

        KeyT m_key;
        ValueT m_value;
    };

    template <typename Map, typename KeyT, typename ValueT>
    struct LockableMapIterator : winrt::implements<LockableMapIterator<Map, KeyT, ValueT>,
        collections::IIterator<collections::IKeyValuePair<KeyT, ValueT>>>
    {
        LockableMapIterator(winrt::com_ptr<Map> map, std::size_t version) : m_map(std::move(map)), m_version(version)
        {
            m_itr = m_map->m_map.begin();
        }

        // IIterator
        collections::IKeyValuePair<KeyT, ValueT> Current()
        {
            std::shared_lock guard{ m_map->m_mutex };
            check_version();
            if (m_itr == m_map->m_map.end())
            {
                throw winrt::hresult_out_of_bounds();
            }

            return winrt::make<KeyValuePair<KeyT, ValueT>>(m_itr->first, m_itr->second);
        }

        bool HasCurrent()
        {
            std::shared_lock guard{ m_map->m_mutex };
            check_version();
            return m_itr != m_map->m_map.end();
        }

        std::uint32_t GetMany(winrt::array_view<collections::IKeyValuePair<KeyT, ValueT>> items)
        {
            std::shared_lock guard{ m_map->m_mutex };
            check_version();

            auto end = m_map->m_map.end();
            std::uint32_t result = 0;
            for (; (m_itr != end) && (result < items.size()); ++m_itr)
            {
                items[result++] = winrt::make<KeyValuePair<KeyT, ValueT>>(m_itr->first, m_itr->second);
            }

            return result;
        }

        bool MoveNext()
        {
            std::shared_lock guard{ m_map->m_mutex };
            check_version();

            auto end = m_map->m_map.end();
            if (m_itr != end)
            {
                ++m_itr;
            }

            return m_itr != end;
        }

    private:
        void check_version()
        {
            if (m_version != m_map->m_version)
            {
                throw winrt::hresult_changed_state();
            }
        }

        winrt::com_ptr<Map> m_map;
        std::size_t m_version;
        typename std::map<KeyT, ValueT>::const_iterator m_itr;
    };

    template <typename Map, typename KeyT, typename ValueT>
    struct LockableMapView : winrt::implements<LockableMapView<Map, KeyT, ValueT>,
        collections::IMapView<KeyT, ValueT>,
        collections::IIterable<collections::IKeyValuePair<KeyT, ValueT>>>
    {
        LockableMapView(winrt::com_ptr<Map> map, std::size_t version) : m_map(std::move(map)), m_version(version)
        {
        }

        // IMapView
        std::uint32_t Size()
        {
            std::shared_lock guard{ m_map->m_mutex };
            check_version();
            return static_cast<std::uint32_t>(m_map->m_map.size());
        }

        bool HasKey(const KeyT& key)
        {
            std::shared_lock guard{ m_map->m_mutex };
            check_version();
            return m_map->m_map.find(key) != m_map->m_map.end();
        }

        ValueT Lookup(const KeyT& key)
        {
            std::shared_lock guard{ m_map->m_mutex };
            check_version();
            auto itr = m_map->m_map.find(key);
            if (itr == m_map->m_map.end())
            {
                throw winrt::hresult_out_of_bounds();
            }

            return itr->second;
        }

        void Split(collections::IMapView<KeyT, ValueT>& lhs, collections::IMapView<KeyT, ValueT>& rhs)
        {
            // NOTE: Follows C++/WinRT implementation
            lhs = nullptr;
            rhs = nullptr;
        }

        // IIterable
        collections::IIterator<collections::IKeyValuePair<KeyT, ValueT>> First()
        {
            std::shared_lock guard{ m_map->m_mutex };
            return winrt::make<LockableMapIterator<Map, KeyT, ValueT>>(m_map, m_version);
        }

    private:
        void check_version()
        {
            if (m_version != m_map->m_version)
            {
                throw winrt::hresult_changed_state();
            }
        }

        winrt::com_ptr<Map> m_map;
        std::size_t m_version;
    };
}

// Here, "lock" means "prevent further modification." Of course, the objects contained within the map can modified, but
// nothing can be added/removed from the map
template <typename KeyT, typename ValueT>
struct LockableMap : winrt::implements<LockableMap<KeyT, ValueT>,
    collections::IMap<KeyT, ValueT>,
    collections::IIterable<collections::IKeyValuePair<KeyT, ValueT>>>
{
    friend struct impl::LockableMapIterator<LockableMap, KeyT, ValueT>;
    friend struct impl::LockableMapView<LockableMap, KeyT, ValueT>;

    // IMap
    std::uint32_t Size()
    {
        std::shared_lock guard{ m_mutex };
        return static_cast<std::uint32_t>(m_map.size());
    }

    void Clear()
    {
        std::map<KeyT, ValueT> oldValues; // Release outside of lock

        std::lock_guard guard{ m_mutex };
        check_not_locked();
        m_map.swap(oldValues);
        ++m_version;
    }

    collections::IMapView<KeyT, ValueT> GetView()
    {
        std::shared_lock guard{ m_mutex };
        return winrt::make<impl::LockableMapView<LockableMap, KeyT, ValueT>>(this->get_strong(), m_version);
    }

    bool HasKey(const KeyT& value)
    {
        std::shared_lock guard{ m_mutex };
        return m_map.find(value) != m_map.end();
    }

    bool Insert(const KeyT& key, const ValueT& value)
    {
        auto removedValue = impl::default_value<ValueT>();

        std::lock_guard guard{ m_mutex };
        check_not_locked();
        auto [itr, added] = m_map.emplace(key, value);
        if (!added)
        {
            std::swap(removedValue, itr->second);
            itr->second = value;
        }
        ++m_version;

        return !added;
    }

    ValueT Lookup(const KeyT& key)
    {
        std::shared_lock guard{ m_mutex };
        auto itr = m_map.find(key);
        if (itr == m_map.end())
        {
            throw winrt::hresult_out_of_bounds();
        }
        return itr->second;
    }

    void Remove(const KeyT& key)
    {
        typename std::map<KeyT, ValueT>::node_type node; // Destroy outside of lock

        {
            std::lock_guard guard{ m_mutex };
            check_not_locked();
            node = m_map.extract(key);
            ++m_version;
        }

        if (!node)
        {
            throw winrt::hresult_out_of_bounds();
        }
    }

    // IIterable
    collections::IIterator<collections::IKeyValuePair<KeyT, ValueT>> First()
    {
        std::shared_lock guard{ m_mutex };
        return winrt::make<impl::LockableMapIterator<LockableMap, KeyT, ValueT>>(this->get_strong(), m_version);
    }

    // Implementation Functions
    void lock()
    {
        std::lock_guard guard{ m_mutex };
        if (m_locked)
        {
            throw winrt::hresult_illegal_method_call(L"Map has already been locked from modification");
        }

        m_locked = true;
    }

private:
    void check_not_locked()
    {
        // NOTE: Lock should be held when calling
        if (m_locked)
        {
            throw winrt::hresult_illegal_method_call(L"Map has been locked from modification");
        }
    }

    std::shared_mutex m_mutex;
    std::size_t m_version = 0;
    bool m_locked = false;
    std::map<KeyT, ValueT> m_map;
};
