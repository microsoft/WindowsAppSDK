// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include <winrt/Windows.Foundation.Collections.h>
#include "FileTypeFilterVector.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
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
        winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> m_innerMap{
            single_threaded_map<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>() };
    };
}
