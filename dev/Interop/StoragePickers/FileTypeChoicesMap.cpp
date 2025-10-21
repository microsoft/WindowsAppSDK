// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "FileTypeChoicesMap.h"
#include "FileTypeFilterVector.h"
#include "TerminalVelocityFeatures-StoragePickers2.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    FileTypeChoicesMap::FileTypeChoicesMap()
    {
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
        
        return m_innerMap.Insert(key, validatingVector);
    }

    winrt::Windows::Foundation::Collections::IVector<hstring> FileTypeChoicesMap::Lookup(hstring const& key) const
    {
        return m_innerMap.Lookup(key);
    }

    uint32_t FileTypeChoicesMap::Size() const
    {
        return m_innerMap.Size();
    }

    bool FileTypeChoicesMap::HasKey(hstring const& key) const
    {
        return m_innerMap.HasKey(key);
    }

    winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> FileTypeChoicesMap::GetView() const
    {
        return m_innerMap.GetView();
    }

    void FileTypeChoicesMap::Remove(hstring const& key)
    {
        m_innerMap.Remove(key);
    }

    void FileTypeChoicesMap::Clear()
    {
        m_innerMap.Clear();
    }

    winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>> FileTypeChoicesMap::First() const
    {
        return m_innerMap.First();
    }
}
