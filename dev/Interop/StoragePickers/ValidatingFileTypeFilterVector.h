// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include <winrt/Windows.Foundation.Collections.h>
// #include "PickerCommon.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    struct ValidatingFileTypeFilterVector : implements<ValidatingFileTypeFilterVector, 
        winrt::Windows::Foundation::Collections::IVector<hstring>, 
        winrt::Windows::Foundation::Collections::IIterable<hstring>>
    {
        ValidatingFileTypeFilterVector();

        // IVector<hstring>
        hstring GetAt(uint32_t index) const;
        uint32_t Size() const;
        winrt::Windows::Foundation::Collections::IVectorView<hstring> GetView() const;
        bool IndexOf(hstring const& value, uint32_t& index) const;
        void SetAt(uint32_t index, hstring const& value);
        void InsertAt(uint32_t index, hstring const& value);
        void RemoveAt(uint32_t index);
        void Append(hstring const& value);
        void RemoveAtEnd();
        void Clear();
        uint32_t GetMany(uint32_t startIndex, array_view<hstring> items) const;
        void ReplaceAll(array_view<hstring const> items);

        // IIterable<hstring>
        winrt::Windows::Foundation::Collections::IIterator<hstring> First() const;

    private:
        winrt::Windows::Foundation::Collections::IVector<hstring> m_innerVector{ single_threaded_vector<hstring>() };
    };
}
