#include "pch.h"
#include "ToastNotification.h"
#include "Microsoft.Windows.ToastNotifications.ToastNotification.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    ToastNotification::ToastNotification(winrt::Windows::Data::Xml::Dom::XmlDocument const& payload)
    {
        m_payload = payload;
    }
    hstring ToastNotification::Tag()
    {
        return m_tag;
    }
    void ToastNotification::Tag(hstring const& tag)
    {
        m_tag = tag;
    }
    hstring ToastNotification::Group()
    {
        return m_group;
    }
    void ToastNotification::Group(hstring const& group)
    {
        m_group = group;
    }
    uint32_t ToastNotification::ToastId()
    {
        return m_toastId;
    }
    void ToastNotification::ToastId(uint32_t toastId)
    {
        m_toastId = toastId;
    }
    winrt::Windows::Data::Xml::Dom::XmlDocument ToastNotification::Payload()
    {
        return m_payload;
    }
    winrt::Microsoft::Windows::ToastNotifications::ToastProgressData ToastNotification::ProgressData()
    {
        return m_progressData;
    }
    void ToastNotification::ProgressData(winrt::Microsoft::Windows::ToastNotifications::ToastProgressData const& progressData)
    {
        m_progressData = progressData;
    }
    winrt::Windows::Foundation::DateTime ToastNotification::ExpirationTime()
    {
        return m_expirationTime;
    }
    void ToastNotification::ExpirationTime(winrt::Windows::Foundation::DateTime const& expirationTime)
    {
        m_expirationTime = expirationTime;
    }
    bool ToastNotification::ExpiresOnReboot()
    {
        return m_expiresOnReboot;
    }
    void ToastNotification::ExpiresOnReboot(bool expiresOnReboot)
    {
        m_expiresOnReboot = expiresOnReboot;
    }
    winrt::Microsoft::Windows::ToastNotifications::ToastPriority ToastNotification::Priority()
    {
        return m_priority;
    }
    void ToastNotification::Priority(winrt::Microsoft::Windows::ToastNotifications::ToastPriority const& priority)
    {
        m_priority = priority;
    }
    bool ToastNotification::SuppressDisplay()
    {
        return m_suppressDisplay;
    }
    void ToastNotification::SuppressDisplay(bool suppressDisplay)
    {
        m_suppressDisplay = suppressDisplay;
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
