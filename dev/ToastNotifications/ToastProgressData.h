#pragma once
#include "Microsoft.Windows.ToastNotifications.ToastProgressData.g.h"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    struct ToastProgressData : ToastProgressDataT<ToastProgressData>
    {
        ToastProgressData() = default;

        uint32_t SequenceNumber();
        void SequenceNumber(uint32_t value);
        hstring Title();
        void Title(hstring const& value);
        double Value();
        void Value(double value);
        hstring ValueStringOverride();
        void ValueStringOverride(hstring const& value);
        hstring Status();
        void Status(hstring const& value);

    private:
        uint32_t m_sequenceNumber;
        hstring m_title;
        double m_progressValue;
        hstring m_progressvalueString;
        hstring m_progressStatus;
    };
}
namespace winrt::Microsoft::Windows::ToastNotifications::factory_implementation
{
    struct ToastProgressData : ToastProgressDataT<ToastProgressData, implementation::ToastProgressData>
    {
    };
}
