#include "pch.h"
#include "ToastProgressData.h"
#include "Microsoft.Windows.ToastNotifications.ToastProgressData.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    uint32_t ToastProgressData::SequenceNumber()
    {
        auto lock{ m_lock.lock_shared() };

        return m_sequenceNumber;
    }
    void ToastProgressData::SequenceNumber(uint32_t value)
    {
        auto lock{ m_lock.lock_shared() };

        m_sequenceNumber = value;
    }
    hstring ToastProgressData::Title()
    {
        auto lock{ m_lock.lock_shared() };

        return m_title;
    }
    void ToastProgressData::Title(hstring const& value)
    {
        auto lock{ m_lock.lock_shared() };

        m_title = value;
    }
    double ToastProgressData::Value()
    {
        auto lock{ m_lock.lock_shared() };

        return m_progressValue;
    }
    void ToastProgressData::Value(double value)
    {
        auto lock{ m_lock.lock_shared() };

        m_progressValue = value;
    }
    hstring ToastProgressData::ValueStringOverride()
    {
        auto lock{ m_lock.lock_shared() };

        return m_progressvalueString;
    }
    void ToastProgressData::ValueStringOverride(hstring const& value)
    {
        auto lock{ m_lock.lock_shared() };

        m_progressvalueString = value;
    }
    hstring ToastProgressData::Status()
    {
        auto lock{ m_lock.lock_shared() };

        return m_progressStatus;
    }
    void ToastProgressData::Status(hstring const& value)
    {
        auto lock{ m_lock.lock_shared() };

        m_progressStatus = value;
    }
}
