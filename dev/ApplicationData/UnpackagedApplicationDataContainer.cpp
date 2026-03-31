// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "UnpackagedApplicationDataContainer.h"

#include "Validate.h"

namespace Microsoft::Windows::Storage
{
    namespace
    {
        // Custom registry types for WinRT PropertyType values that don't have native
        // registry equivalents. Modeled after Windows' STATE_REG_TYPE used in
        // onecore\base\appmodel\statemanager. Standard registry types (REG_SZ,
        // REG_DWORD, REG_QWORD) are used for String, UInt32, and UInt64. Custom
        // types start at PropertyType value + 0x20000 to avoid collisions with standard registry types.
        enum ApplicationDataRegistryType : DWORD
        {
            // Scalar types: PropertyType enum value + 0x20000
            ApplicationDataRegistryType_UInt8       = 0x20001, // PropertyType::UInt8 (1)
            ApplicationDataRegistryType_Int16       = 0x20002, // PropertyType::Int16 (2)
            ApplicationDataRegistryType_UInt16      = 0x20003, // PropertyType::UInt16 (3)
            ApplicationDataRegistryType_Int32       = 0x20004, // PropertyType::Int32 (4)
            // UInt32 (5) -> REG_DWORD
            ApplicationDataRegistryType_Int64       = 0x20006, // PropertyType::Int64 (6)
            // UInt64 (7) -> REG_QWORD
            ApplicationDataRegistryType_Single      = 0x20008, // PropertyType::Single (8)
            ApplicationDataRegistryType_Double      = 0x20009, // PropertyType::Double (9)
            ApplicationDataRegistryType_Char16      = 0x2000A, // PropertyType::Char16 (10)
            ApplicationDataRegistryType_Boolean     = 0x2000B, // PropertyType::Boolean (11)
            // String (12) -> REG_SZ
            ApplicationDataRegistryType_DateTime    = 0x2000E, // PropertyType::DateTime (14)
            ApplicationDataRegistryType_TimeSpan    = 0x2000F, // PropertyType::TimeSpan (15)
            ApplicationDataRegistryType_Guid        = 0x20010, // PropertyType::Guid (16)
            ApplicationDataRegistryType_Point       = 0x20011, // PropertyType::Point (17)
            ApplicationDataRegistryType_Size        = 0x20012, // PropertyType::Size (18)
            ApplicationDataRegistryType_Rect        = 0x20013, // PropertyType::Rect (19)
            // Array types: PropertyType enum value + 0x20000
            ApplicationDataRegistryType_UInt8Array   = 0x20401, // PropertyType::UInt8Array (1025)
            ApplicationDataRegistryType_Int16Array   = 0x20402, // PropertyType::Int16Array (1026)
            ApplicationDataRegistryType_UInt16Array  = 0x20403, // PropertyType::UInt16Array (1027)
            ApplicationDataRegistryType_Int32Array   = 0x20404, // PropertyType::Int32Array (1028)
            ApplicationDataRegistryType_UInt32Array  = 0x20405, // PropertyType::UInt32Array (1029)
            ApplicationDataRegistryType_Int64Array   = 0x20406, // PropertyType::Int64Array (1030)
            ApplicationDataRegistryType_UInt64Array  = 0x20407, // PropertyType::UInt64Array (1031)
            ApplicationDataRegistryType_SingleArray  = 0x20408, // PropertyType::SingleArray (1032)
            ApplicationDataRegistryType_DoubleArray  = 0x20409, // PropertyType::DoubleArray (1033)
            ApplicationDataRegistryType_Char16Array  = 0x2040A, // PropertyType::Char16Array (1034)
            ApplicationDataRegistryType_BooleanArray = 0x2040B, // PropertyType::BooleanArray (1035)
            // StringArray (1036) -> REG_MULTI_SZ
            ApplicationDataRegistryType_DateTimeArray = 0x2040E, // PropertyType::DateTimeArray (1038)
            ApplicationDataRegistryType_TimeSpanArray = 0x2040F, // PropertyType::TimeSpanArray (1039)
            ApplicationDataRegistryType_GuidArray    = 0x20410, // PropertyType::GuidArray (1040)
            ApplicationDataRegistryType_PointArray   = 0x20411, // PropertyType::PointArray (1041)
            ApplicationDataRegistryType_SizeArray    = 0x20412, // PropertyType::SizeArray (1042)
            ApplicationDataRegistryType_RectArray    = 0x20413, // PropertyType::RectArray (1043)
        };

