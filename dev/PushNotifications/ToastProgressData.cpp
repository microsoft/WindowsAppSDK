#include "pch.h"
#include "ToastProgressData.h"
#include "Microsoft.Windows.ToastNotifications.ToastProgressData.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    uint32_t ToastProgressData::SequenceNumber()
    {
        throw hresult_not_implemented();
    }
    void ToastProgressData::SequenceNumber(uint32_t value)
    {
        throw hresult_not_implemented();
    }
    hstring ToastProgressData::Title()
    {
        throw hresult_not_implemented();
    }
    void ToastProgressData::Title(hstring const& value)
    {
        throw hresult_not_implemented();
    }
    double ToastProgressData::Value()
    {
        throw hresult_not_implemented();
    }
    void ToastProgressData::Value(double value)
    {
        throw hresult_not_implemented();
    }
    hstring ToastProgressData::ValueStringOverride()
    {
        throw hresult_not_implemented();
    }
    void ToastProgressData::ValueStringOverride(hstring const& value)
    {
        throw hresult_not_implemented();
    }
    hstring ToastProgressData::Status()
    {
        throw hresult_not_implemented();
    }
    void ToastProgressData::Status(hstring const& value)
    {
        throw hresult_not_implemented();
    }
}
