// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "FileTypeFilterVector.h"
#include "PickerCommon.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    FileTypeFilterVector::FileTypeFilterVector()
    {
    }

    void FileTypeFilterVector::SetAt(uint32_t index, hstring const& value)
    {
        PickerCommon::ValidateSingleFileTypeFilterElement(value);
        m_innerVector.SetAt(index, value);
    }

    void FileTypeFilterVector::InsertAt(uint32_t index, hstring const& value)
    {
        PickerCommon::ValidateSingleFileTypeFilterElement(value);
        m_innerVector.InsertAt(index, value);
    }

    void FileTypeFilterVector::Append(hstring const& value)
    {
        PickerCommon::ValidateSingleFileTypeFilterElement(value);
        m_innerVector.Append(value);
    }

    void FileTypeFilterVector::ReplaceAll(array_view<hstring const> items)
    {
        // Validate all items before replacing
        for (auto const& item : items)
        {
            PickerCommon::ValidateSingleFileTypeFilterElement(item);
        }
        m_innerVector.ReplaceAll(items);
    }

    hstring FileTypeFilterVector::GetAt(uint32_t index) const
    {
        return m_innerVector.GetAt(index);
    }

    uint32_t FileTypeFilterVector::Size() const
    {
        return m_innerVector.Size();
    }

    winrt::Windows::Foundation::Collections::IVectorView<hstring> FileTypeFilterVector::GetView() const
    {
        return m_innerVector.GetView();
    }

    bool FileTypeFilterVector::IndexOf(hstring const& value, uint32_t& index) const
    {
        return m_innerVector.IndexOf(value, index);
    }

    void FileTypeFilterVector::RemoveAt(uint32_t index)
    {
        m_innerVector.RemoveAt(index);
    }

    void FileTypeFilterVector::RemoveAtEnd()
    {
        m_innerVector.RemoveAtEnd();
    }

    void FileTypeFilterVector::Clear()
    {
        m_innerVector.Clear();
    }

    uint32_t FileTypeFilterVector::GetMany(uint32_t startIndex, array_view<hstring> items) const
    {
        return m_innerVector.GetMany(startIndex, items);
    }

    winrt::Windows::Foundation::Collections::IIterator<hstring> FileTypeFilterVector::First() const
    {
        return m_innerVector.First();
    }
}
