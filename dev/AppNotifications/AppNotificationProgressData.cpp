// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "AppNotificationProgressData.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationProgressData.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    AppNotificationProgressData::AppNotificationProgressData(uint32_t sequenceNumber)
    {
        THROW_HR_IF(E_INVALIDARG, sequenceNumber == 0); // The sequence number is always greater than 0
        m_sequenceNumber = sequenceNumber;
    }
    uint32_t AppNotificationProgressData::SequenceNumber()
    {
        auto lock{ m_lock.lock_shared() };

        return m_sequenceNumber;
    }
    void AppNotificationProgressData::SequenceNumber(uint32_t sequenceNumber)
    {
        THROW_HR_IF(E_INVALIDARG, sequenceNumber == 0); // The sequence number is always greater than 0

        auto lock{ m_lock.lock_exclusive() };

        m_sequenceNumber = sequenceNumber;
    }
    hstring AppNotificationProgressData::Title()
    {
        auto lock{ m_lock.lock_shared() };

        return m_title;
    }
    void AppNotificationProgressData::Title(hstring const& title)
    {
        auto lock{ m_lock.lock_exclusive() };

        m_title = title;
    }
    double AppNotificationProgressData::Value()
    {
        auto lock{ m_lock.lock_shared() };

        return m_progressValue;
    }
    void AppNotificationProgressData::Value(double progressValue)
    {
        auto lock{ m_lock.lock_exclusive() };

        m_progressValue = progressValue;
    }
    hstring AppNotificationProgressData::ValueStringOverride()
    {
        auto lock{ m_lock.lock_shared() };

        return m_progressValueString;
    }
    void AppNotificationProgressData::ValueStringOverride(hstring const& progressValueString)
    {
        auto lock{ m_lock.lock_exclusive() };

        m_progressValueString = progressValueString;
    }
    hstring AppNotificationProgressData::Status()
    {
        auto lock{ m_lock.lock_shared() };

        return m_progressStatus;
    }
    void AppNotificationProgressData::Status(hstring const& progressStatus)
    {
        auto lock{ m_lock.lock_exclusive() };

        m_progressStatus = progressStatus;
    }
}
