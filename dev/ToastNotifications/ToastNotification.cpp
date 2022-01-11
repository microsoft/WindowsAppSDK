#include "pch.h"
#include "ToastNotification.h"
#include "Microsoft.Windows.ToastNotifications.ToastNotification.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    ToastNotification::ToastNotification(winrt::Windows::Data::Xml::Dom::XmlDocument const& /* payload */)
    {
        throw hresult_not_implemented();
    }
    hstring ToastNotification::Tag()
    {
        throw hresult_not_implemented();
    }
    void ToastNotification::Tag(hstring const& /* value */)
    {
        throw hresult_not_implemented();
    }
    hstring ToastNotification::Group()
    {
        throw hresult_not_implemented();
    }
    void ToastNotification::Group(hstring const& /* value */)
    {
        throw hresult_not_implemented();
    }
    uint32_t ToastNotification::ToastId()
    {
        throw hresult_not_implemented();
    }
    void ToastNotification::ToastId(uint32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Data::Xml::Dom::XmlDocument ToastNotification::Payload()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::ToastNotifications::ToastProgressData ToastNotification::ProgressData()
    {
        throw hresult_not_implemented();
    }
    void ToastNotification::ProgressData(winrt::Microsoft::Windows::ToastNotifications::ToastProgressData const& /* value */)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::DateTime ToastNotification::ExpirationTime()
    {
        throw hresult_not_implemented();
    }
    void ToastNotification::ExpirationTime(winrt::Windows::Foundation::DateTime const& /* value */)
    {
        throw hresult_not_implemented();
    }
    bool ToastNotification::ExpiresOnReboot()
    {
        throw hresult_not_implemented();
    }
    void ToastNotification::ExpiresOnReboot(bool /* value */)
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::ToastNotifications::ToastPriority ToastNotification::Priority()
    {
        throw hresult_not_implemented();
    }
    void ToastNotification::Priority(winrt::Microsoft::Windows::ToastNotifications::ToastPriority const& /* value */)
    {
        throw hresult_not_implemented();
    }
    bool ToastNotification::SuppressDisplay()
    {
        throw hresult_not_implemented();
    }
    void ToastNotification::SuppressDisplay(bool /* value */)
    {
        throw hresult_not_implemented();
    }
}
