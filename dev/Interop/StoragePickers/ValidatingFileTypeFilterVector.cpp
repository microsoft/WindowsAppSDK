// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ValidatingFileTypeFilterVector.h"
#include "PickerCommon.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    ValidatingFileTypeFilterVector::ValidatingFileTypeFilterVector()
    {
    }

    void ValidatingFileTypeFilterVector::SetAt(uint32_t index, hstring const& value)
    {
        PickerCommon::ValidateSingleFileTypeFilterElement(value);
        m_innerVector.SetAt(index, value);
    }

    void ValidatingFileTypeFilterVector::InsertAt(uint32_t index, hstring const& value)
    {
        PickerCommon::ValidateSingleFileTypeFilterElement(value);
        m_innerVector.InsertAt(index, value);
    }

    void ValidatingFileTypeFilterVector::Append(hstring const& value)
    {
        PickerCommon::ValidateSingleFileTypeFilterElement(value);
        m_innerVector.Append(value);
    }

    void ValidatingFileTypeFilterVector::ReplaceAll(array_view<hstring const> items)
    {
        // Validate all items before replacing
        for (auto const& item : items)
        {
            PickerCommon::ValidateSingleFileTypeFilterElement(item);
        }
        m_innerVector.ReplaceAll(items);
    }

    hstring ValidatingFileTypeFilterVector::GetAt(uint32_t index) const
    {
        return m_innerVector.GetAt(index);
    }

    uint32_t ValidatingFileTypeFilterVector::Size() const
    {
        return m_innerVector.Size();
    }

    winrt::Windows::Foundation::Collections::IVectorView<hstring> ValidatingFileTypeFilterVector::GetView() const
    {
        return m_innerVector.GetView();
    }

    bool ValidatingFileTypeFilterVector::IndexOf(hstring const& value, uint32_t& index) const
    {
        return m_innerVector.IndexOf(value, index);
    }

    void ValidatingFileTypeFilterVector::RemoveAt(uint32_t index)
    {
        m_innerVector.RemoveAt(index);
    }

    void ValidatingFileTypeFilterVector::RemoveAtEnd()
    {
        m_innerVector.RemoveAtEnd();
    }

    void ValidatingFileTypeFilterVector::Clear()
    {
        m_innerVector.Clear();
    }

    uint32_t ValidatingFileTypeFilterVector::GetMany(uint32_t startIndex, array_view<hstring> items) const
    {
        return m_innerVector.GetMany(startIndex, items);
    }

    winrt::Windows::Foundation::Collections::IIterator<hstring> ValidatingFileTypeFilterVector::First() const
    {
        return m_innerVector.First();
    }
}