        template <typename T>
        void SetCustomTypeValue(HKEY key, PCWSTR valueName, DWORD regType, const T& val)
        {
            THROW_IF_WIN32_ERROR(::RegSetValueExW(
                key, valueName, 0, regType,
                reinterpret_cast<const BYTE*>(&val), sizeof(T)));
        }

        template <typename T>
        T ReadCustomTypeValue(HKEY key, PCWSTR valueName, DWORD dataSize)
        {
            THROW_HR_IF(E_UNEXPECTED, dataSize != sizeof(T));
            T val{};
            THROW_IF_WIN32_ERROR(::RegQueryValueExW(
                key, valueName, nullptr, nullptr,
                reinterpret_cast<BYTE*>(&val), &dataSize));
            return val;
        }

        template <typename T>
        void SetCustomTypeArrayValue(HKEY key, PCWSTR valueName, DWORD regType, const T* data, uint32_t count)
        {
            THROW_IF_WIN32_ERROR(::RegSetValueExW(
                key, valueName, 0, regType,
                reinterpret_cast<const BYTE*>(data),
                static_cast<DWORD>(count * sizeof(T))));
        }

        template <typename T>
        winrt::com_array<T> ReadCustomTypeArrayValue(HKEY key, PCWSTR valueName, DWORD dataSize)
        {
            THROW_HR_IF(E_UNEXPECTED, dataSize % sizeof(T) != 0);
            const uint32_t count{ dataSize / static_cast<DWORD>(sizeof(T)) };
            winrt::com_array<T> arr(count);
            THROW_IF_WIN32_ERROR(::RegQueryValueExW(
                key, valueName, nullptr, nullptr,
                reinterpret_cast<BYTE*>(arr.data()), &dataSize));
            return arr;
        }

