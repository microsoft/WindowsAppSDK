#include "pch.h"
#include "ToastProgressData.h"
#include "Microsoft.Windows.ToastNotifications.ToastProgressData.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    uint32_t ToastProgressData::SequenceNumber()
    {
        return m_sequenceNumber;
    }
    void ToastProgressData::SequenceNumber(uint32_t value)
    {
        m_sequenceNumber = value;
    }
    hstring ToastProgressData::Title()
    {
        return m_title;
    }
    void ToastProgressData::Title(hstring const& value)
    {
        m_title = value;
    }
    double ToastProgressData::Value()
    {
        return m_progressValue;
    }
    void ToastProgressData::Value(double value)
    {
        m_progressValue = value;
    }
    hstring ToastProgressData::ValueStringOverride()
    {
        return m_progressvalueString;
    }
    void ToastProgressData::ValueStringOverride(hstring const& value)
    {
        m_progressvalueString = value;
    }
    hstring ToastProgressData::Status()
    {
        return m_progressStatus;
    }
    void ToastProgressData::Status(hstring const& value)
    {
        m_progressStatus = value;
    }
}
