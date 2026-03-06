// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "UnpackagedApplicationDataContainer.h"

namespace Microsoft::Windows::Storage
{
    namespace
    {
        // REG_BINARY values are stored as [1-byte PropertyType tag][raw data bytes].
        // This allows roundtripping types that share the same raw size (e.g. Int32 vs Boolean).
        // REG_SZ, REG_DWORD, and REG_QWORD are stored natively for easy manual inspection.

        template <typename T>
        std::vector<uint8_t> TaggedBytes(winrt::Windows::Foundation::PropertyType tag, const T& val)
        {
            std::vector<uint8_t> data(1 + sizeof(T));
            data[0] = static_cast<uint8_t>(tag);
            std::memcpy(data.data() + 1, &val, sizeof(T));
            return data;
        }

        winrt::Windows::Foundation::IInspectable ReadRegistryValue(HKEY key, PCWSTR valueName)
        {
            DWORD type{};
            DWORD dataSize{};
            const auto status{ ::RegQueryValueExW(key, valueName, nullptr, &type, nullptr, &dataSize) };
            THROW_IF_WIN32_ERROR(status);

            switch (type)
            {
            case REG_SZ:
            {
                auto value{ wil::reg::get_value_string(key, valueName) };
                return winrt::box_value(winrt::hstring{ value });
            }
            case REG_DWORD:
            {
                auto value{ wil::reg::get_value_dword(key, valueName) };
                return winrt::box_value(value);
            }
            case REG_QWORD:
            {
                auto value{ wil::reg::get_value_qword(key, valueName) };
                return winrt::box_value(value);
            }
            case REG_BINARY:
            {
                auto bytes{ wil::reg::get_value_binary(key, valueName, REG_BINARY) };
                THROW_HR_IF(E_UNEXPECTED, bytes.empty());
                const auto tag{ static_cast<winrt::Windows::Foundation::PropertyType>(bytes[0]) };
                const uint8_t* payload{ bytes.data() + 1 };
                const size_t payloadSize{ bytes.size() - 1 };

                switch (tag)
                {
                case winrt::Windows::Foundation::PropertyType::UInt8:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(uint8_t));
                    uint8_t val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::Int16:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(int16_t));
                    int16_t val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::UInt16:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(uint16_t));
                    uint16_t val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::Int32:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(int32_t));
                    int32_t val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::Int64:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(int64_t));
                    int64_t val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::Single:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(float));
                    float val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::Double:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(double));
                    double val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::Char16:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(char16_t));
                    char16_t val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::Boolean:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(uint8_t));
                    return winrt::box_value(static_cast<bool>(payload[0]));
                }
                case winrt::Windows::Foundation::PropertyType::DateTime:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(int64_t));
                    int64_t ticks{};
                    std::memcpy(&ticks, payload, sizeof(ticks));
                    return winrt::box_value(winrt::Windows::Foundation::DateTime{ winrt::Windows::Foundation::TimeSpan{ ticks } });
                }
                case winrt::Windows::Foundation::PropertyType::TimeSpan:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(int64_t));
                    int64_t duration{};
                    std::memcpy(&duration, payload, sizeof(duration));
                    return winrt::box_value(winrt::Windows::Foundation::TimeSpan{ duration });
                }
                case winrt::Windows::Foundation::PropertyType::Guid:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(winrt::guid));
                    winrt::guid val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::Point:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(winrt::Windows::Foundation::Point));
                    winrt::Windows::Foundation::Point val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::Size:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(winrt::Windows::Foundation::Size));
                    winrt::Windows::Foundation::Size val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                case winrt::Windows::Foundation::PropertyType::Rect:
                {
                    THROW_HR_IF(E_UNEXPECTED, payloadSize != sizeof(winrt::Windows::Foundation::Rect));
                    winrt::Windows::Foundation::Rect val{};
                    std::memcpy(&val, payload, sizeof(val));
                    return winrt::box_value(val);
                }
                default:
                    THROW_HR(E_UNEXPECTED);
                }
            }
            default:
                THROW_HR(E_UNEXPECTED);
            }
        }

        void WriteRegistryValue(HKEY key, PCWSTR valueName, winrt::Windows::Foundation::IInspectable const& value)
        {
            auto propertyValue{ value.as<winrt::Windows::Foundation::IPropertyValue>() };
            switch (propertyValue.Type())
            {
            case winrt::Windows::Foundation::PropertyType::String:
            {
                auto str{ winrt::unbox_value<winrt::hstring>(value) };
                wil::reg::set_value_string(key, valueName, str.c_str());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::UInt32:
            {
                auto val{ winrt::unbox_value<uint32_t>(value) };
                wil::reg::set_value_dword(key, valueName, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::UInt64:
            {
                auto val{ winrt::unbox_value<uint64_t>(value) };
                wil::reg::set_value_qword(key, valueName, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::UInt8:
            {
                auto val{ winrt::unbox_value<uint8_t>(value) };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::UInt8, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Int16:
            {
                auto val{ winrt::unbox_value<int16_t>(value) };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Int16, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::UInt16:
            {
                auto val{ winrt::unbox_value<uint16_t>(value) };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::UInt16, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Int32:
            {
                auto val{ winrt::unbox_value<int32_t>(value) };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Int32, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Int64:
            {
                auto val{ winrt::unbox_value<int64_t>(value) };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Int64, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Single:
            {
                auto val{ winrt::unbox_value<float>(value) };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Single, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Double:
            {
                auto val{ winrt::unbox_value<double>(value) };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Double, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Char16:
            {
                auto val{ winrt::unbox_value<char16_t>(value) };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Char16, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Boolean:
            {
                auto val{ winrt::unbox_value<bool>(value) };
                uint8_t byte{ val ? static_cast<uint8_t>(1) : static_cast<uint8_t>(0) };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Boolean, byte));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::DateTime:
            {
                auto val{ propertyValue.GetDateTime() };
                auto ticks{ val.time_since_epoch().count() };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::DateTime, ticks));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::TimeSpan:
            {
                auto val{ propertyValue.GetTimeSpan() };
                auto duration{ val.count() };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::TimeSpan, duration));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Guid:
            {
                auto val{ propertyValue.GetGuid() };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Guid, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Point:
            {
                auto val{ propertyValue.GetPoint() };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Point, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Size:
            {
                auto val{ propertyValue.GetSize() };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Size, val));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Rect:
            {
                auto val{ propertyValue.GetRect() };
                wil::reg::set_value_binary(key, valueName, REG_BINARY, TaggedBytes(winrt::Windows::Foundation::PropertyType::Rect, val));
                break;
            }
            default:
                THROW_HR(E_NOTIMPL);
            }
        }

        struct RegistryPropertySetIterator : winrt::implements<RegistryPropertySetIterator,
            winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::hstring, winrt::Windows::Foundation::IInspectable>>>
        {
            RegistryPropertySetIterator(std::vector<winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::hstring, winrt::Windows::Foundation::IInspectable>>&& items) :
                m_items(std::move(items)),
                m_index(0)
            {
            }

            winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::hstring, winrt::Windows::Foundation::IInspectable> Current() const
            {
                if (m_index >= m_items.size())
                {
                    throw winrt::hresult_out_of_bounds();
                }
                return m_items[m_index];
            }

            bool HasCurrent() const
            {
                return m_index < m_items.size();
            }

            bool MoveNext()
            {
                if (m_index < m_items.size())
                {
                    ++m_index;
                }
                return m_index < m_items.size();
            }

            uint32_t GetMany(winrt::array_view<winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::hstring, winrt::Windows::Foundation::IInspectable>> items)
            {
                uint32_t count{};
                for (auto& item : items)
                {
                    if (m_index >= m_items.size())
                    {
                        break;
                    }
                    item = m_items[m_index];
                    ++m_index;
                    ++count;
                }
                return count;
            }

        private:
            std::vector<winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::hstring, winrt::Windows::Foundation::IInspectable>> m_items;
            uint32_t m_index{};
        };

        struct RegistryPropertySet : winrt::implements<RegistryPropertySet,
            winrt::Windows::Foundation::Collections::IPropertySet,
            winrt::Windows::Foundation::Collections::IObservableMap<winrt::hstring, winrt::Windows::Foundation::IInspectable>,
            winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::Windows::Foundation::IInspectable>,
            winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::hstring, winrt::Windows::Foundation::IInspectable>>>
        {
            RegistryPropertySet(wil::shared_hkey key) :
                m_key(std::move(key))
            {
            }

            // IMap
            winrt::Windows::Foundation::IInspectable Lookup(winrt::hstring const& key) const
            {
                return ReadRegistryValue(m_key.get(), key.c_str());
            }

            uint32_t Size() const
            {
                DWORD valueCount{};
                THROW_IF_WIN32_ERROR(::RegQueryInfoKeyW(m_key.get(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &valueCount, nullptr, nullptr, nullptr, nullptr));
                return valueCount;
            }

            bool HasKey(winrt::hstring const& key) const
            {
                DWORD type{};
                const auto status{ ::RegQueryValueExW(m_key.get(), key.c_str(), nullptr, &type, nullptr, nullptr) };
                return status == ERROR_SUCCESS;
            }

            winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::IInspectable> GetView() const
            {
                auto snapshot{ winrt::single_threaded_map<winrt::hstring, winrt::Windows::Foundation::IInspectable>() };
                for (const auto& valueData : wil::make_range(wil::reg::value_iterator{ m_key.get() }, wil::reg::value_iterator{}))
                {
                    try
                    {
                        auto value{ ReadRegistryValue(m_key.get(), valueData.name.c_str()) };
                        snapshot.Insert(winrt::hstring{ valueData.name }, value);
                    }
                    catch (...)
                    {
                        // Skip values that cannot be read
                    }
                }
                return snapshot.GetView();
            }

            bool Insert(winrt::hstring const& key, winrt::Windows::Foundation::IInspectable const& value)
            {
                bool existed{ HasKey(key) };
                WriteRegistryValue(m_key.get(), key.c_str(), value);
                m_mapChanged(*this, winrt::make<MapChangedEventArgs>(
                    existed ? winrt::Windows::Foundation::Collections::CollectionChange::ItemChanged : winrt::Windows::Foundation::Collections::CollectionChange::ItemInserted,
                    key));
                return !existed;
            }

            void Remove(winrt::hstring const& key)
            {
                THROW_IF_WIN32_ERROR(::RegDeleteValueW(m_key.get(), key.c_str()));
                m_mapChanged(*this, winrt::make<MapChangedEventArgs>(
                    winrt::Windows::Foundation::Collections::CollectionChange::ItemRemoved, key));
            }

            void Clear()
            {
                // Collect all value names first, then delete
                std::vector<std::wstring> names;
                for (const auto& valueData : wil::make_range(wil::reg::value_iterator{ m_key.get() }, wil::reg::value_iterator{}))
                {
                    names.push_back(valueData.name);
                }
                for (const auto& name : names)
                {
                    ::RegDeleteValueW(m_key.get(), name.c_str());
                }
                m_mapChanged(*this, winrt::make<MapChangedEventArgs>(
                    winrt::Windows::Foundation::Collections::CollectionChange::Reset, winrt::hstring{}));
            }

            // IIterable
            winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::hstring, winrt::Windows::Foundation::IInspectable>> First() const
            {
                std::vector<winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::hstring, winrt::Windows::Foundation::IInspectable>> items;
                for (const auto& valueData : wil::make_range(wil::reg::value_iterator{ m_key.get() }, wil::reg::value_iterator{}))
                {
                    try
                    {
                        auto value{ ReadRegistryValue(m_key.get(), valueData.name.c_str()) };
                        items.push_back(winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::hstring, winrt::Windows::Foundation::IInspectable>{
                            winrt::make<KeyValuePair>(winrt::hstring{ valueData.name }, value) });
                    }
                    catch (...)
                    {
                        // Skip values that cannot be read
                    }
                }
                return winrt::make<RegistryPropertySetIterator>(std::move(items));
            }

            // IObservableMap
            winrt::event_token MapChanged(winrt::Windows::Foundation::Collections::MapChangedEventHandler<winrt::hstring, winrt::Windows::Foundation::IInspectable> const& handler)
            {
                return m_mapChanged.add(handler);
            }

            void MapChanged(winrt::event_token const& token) noexcept
            {
                m_mapChanged.remove(token);
            }

        private:
            struct MapChangedEventArgs : winrt::implements<MapChangedEventArgs,
                winrt::Windows::Foundation::Collections::IMapChangedEventArgs<winrt::hstring>>
            {
                MapChangedEventArgs(winrt::Windows::Foundation::Collections::CollectionChange change, winrt::hstring const& key) :
                    m_change(change),
                    m_key(key)
                {
                }

                winrt::Windows::Foundation::Collections::CollectionChange CollectionChange() const
                {
                    return m_change;
                }

                winrt::hstring Key() const
                {
                    return m_key;
                }

            private:
                winrt::Windows::Foundation::Collections::CollectionChange m_change;
                winrt::hstring m_key;
            };

            struct KeyValuePair : winrt::implements<KeyValuePair,
                winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::hstring, winrt::Windows::Foundation::IInspectable>>
            {
                KeyValuePair(winrt::hstring const& key, winrt::Windows::Foundation::IInspectable const& value) :
                    m_key(key),
                    m_value(value)
                {
                }

                winrt::hstring Key() const
                {
                    return m_key;
                }

                winrt::Windows::Foundation::IInspectable Value() const
                {
                    return m_value;
                }

            private:
                winrt::hstring m_key;
                winrt::Windows::Foundation::IInspectable m_value;
            };

            wil::shared_hkey m_key;
            winrt::event<winrt::Windows::Foundation::Collections::MapChangedEventHandler<winrt::hstring, winrt::Windows::Foundation::IInspectable>> m_mapChanged;
        };
    }

    UnpackagedApplicationDataContainer::UnpackagedApplicationDataContainer(
        wil::shared_hkey key,
        winrt::hstring const& name,
        winrt::Microsoft::Windows::Storage::ApplicationDataLocality locality) :
        m_key(std::move(key)),
        m_name(name),
        m_locality(locality)
    {
    }

    winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::Microsoft::Windows::Storage::ApplicationDataContainer> UnpackagedApplicationDataContainer::Containers()
    {
        auto map{ winrt::single_threaded_map<winrt::hstring, winrt::Microsoft::Windows::Storage::ApplicationDataContainer>() };
        for (const auto& keyData : wil::make_range(wil::reg::key_iterator{ m_key.get() }, wil::reg::key_iterator{}))
        {
            auto subKey{ wil::reg::open_shared_key(m_key.get(), keyData.name.c_str(), wil::reg::key_access::readwrite) };
            auto subContainer{ std::make_shared<UnpackagedApplicationDataContainer>(std::move(subKey), winrt::hstring{ keyData.name }, m_locality) };
            auto wrappedContainer{ winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationDataContainer>(subContainer) };
            map.Insert(winrt::hstring{ keyData.name }, wrappedContainer);
        }
        return map;
    }

    winrt::hstring UnpackagedApplicationDataContainer::Name()
    {
        return m_name;
    }

    winrt::Microsoft::Windows::Storage::ApplicationDataLocality UnpackagedApplicationDataContainer::Locality()
    {
        return m_locality;
    }

    winrt::Windows::Foundation::Collections::IPropertySet UnpackagedApplicationDataContainer::Values()
    {
        return winrt::make<RegistryPropertySet>(m_key);
    }

    void UnpackagedApplicationDataContainer::Close()
    {
        m_key.reset();
    }

    winrt::Microsoft::Windows::Storage::ApplicationDataContainer UnpackagedApplicationDataContainer::CreateContainer(
        winrt::hstring const& name,
        winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition const& disposition)
    {
        if (disposition == winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Existing)
        {
            auto subKey{ wil::reg::open_shared_key(m_key.get(), name.c_str(), wil::reg::key_access::readwrite) };
            auto subContainer{ std::make_shared<UnpackagedApplicationDataContainer>(std::move(subKey), name, m_locality) };
            return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationDataContainer>(subContainer);
        }
        else
        {
            auto subKey{ wil::reg::create_shared_key(m_key.get(), name.c_str(), wil::reg::key_access::readwrite) };
            auto subContainer{ std::make_shared<UnpackagedApplicationDataContainer>(std::move(subKey), name, m_locality) };
            return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationDataContainer>(subContainer);
        }
    }

    void UnpackagedApplicationDataContainer::DeleteContainer(winrt::hstring const& name)
    {
        const auto hr{ HRESULT_FROM_WIN32(::RegDeleteTreeW(m_key.get(), name.c_str())) };
        if ((hr != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) && (hr != HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND)))
        {
            THROW_IF_WIN32_ERROR_MSG(::RegDeleteTreeW(m_key.get(), name.c_str()), "%ls", name.c_str());
        }
    }
}
