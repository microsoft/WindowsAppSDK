// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "FileTypeChoicesMap.h"
#include "FileTypeFilterVector.h"
#include "TerminalVelocityFeatures-StoragePickers2.h"
#include <algorithm>
#include <unordered_map>

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    FileTypeChoicesMap::FileTypeChoicesMap()
    {
    }

    size_t FileTypeChoicesMap::FindKeyIndex(hstring const& key) const
    {
        auto it = m_keyToIndex.find(std::wstring(key.c_str()));
        return (it != m_keyToIndex.end()) ? it->second : SIZE_MAX;
    }

    auto FileTypeChoicesMap::FindKey(hstring const& key) const
    {
        size_t index = FindKeyIndex(key);
        return (index != SIZE_MAX) ? m_orderedMap.begin() + index : m_orderedMap.end();
    }

    auto FileTypeChoicesMap::FindKey(hstring const& key)
    {
        size_t index = FindKeyIndex(key);
        return (index != SIZE_MAX) ? m_orderedMap.begin() + index : m_orderedMap.end();
    }

    bool FileTypeChoicesMap::Insert(hstring const& key, winrt::Windows::Foundation::Collections::IVector<hstring> const& value)
    {
        if (ForFeature_StoragePickers2)
        {
            THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        }

        // Create a new FileTypeFilterVector and copy all values from the input vector
        auto validatingVector = make<FileTypeFilterVector>();

        if (value)
        {
            // Each Append call will validate the extension
            for (auto const& item : value)
            {
                validatingVector.as<winrt::Windows::Foundation::Collections::IVector<hstring>>().Append(item);
            }
        }

        // Check if key already exists using O(1) lookup
        size_t index = FindKeyIndex(key);
        if (index != SIZE_MAX)
        {
            // Key exists, update the value
            m_orderedMap[index].second = validatingVector;
            return false; // Indicates replacement, not insertion
        }
        else
        {
            // Key doesn't exist, insert new pair at the end to maintain insertion order
            size_t newIndex = m_orderedMap.size();
            m_orderedMap.emplace_back(key, validatingVector);
            m_keyToIndex[std::wstring(key.c_str())] = newIndex;
            return true; // Indicates new insertion
        }
    }

    winrt::Windows::Foundation::Collections::IVector<hstring> FileTypeChoicesMap::Lookup(hstring const& key) const
    {
        auto it = FindKey(key);
        if (it != m_orderedMap.end())
        {
            return it->second;
        }
        throw winrt::hresult_out_of_bounds(L"Key not found");
    }

    uint32_t FileTypeChoicesMap::Size() const
    {
        return static_cast<uint32_t>(m_orderedMap.size());
    }

    bool FileTypeChoicesMap::HasKey(hstring const& key) const
    {
        return FindKey(key) != m_orderedMap.end();
    }

    winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> FileTypeChoicesMap::GetView() const
    {
        return make<OrderedMapView>(m_orderedMap);
    }

    void FileTypeChoicesMap::Remove(hstring const& key)
    {
        size_t index = FindKeyIndex(key);
        if (index != SIZE_MAX)
        {
            // Remove from vector
            m_orderedMap.erase(m_orderedMap.begin() + index);
            
            // Remove from hash map
            m_keyToIndex.erase(std::wstring(key.c_str()));
            
            // Update indices for all elements after the removed one
            for (auto& kvp : m_keyToIndex)
            {
                if (kvp.second > index)
                {
                    kvp.second--;
                }
            }
        }
    }

    void FileTypeChoicesMap::Clear()
    {
        m_orderedMap.clear();
        m_keyToIndex.clear();
    }

    winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> FileTypeChoicesMap::First() const
    {
        return make<OrderedMapIterator>(m_orderedMap);
    }

    // OrderedMapIterator implementation
    winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> OrderedMapIterator::Current() const
    {
        if (m_current >= m_map.size())
        {
            throw winrt::hresult_out_of_bounds();
        }
        // Create a simple key-value pair
        auto tempMap = single_threaded_map<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>();
        tempMap.Insert(m_map[m_current].first, m_map[m_current].second);
        return tempMap.First().Current();
    }

    bool OrderedMapIterator::HasCurrent() const
    {
        return m_current < m_map.size();
    }

    bool OrderedMapIterator::MoveNext()
    {
        if (m_current < m_map.size())
        {
            ++m_current;
            return m_current < m_map.size();
        }
        return false;
    }

    uint32_t OrderedMapIterator::GetMany(array_view<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> items)
    {
        uint32_t copied = 0;
        while (copied < items.size() && HasCurrent())
        {
            items[copied] = Current();
            MoveNext();
            ++copied;
        }
        return copied;
    }

    // OrderedMapView implementation
    auto OrderedMapView::FindKey(hstring const& key) const -> vector_type::const_iterator
    {
        return std::find_if(m_map.begin(), m_map.end(),
            [&key](const auto& pair) { return pair.first == key; });
    }

    winrt::Windows::Foundation::Collections::IVector<hstring> OrderedMapView::Lookup(hstring const& key) const
    {
        auto it = FindKey(key);
        if (it != m_map.end())
        {
            return it->second;
        }
        throw winrt::hresult_out_of_bounds(L"Key not found");
    }

    uint32_t OrderedMapView::Size() const
    {
        return static_cast<uint32_t>(m_map.size());
    }

    bool OrderedMapView::HasKey(hstring const& key) const
    {
        return FindKey(key) != m_map.end();
    }

    void OrderedMapView::Split(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>& first,
                              winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>& second) const
    {
        // For simplicity, not implementing split
        first = nullptr;
        second = nullptr;
    }

    winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> OrderedMapView::First() const
    {
        return make<OrderedMapIterator>(m_map);
    }
}
