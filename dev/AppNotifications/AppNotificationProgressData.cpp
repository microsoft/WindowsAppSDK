#include "pch.h"
#include "AppNotificationProgressData.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationProgressData.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    uint32_t AppNotificationProgressData::SequenceNumber()
    {
        throw hresult_not_implemented();
    }
    void AppNotificationProgressData::SequenceNumber(uint32_t /*value*/)
    {
        throw hresult_not_implemented();
    }
    hstring AppNotificationProgressData::Title()
    {
        throw hresult_not_implemented();
    }
    void AppNotificationProgressData::Title(hstring const& /*value*/)
    {
        throw hresult_not_implemented();
    }
    double AppNotificationProgressData::Value()
    {
        throw hresult_not_implemented();
    }
    void AppNotificationProgressData::Value(double /*value*/)
    {
        throw hresult_not_implemented();
    }
    hstring AppNotificationProgressData::ValueStringOverride()
    {
        throw hresult_not_implemented();
    }
    void AppNotificationProgressData::ValueStringOverride(hstring const& /*value*/)
    {
        throw hresult_not_implemented();
    }
    hstring AppNotificationProgressData::Status()
    {
        throw hresult_not_implemented();
    }
    void AppNotificationProgressData::Status(hstring const& /*value*/)
    {
        throw hresult_not_implemented();
    }
}
