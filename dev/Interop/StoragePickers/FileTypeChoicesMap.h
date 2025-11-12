// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include <winrt/Windows.Foundation.Collections.h>
#include <vector>
#include <utility>
#include <memory>
#include "FileTypeFilterVector.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    // Forward declarations
    struct OrderedMapView;
    struct OrderedMapIterator;

    using FileTypeChoiceEntry = std::pair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>;
    using FileTypeChoiceVector = std::vector<FileTypeChoiceEntry>;

    struct FileTypeChoicesMap : implements<FileTypeChoicesMap,
        winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>,
        winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>>>
    {
        FileTypeChoicesMap();

        bool ForFeature_StoragePickers2{ false };

        // IMap<hstring, IVector<hstring>>
        winrt::Windows::Foundation::Collections::IVector<hstring> Lookup(hstring const& key) const;
        uint32_t Size() const noexcept;
        bool HasKey(hstring const& key) const noexcept;
        winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> GetView() const;
        bool Insert(hstring const& key, winrt::Windows::Foundation::Collections::IVector<hstring> const& value);
        void Remove(hstring const& key);
        void Clear();

        // IIterable<IKeyValuePair<hstring, IVector<hstring>>>
        winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> First() const;

    private:
        // Shared ownership keeps insertion-ordered entries alive for any outstanding views/iterators.
        std::shared_ptr<FileTypeChoiceVector> m_orderedMap;

        // Helper methods
        FileTypeChoiceVector::const_iterator FindKey(hstring const& key) const noexcept;
        FileTypeChoiceVector::iterator FindKey(hstring const& key) noexcept;
    };

    // Custom iterator to maintain insertion order
    struct OrderedMapIterator : implements<OrderedMapIterator,
        winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>>>
    {
        OrderedMapIterator(std::shared_ptr<FileTypeChoiceVector const> map) : m_map(std::move(map)), m_current(0) {}

        winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> Current() const;
        bool HasCurrent() const noexcept;
        bool MoveNext() noexcept;
        uint32_t GetMany(array_view<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> items);

    private:
        std::shared_ptr<FileTypeChoiceVector const> m_map;
        size_t m_current;
    };

    // Custom view to maintain insertion order  
    struct OrderedMapView : implements<OrderedMapView,
        winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>,
        winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>>>
    {
        OrderedMapView(std::shared_ptr<FileTypeChoiceVector const> map) : m_map(std::move(map)) {}

        // IMapView
        winrt::Windows::Foundation::Collections::IVector<hstring> Lookup(hstring const& key) const;
        uint32_t Size() const;
        bool HasKey(hstring const& key) const noexcept;
        void Split(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>& first,
            winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>& second) const noexcept;

        // IIterable
        winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> First() const;

    private:
        std::shared_ptr<FileTypeChoiceVector const> m_map;
        FileTypeChoiceVector::const_iterator FindKey(hstring const& key) const noexcept;
    };
}
