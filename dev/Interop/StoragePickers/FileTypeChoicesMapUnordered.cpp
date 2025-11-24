// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "FileTypeChoicesMapUnordered.h"
#include "FileTypeFilterVector.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    FileTypeChoicesMapUnordered::FileTypeChoicesMapUnordered()
    {
    }

    bool FileTypeChoicesMapUnordered::Insert(hstring const& key, winrt::Windows::Foundation::Collections::IVector<hstring> const& value)
    {
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
        
        return m_innerMap.Insert(key, validatingVector);
    }

    winrt::Windows::Foundation::Collections::IVector<hstring> FileTypeChoicesMapUnordered::Lookup(hstring const& key) const
    {
        return m_innerMap.Lookup(key);
    }

    uint32_t FileTypeChoicesMapUnordered::Size() const
    {
        return m_innerMap.Size();
    }

    bool FileTypeChoicesMapUnordered::HasKey(hstring const& key) const
    {
        return m_innerMap.HasKey(key);
    }

    winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> FileTypeChoicesMapUnordered::GetView() const
    {
        return m_innerMap.GetView();
    }

    void FileTypeChoicesMapUnordered::Remove(hstring const& key)
    {
        m_innerMap.Remove(key);
    }

    void FileTypeChoicesMapUnordered::Clear()
    {
        m_innerMap.Clear();
    }

    winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> FileTypeChoicesMapUnordered::First() const
    {
        return m_innerMap.First();
    }
}
