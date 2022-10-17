#include <pch.h>
#include "common.h"

#include "AuthFailure.h"
#include <Microsoft.Windows.Security.Authentication.OAuth.AuthFailure.g.cpp>

using namespace std::literals;
using namespace winrt::Microsoft::Windows::Security::Authentication::OAuth;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::Windows::Security::Authentication::OAuth::implementation
{
    AuthFailure::AuthFailure(const Uri& responseUri)
    {
        std::map<winrt::hstring, winrt::hstring> additionalParams;

        for (auto&& entry : responseUri.QueryParsed())
        {
            auto name = entry.Name();
            if (name == L"error"sv)
            {
                m_error = entry.Value();
            }
            else if (name == L"error_description"sv)
            {
                m_errorDescription = entry.Value();
            }
            else if (name == L"error_uri"sv)
            {
                m_errorUri = Uri(entry.Value());
            }
            else if (name == L"state"sv)
            {
                m_state = entry.Value();
            }
            else
            {
                additionalParams.emplace(std::move(name), entry.Value());
            }
        }

        // TODO: Look in the fragment part as well

        m_additionalParams = winrt::single_threaded_map(std::move(additionalParams)).GetView();
    }

    winrt::hstring AuthFailure::Error()
    {
        return m_error;
    }

    winrt::hstring AuthFailure::ErrorDescription()
    {
        return m_errorDescription;
    }

    Uri AuthFailure::ErrorUri()
    {
        return m_errorUri;
    }

    winrt::hstring AuthFailure::State()
    {
        return m_state;
    }

    IMapView<winrt::hstring, winrt::hstring> AuthFailure::AdditionalParams()
    {
        return m_additionalParams;
    }
}
