// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "FileTypeChoicesMap.h"
#include "FileTypeFilterVector.h"
#include "TerminalVelocityFeatures-StoragePickers2.h"
#include <memory>

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    FileTypeChoicesMap::FileTypeChoicesMap()
        : m_orderedMap(std::make_shared<FileTypeChoiceVector>())
    {
        // Pre-allocate capacity for typical file type choices (usually 2-8 items)
        m_orderedMap->reserve(8);
    }

    FileTypeChoiceVector::const_iterator FileTypeChoicesMap::FindKey(hstring const& key) const noexcept
    {
        for (auto it = m_orderedMap->cbegin(); it != m_orderedMap->cend(); ++it)
        {
            if (it->first == key)
            {
                return it;
            }
        }
        return m_orderedMap->cend();
    }

    FileTypeChoiceVector::iterator FileTypeChoicesMap::FindKey(hstring const& key) noexcept
    {
        for (auto it = m_orderedMap->begin(); it != m_orderedMap->end(); ++it)
        {
            if (it->first == key)
            {
                return it;
            }
        }
        return m_orderedMap->end();
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

        // Check if key already exists; vector is small so linear scan is sufficient
        auto existing = FindKey(key);
        if (existing != m_orderedMap->end())
        {
            // Key exists, update the value
            existing->second = validatingVector;
            return false; // Indicates replacement, not insertion
        }
        else
        {
            // Key doesn't exist, insert new pair at the end to maintain insertion order
            m_orderedMap->emplace_back(key, validatingVector);
            return true; // Indicates new insertion
        }
    }

    winrt::Windows::Foundation::Collections::IVector<hstring> FileTypeChoicesMap::Lookup(hstring const& key) const
    {
        auto it = FindKey(key);
        if (it != m_orderedMap->cend())
        {
            return it->second;
        }
        throw winrt::hresult_out_of_bounds(L"Key not found");
    }

    uint32_t FileTypeChoicesMap::Size() const noexcept
    {
        return static_cast<uint32_t>(m_orderedMap->size());
    }

    bool FileTypeChoicesMap::HasKey(hstring const& key) const noexcept
    {
        return FindKey(key) != m_orderedMap->cend();
    }

    winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> FileTypeChoicesMap::GetView() const
    {
        return make<OrderedMapView>(m_orderedMap);
    }

    void FileTypeChoicesMap::Remove(hstring const& key)
    {
        auto it = FindKey(key);
        if (it != m_orderedMap->end())
        {
            // Remove from vector
            m_orderedMap->erase(it);
        }
    }

    void FileTypeChoicesMap::Clear()
    {
        m_orderedMap->clear();
    }

    winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> FileTypeChoicesMap::First() const
    {
        return make<OrderedMapIterator>(m_orderedMap);
    }

    // OrderedMapIterator implementation
    winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> OrderedMapIterator::Current() const
    {
        if (!m_map || m_current >= m_map->size())
        {
            throw winrt::hresult_out_of_bounds();
        }
        // Create a simple key-value pair
        auto tempMap = single_threaded_map<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>();
        tempMap.Insert((*m_map)[m_current].first, (*m_map)[m_current].second);
        return tempMap.First().Current();
    }

    bool OrderedMapIterator::HasCurrent() const noexcept
    {
        return m_map && m_current < m_map->size();
    }

    bool OrderedMapIterator::MoveNext() noexcept
    {
        if (m_map && m_current < m_map->size())
        {
            ++m_current;
            return m_current < m_map->size();
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
    FileTypeChoiceVector::const_iterator OrderedMapView::FindKey(hstring const& key) const noexcept
    {
        if (!m_map)
        {
            return FileTypeChoiceVector::const_iterator{};
        }
        for (auto it = m_map->cbegin(); it != m_map->cend(); ++it)
        {
            if (it->first == key)
            {
                return it;
            }
        }
        return m_map->cend();
    }

    winrt::Windows::Foundation::Collections::IVector<hstring> OrderedMapView::Lookup(hstring const& key) const
    {
        if (!m_map)
        {
            throw winrt::hresult_error(E_ILLEGAL_METHOD_CALL, L"Map view is no longer valid");
        }

        auto it = FindKey(key);
        if (it != m_map->end())
        {
            return it->second;
        }
        throw winrt::hresult_out_of_bounds(L"Key not found");
    }

    uint32_t OrderedMapView::Size() const
    {
        return m_map ? static_cast<uint32_t>(m_map->size()) : 0;
    }

    bool OrderedMapView::HasKey(hstring const& key) const noexcept
    {
        if (!m_map)
        {
            return false;
        }
        return FindKey(key) != m_map->end();
    }

    void OrderedMapView::Split(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>& first,
        winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>& second) const noexcept
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
