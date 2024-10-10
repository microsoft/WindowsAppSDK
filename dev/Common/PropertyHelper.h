// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace winrt
{
    template<typename TStored> struct basic_property
    {
        TStored m_stored{};

    public:
        basic_property() = default;
        template<typename... TIn> basic_property(TIn&&... in) : m_stored(std::forward<TIn>(in)...) {}

        operator TStored() const
        {
            return m_stored;
        }

        auto operator()() const
        {
            return m_stored;
        }

        template<typename TIn> void operator()(TIn&& in)
        {
            m_stored = std::forward<TIn>(in);
        }
    };
}
