#include "pch.h"
#include "ToastProgressData.h"
#include "Microsoft.Windows.ToastNotifications.ToastProgressData.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    uint32_t ToastProgressData::SequenceNumber()
    {
        return m_sequenceNumber;
    }
    void ToastProgressData::SequenceNumber(uint32_t sequenceNumber)
    {
        m_sequenceNumber = sequenceNumber;
    }
    hstring ToastProgressData::Title()
    {
        return m_title;
    }
    void ToastProgressData::Title(hstring const& title)
    {
        m_title = title;
    }
    double ToastProgressData::Value()
    {
        return m_progressValue;
    }
    void ToastProgressData::Value(double progressValue)
    {
        m_progressValue = progressValue;
    }
    hstring ToastProgressData::ValueStringOverride()
    {
        return m_progressvalueString;
    }
    void ToastProgressData::ValueStringOverride(hstring const& progressvalueString)
    {
        m_progressvalueString = progressvalueString;
    }
    hstring ToastProgressData::Status()
    {
        return m_progressStatus;
    }
    void ToastProgressData::Status(hstring const& progressStatus)
    {
        m_progressStatus = progressStatus;
    }
}
