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
    void ToastProgressData::SequenceNumber(uint32_t sequenceNumber)
    {
        auto lock{ m_lock.lock_exclusive() };

        m_sequenceNumber = sequenceNumber;
    }
    hstring ToastProgressData::Title()
    {
        auto lock{ m_lock.lock_shared() };

        return m_title;
    }
    void ToastProgressData::Title(hstring const& title)
    {
        auto lock{ m_lock.lock_exclusive() };

        m_title = title;
    }
    double ToastProgressData::Value()
    {
        auto lock{ m_lock.lock_shared() };

        return m_progressValue;
    }
    void ToastProgressData::Value(double progressValue)
    {
        auto lock{ m_lock.lock_exclusive() };

        m_progressValue = progressValue;
    }
    hstring ToastProgressData::ValueStringOverride()
    {
        auto lock{ m_lock.lock_shared() };

        return m_progressValueString;
    }
    void ToastProgressData::ValueStringOverride(hstring const& progressValueString)
    {
        auto lock{ m_lock.lock_exclusive() };

        m_progressValueString = progressValueString;
    }
    hstring ToastProgressData::Status()
    {
        auto lock{ m_lock.lock_shared() };

        return m_progressStatus;
    }
    void ToastProgressData::Status(hstring const& progressStatus)
    {
        auto lock{ m_lock.lock_exclusive() };

        m_progressStatus = progressStatus;
    }
}
