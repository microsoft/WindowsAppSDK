// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include <winrt/Windows.Foundation.Collections.h>
#include <vector>
#include <utility>
#include "FileTypeFilterVector.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    // Forward declarations
    struct OrderedMapView;
    struct OrderedMapIterator;

    struct FileTypeChoicesMap : implements<FileTypeChoicesMap,
        winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>,
        winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>>>
    {
        FileTypeChoicesMap();

        bool ForFeature_StoragePickers2{ false };

        // IMap<hstring, IVector<hstring>>
        winrt::Windows::Foundation::Collections::IVector<hstring> Lookup(hstring const& key) const;
        uint32_t Size() const;
        bool HasKey(hstring const& key) const;
        winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> GetView() const;
        bool Insert(hstring const& key, winrt::Windows::Foundation::Collections::IVector<hstring> const& value);
        void Remove(hstring const& key);
        void Clear();

        // IIterable<IKeyValuePair<hstring, IVector<hstring>>>
        winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> First() const;

    private:
        // Use vector to maintain insertion order + hash map for O(1) lookup
        std::vector<std::pair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> m_orderedMap;
        std::unordered_map<std::wstring, size_t> m_keyToIndex; // Maps key to index in m_orderedMap

        // Helper methods
        auto FindKey(hstring const& key) const;
        auto FindKey(hstring const& key);
        size_t FindKeyIndex(hstring const& key) const;
    };

    // Custom iterator to maintain insertion order
    struct OrderedMapIterator : implements<OrderedMapIterator,
        winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>>>
    {
        using vector_type = std::vector<std::pair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>>;

        OrderedMapIterator(vector_type const& map) : m_map(map), m_current(0) {}

        winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> Current() const;
        bool HasCurrent() const;
        bool MoveNext();
        uint32_t GetMany(array_view<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> items);

    private:
        vector_type const& m_map;
        size_t m_current;
    };

    // Custom view to maintain insertion order  
    struct OrderedMapView : implements<OrderedMapView,
        winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>,
        winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>>>
    {
        using vector_type = std::vector<std::pair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>>;

        OrderedMapView(vector_type const& map) : m_map(map) {}

        // IMapView
        winrt::Windows::Foundation::Collections::IVector<hstring> Lookup(hstring const& key) const;
        uint32_t Size() const;
        bool HasKey(hstring const& key) const;
        void Split(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>& first,
                  winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>& second) const;

        // IIterable
        winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> First() const;

    private:
        vector_type const& m_map;
        vector_type::const_iterator FindKey(hstring const& key) const;
    };
}