        winrt::Windows::Foundation::IInspectable ReadRegistryValue(HKEY key, PCWSTR valueName)
        {
            DWORD type{};
            DWORD dataSize{};
            const auto status{ ::RegQueryValueExW(key, valueName, nullptr, &type, nullptr, &dataSize) };
            THROW_IF_WIN32_ERROR(status);

            switch (type)
            {
            case REG_NONE:
                return nullptr;
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
            case REG_MULTI_SZ:
            {
                std::vector<BYTE> buffer(dataSize);
                THROW_IF_WIN32_ERROR(::RegQueryValueExW(key, valueName, nullptr, nullptr, buffer.data(), &dataSize));
                THROW_HR_IF(E_UNEXPECTED, dataSize % sizeof(wchar_t) != 0);
                auto* p{ reinterpret_cast<const wchar_t*>(buffer.data()) };
                auto* end{ reinterpret_cast<const wchar_t*>(buffer.data() + dataSize) };
                std::vector<winrt::hstring> strings;
                while (p < end && *p != L'\0')
                {
                    auto len{ wcsnlen(p, static_cast<size_t>(end - p)) };
                    winrt::hstring str{ p, static_cast<winrt::hstring::size_type>(len) };
                    strings.push_back(str);
                    p += str.size() + 1;
                }
                winrt::com_array<winrt::hstring> arr(strings.begin(), strings.end());
                return winrt::Windows::Foundation::PropertyValue::CreateStringArray(arr);
            }
            case ApplicationDataRegistryType_UInt8:
                return winrt::box_value(ReadCustomTypeValue<uint8_t>(key, valueName, dataSize));
            case ApplicationDataRegistryType_Int16:
                return winrt::box_value(ReadCustomTypeValue<int16_t>(key, valueName, dataSize));
            case ApplicationDataRegistryType_UInt16:
                return winrt::box_value(ReadCustomTypeValue<uint16_t>(key, valueName, dataSize));
            case ApplicationDataRegistryType_Int32:
                return winrt::box_value(ReadCustomTypeValue<int32_t>(key, valueName, dataSize));
            case ApplicationDataRegistryType_Int64:
                return winrt::box_value(ReadCustomTypeValue<int64_t>(key, valueName, dataSize));
            case ApplicationDataRegistryType_Single:
                return winrt::box_value(ReadCustomTypeValue<float>(key, valueName, dataSize));
            case ApplicationDataRegistryType_Double:
                return winrt::box_value(ReadCustomTypeValue<double>(key, valueName, dataSize));
            case ApplicationDataRegistryType_Char16:
                return winrt::box_value(ReadCustomTypeValue<char16_t>(key, valueName, dataSize));
            case ApplicationDataRegistryType_Boolean:
                return winrt::box_value(static_cast<bool>(ReadCustomTypeValue<uint8_t>(key, valueName, dataSize)));
            case ApplicationDataRegistryType_DateTime:
            {
                auto ticks{ ReadCustomTypeValue<int64_t>(key, valueName, dataSize) };
                return winrt::box_value(winrt::Windows::Foundation::DateTime{ winrt::Windows::Foundation::TimeSpan{ ticks } });
            }
            case ApplicationDataRegistryType_TimeSpan:
            {
                auto duration{ ReadCustomTypeValue<int64_t>(key, valueName, dataSize) };
                return winrt::box_value(winrt::Windows::Foundation::TimeSpan{ duration });
            }
            case ApplicationDataRegistryType_Guid:
                return winrt::box_value(ReadCustomTypeValue<winrt::guid>(key, valueName, dataSize));
            case ApplicationDataRegistryType_Point:
                return winrt::box_value(ReadCustomTypeValue<winrt::Windows::Foundation::Point>(key, valueName, dataSize));
            case ApplicationDataRegistryType_Size:
                return winrt::box_value(ReadCustomTypeValue<winrt::Windows::Foundation::Size>(key, valueName, dataSize));
            case ApplicationDataRegistryType_Rect:
                return winrt::box_value(ReadCustomTypeValue<winrt::Windows::Foundation::Rect>(key, valueName, dataSize));
            case ApplicationDataRegistryType_UInt8Array:
            {
                auto arr{ ReadCustomTypeArrayValue<uint8_t>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateUInt8Array(arr);
            }
            case ApplicationDataRegistryType_Int16Array:
            {
                auto arr{ ReadCustomTypeArrayValue<int16_t>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateInt16Array(arr);
            }
            case ApplicationDataRegistryType_UInt16Array:
            {
                auto arr{ ReadCustomTypeArrayValue<uint16_t>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateUInt16Array(arr);
            }
            case ApplicationDataRegistryType_Int32Array:
            {
                auto arr{ ReadCustomTypeArrayValue<int32_t>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateInt32Array(arr);
            }
            case ApplicationDataRegistryType_UInt32Array:
            {
                auto arr{ ReadCustomTypeArrayValue<uint32_t>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateUInt32Array(arr);
            }
            case ApplicationDataRegistryType_Int64Array:
            {
                auto arr{ ReadCustomTypeArrayValue<int64_t>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateInt64Array(arr);
            }
            case ApplicationDataRegistryType_UInt64Array:
            {
                auto arr{ ReadCustomTypeArrayValue<uint64_t>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateUInt64Array(arr);
            }
            case ApplicationDataRegistryType_SingleArray:
            {
                auto arr{ ReadCustomTypeArrayValue<float>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateSingleArray(arr);
            }
            case ApplicationDataRegistryType_DoubleArray:
            {
                auto arr{ ReadCustomTypeArrayValue<double>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateDoubleArray(arr);
            }
            case ApplicationDataRegistryType_Char16Array:
            {
                auto arr{ ReadCustomTypeArrayValue<char16_t>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateChar16Array(arr);
            }
            case ApplicationDataRegistryType_BooleanArray:
            {
                auto bytes{ ReadCustomTypeArrayValue<uint8_t>(key, valueName, dataSize) };
                winrt::com_array<bool> arr(bytes.size());
                for (uint32_t i = 0; i < bytes.size(); ++i)
                {
                    arr[i] = static_cast<bool>(bytes[i]);
                }
                return winrt::Windows::Foundation::PropertyValue::CreateBooleanArray(arr);
            }
            case ApplicationDataRegistryType_DateTimeArray:
            {
                auto ticks{ ReadCustomTypeArrayValue<int64_t>(key, valueName, dataSize) };
                winrt::com_array<winrt::Windows::Foundation::DateTime> arr(ticks.size());
                for (uint32_t i = 0; i < ticks.size(); ++i)
                {
                    arr[i] = winrt::Windows::Foundation::DateTime{ winrt::Windows::Foundation::TimeSpan{ ticks[i] } };
                }
                return winrt::Windows::Foundation::PropertyValue::CreateDateTimeArray(arr);
            }
            case ApplicationDataRegistryType_TimeSpanArray:
            {
                auto durations{ ReadCustomTypeArrayValue<int64_t>(key, valueName, dataSize) };
                winrt::com_array<winrt::Windows::Foundation::TimeSpan> arr(durations.size());
                for (uint32_t i = 0; i < durations.size(); ++i)
                {
                    arr[i] = winrt::Windows::Foundation::TimeSpan{ durations[i] };
                }
                return winrt::Windows::Foundation::PropertyValue::CreateTimeSpanArray(arr);
            }
            case ApplicationDataRegistryType_GuidArray:
            {
                auto arr{ ReadCustomTypeArrayValue<winrt::guid>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateGuidArray(arr);
            }
            case ApplicationDataRegistryType_PointArray:
            {
                auto arr{ ReadCustomTypeArrayValue<winrt::Windows::Foundation::Point>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreatePointArray(arr);
            }
            case ApplicationDataRegistryType_SizeArray:
            {
                auto arr{ ReadCustomTypeArrayValue<winrt::Windows::Foundation::Size>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateSizeArray(arr);
            }
            case ApplicationDataRegistryType_RectArray:
            {
                auto arr{ ReadCustomTypeArrayValue<winrt::Windows::Foundation::Rect>(key, valueName, dataSize) };
                return winrt::Windows::Foundation::PropertyValue::CreateRectArray(arr);
            }
            default:
                THROW_HR(E_UNEXPECTED);
            }
        }

        void WriteRegistryValue(HKEY key, PCWSTR valueName, winrt::Windows::Foundation::IInspectable const& value)
        {
            if (!value)
            {
                THROW_IF_WIN32_ERROR(::RegSetValueExW(
                    key, valueName, 0, REG_NONE, nullptr, 0));
                return;
            }
            auto propertyValue{ value.as<winrt::Windows::Foundation::IPropertyValue>() };
            switch (propertyValue.Type())
            {
            case winrt::Windows::Foundation::PropertyType::Empty:
            {
                THROW_IF_WIN32_ERROR(::RegSetValueExW(
                    key, valueName, 0, REG_NONE, nullptr, 0));
                break;
            }
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
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_UInt8, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Int16:
            {
                auto val{ winrt::unbox_value<int16_t>(value) };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Int16, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::UInt16:
            {
                auto val{ winrt::unbox_value<uint16_t>(value) };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_UInt16, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Int32:
            {
                auto val{ winrt::unbox_value<int32_t>(value) };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Int32, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Int64:
            {
                auto val{ winrt::unbox_value<int64_t>(value) };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Int64, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Single:
            {
                auto val{ winrt::unbox_value<float>(value) };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Single, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Double:
            {
                auto val{ winrt::unbox_value<double>(value) };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Double, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Char16:
            {
                auto val{ winrt::unbox_value<char16_t>(value) };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Char16, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Boolean:
            {
                auto val{ winrt::unbox_value<bool>(value) };
                uint8_t byte{ val ? static_cast<uint8_t>(1) : static_cast<uint8_t>(0) };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Boolean, byte);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::DateTime:
            {
                auto val{ propertyValue.GetDateTime() };
                auto ticks{ val.time_since_epoch().count() };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_DateTime, ticks);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::TimeSpan:
            {
                auto val{ propertyValue.GetTimeSpan() };
                auto duration{ val.count() };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_TimeSpan, duration);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Guid:
            {
                auto val{ propertyValue.GetGuid() };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Guid, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Point:
            {
                auto val{ propertyValue.GetPoint() };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Point, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Size:
            {
                auto val{ propertyValue.GetSize() };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Size, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Rect:
            {
                auto val{ propertyValue.GetRect() };
                SetCustomTypeValue(key, valueName, ApplicationDataRegistryType_Rect, val);
                break;
            }
            case winrt::Windows::Foundation::PropertyType::UInt8Array:
            {
                winrt::com_array<uint8_t> arr;
                propertyValue.GetUInt8Array(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_UInt8Array, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Int16Array:
            {
                winrt::com_array<int16_t> arr;
                propertyValue.GetInt16Array(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_Int16Array, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::UInt16Array:
            {
                winrt::com_array<uint16_t> arr;
                propertyValue.GetUInt16Array(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_UInt16Array, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Int32Array:
            {
                winrt::com_array<int32_t> arr;
                propertyValue.GetInt32Array(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_Int32Array, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::UInt32Array:
            {
                winrt::com_array<uint32_t> arr;
                propertyValue.GetUInt32Array(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_UInt32Array, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Int64Array:
            {
                winrt::com_array<int64_t> arr;
                propertyValue.GetInt64Array(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_Int64Array, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::UInt64Array:
            {
                winrt::com_array<uint64_t> arr;
                propertyValue.GetUInt64Array(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_UInt64Array, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::SingleArray:
            {
                winrt::com_array<float> arr;
                propertyValue.GetSingleArray(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_SingleArray, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::DoubleArray:
            {
                winrt::com_array<double> arr;
                propertyValue.GetDoubleArray(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_DoubleArray, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::Char16Array:
            {
                winrt::com_array<char16_t> arr;
                propertyValue.GetChar16Array(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_Char16Array, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::BooleanArray:
            {
                winrt::com_array<bool> arr;
                propertyValue.GetBooleanArray(arr);
                std::vector<uint8_t> bytes(arr.size());
                for (uint32_t i = 0; i < arr.size(); ++i)
                {
                    bytes[i] = arr[i] ? static_cast<uint8_t>(1) : static_cast<uint8_t>(0);
                }
                THROW_IF_WIN32_ERROR(::RegSetValueExW(
                    key, valueName, 0, ApplicationDataRegistryType_BooleanArray,
                    bytes.data(), static_cast<DWORD>(bytes.size())));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::StringArray:
            {
                winrt::com_array<winrt::hstring> arr;
                propertyValue.GetStringArray(arr);
                std::wstring multiSz;
                for (const auto& s : arr)
                {
                    multiSz.append(s.c_str(), s.size());
                    multiSz.push_back(L'\0');
                }
                multiSz.push_back(L'\0');
                THROW_IF_WIN32_ERROR(::RegSetValueExW(
                    key, valueName, 0, REG_MULTI_SZ,
                    reinterpret_cast<const BYTE*>(multiSz.c_str()),
                    static_cast<DWORD>(multiSz.size() * sizeof(wchar_t))));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::DateTimeArray:
            {
                winrt::com_array<winrt::Windows::Foundation::DateTime> arr;
                propertyValue.GetDateTimeArray(arr);
                std::vector<int64_t> ticks(arr.size());
                for (uint32_t i = 0; i < arr.size(); ++i)
                {
                    ticks[i] = arr[i].time_since_epoch().count();
                }
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_DateTimeArray, ticks.data(), static_cast<uint32_t>(ticks.size()));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::TimeSpanArray:
            {
                winrt::com_array<winrt::Windows::Foundation::TimeSpan> arr;
                propertyValue.GetTimeSpanArray(arr);
                std::vector<int64_t> durations(arr.size());
                for (uint32_t i = 0; i < arr.size(); ++i)
                {
                    durations[i] = arr[i].count();
                }
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_TimeSpanArray, durations.data(), static_cast<uint32_t>(durations.size()));
                break;
            }
            case winrt::Windows::Foundation::PropertyType::GuidArray:
            {
                winrt::com_array<winrt::guid> arr;
                propertyValue.GetGuidArray(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_GuidArray, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::PointArray:
            {
                winrt::com_array<winrt::Windows::Foundation::Point> arr;
                propertyValue.GetPointArray(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_PointArray, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::SizeArray:
            {
                winrt::com_array<winrt::Windows::Foundation::Size> arr;
                propertyValue.GetSizeArray(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_SizeArray, arr.data(), arr.size());
                break;
            }
            case winrt::Windows::Foundation::PropertyType::RectArray:
            {
                winrt::com_array<winrt::Windows::Foundation::Rect> arr;
                propertyValue.GetRectArray(arr);
                SetCustomTypeArrayValue(key, valueName, ApplicationDataRegistryType_RectArray, arr.data(), arr.size());
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
                const auto hr{ HRESULT_FROM_WIN32(::RegQueryValueExW(m_key.get(), key.c_str(), nullptr, &type, nullptr, nullptr)) };
                if (SUCCEEDED(hr))
                {
                    return true;
                }
                else if (wil::reg::is_registry_not_found(hr))
                {
                    return false;
                }
                else
                {
                    THROW_HR_MSG(hr, "%ls", key.c_str());
                }
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
                        LOG_CAUGHT_EXCEPTION();
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
                return existed;
            }

            void Remove(winrt::hstring const& key)
            {
                THROW_IF_WIN32_ERROR(::RegDeleteValueW(m_key.get(), key.c_str()));
                m_mapChanged(*this, winrt::make<MapChangedEventArgs>(
                    winrt::Windows::Foundation::Collections::CollectionChange::ItemRemoved, key));
            }

            void Clear()
            {
                // Best-effort but on failure report the first
                HRESULT hrFirst{};

                // Collect all value names first, then delete
                std::vector<std::wstring> names;
                for (const auto& valueData : wil::make_range(wil::reg::value_iterator{ m_key.get() }, wil::reg::value_iterator{}))
                {
                    names.push_back(valueData.name);
                }
                for (const auto& name : names)
                {
                    const HRESULT hrDeleteValue{ HRESULT_FROM_WIN32(::RegDeleteValueW(m_key.get(), name.c_str())) };
                    if (FAILED(hrDeleteValue) && !wil::reg::is_registry_not_found(hrDeleteValue))
                    {
                        std::ignore = LOG_HR_MSG(hrDeleteValue, "%ls", name.c_str());
                        if (SUCCEEDED(hrFirst))
                        {
                            hrFirst = hrDeleteValue;
                        }
                    }
                }
                m_mapChanged(*this, winrt::make<MapChangedEventArgs>(
                    FAILED(hrFirst) ?
                        winrt::Windows::Foundation::Collections::CollectionChange::ItemRemoved :
                        winrt::Windows::Foundation::Collections::CollectionChange::Reset,
                    winrt::hstring{}));
                THROW_IF_FAILED(hrFirst);
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
                        LOG_CAUGHT_EXCEPTION();
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
        _VerifyNotClosed();

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
        _VerifyNotClosed();

        return m_name;
    }

    winrt::Microsoft::Windows::Storage::ApplicationDataLocality UnpackagedApplicationDataContainer::Locality()
    {
        _VerifyNotClosed();

        return m_locality;
    }

    winrt::Windows::Foundation::Collections::IPropertySet UnpackagedApplicationDataContainer::Values()
    {
        _VerifyNotClosed();

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
        _VerifyNotClosed();

        _VerifyContainerName(name);

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
        _VerifyNotClosed();

        _VerifyContainerName(name);

        const auto hr{ HRESULT_FROM_WIN32(::RegDeleteTreeW(m_key.get(), name.c_str())) };
        if (SUCCEEDED(hr))
        {
            return;
        }
        else if (!wil::reg::is_registry_not_found(hr))
        {
            THROW_HR_MSG(hr, "%ls", name.c_str());
        }
    }

    void UnpackagedApplicationDataContainer::_VerifyNotClosed()
    {
        THROW_HR_IF_NULL(RO_E_CLOSED, m_key);
    }

    void UnpackagedApplicationDataContainer::_VerifyContainerName(winrt::hstring const& name)
    {
        // Container name max length must be <= 255
        const size_t c_registryKeyNameMaxLength{ 255 };
        THROW_HR_IF_MSG(E_INVALIDARG, name.size() > c_registryKeyNameMaxLength, "Container name not valid (%ls)", name.c_str());

        // Container name cannot contain a backslash
        for (PCWSTR s = name.c_str(); *s != L'\0'; ++s)
        {
            THROW_HR_IF_MSG(E_INVALIDARG, *s == L'\\', "Container name not valid (%ls)", name.c_str());
        }

        // Container name cannot be "." or ".."
        THROW_HR_IF_MSG(E_INVALIDARG, name == L".", "Container name not valid (%ls)", name.c_str());
        THROW_HR_IF_MSG(E_INVALIDARG, name == L"..", "Container name not valid (%ls)", name.c_str());
    }
}
