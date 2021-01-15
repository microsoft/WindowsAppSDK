// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EncodedLaunchExecuteCommand.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    IFACEMETHODIMP EncodedLaunchExecuteCommand::Execute() noexcept try
    {
        if (IsDebuggerPresent())
        {
            __debugbreak();
        }

        THROW_HR_IF_NULL(E_INVALIDARG, m_selection);

        com_ptr<IShellItem> item;
        THROW_IF_FAILED(m_selection->GetItemAt(0, item.put()));

        LPWSTR buffer = nullptr;
        THROW_IF_FAILED(item->GetDisplayName(SIGDN_URL, &buffer));
        std::wstring_view rawUri{ buffer };

        Uri uri{ rawUri };
        auto host = uri.Host();

        auto separator = rawUri.find(L":");
        if (separator == std::wstring::npos)
        {
            // TODO: Fail
        }

        std::wstring encodedLaunchUri{ L"ms-encodedlaunch" };
        encodedLaunchUri += rawUri.substr(separator);

        SHELLEXECUTEINFO executionInfo{};
        executionInfo.cbSize = sizeof executionInfo;
        executionInfo.fMask = SEE_MASK_CLASSNAME | SEE_MASK_FLAG_HINST_IS_SITE;

        auto progId = ResolveUriTarget(encodedLaunchUri, host.c_str());
        executionInfo.lpClass = progId.c_str();
        executionInfo.lpFile = encodedLaunchUri.c_str();

        com_ptr<::IUnknown> site;
        THROW_IF_FAILED(GetSite(IID_PPV_ARGS(&site)));
        executionInfo.hInstApp = reinterpret_cast<HINSTANCE>(site.get());

        auto succeeded = ShellExecuteEx(&executionInfo);
        if (!succeeded)
        {
            // TODO: handle failures.
            /*reinterpret_cast<int64_t>(executionInfo.hInstApp);
            result.Result(static_cast<int32_t>(resultCode));*/
        }

        return S_OK;
    }
    CATCH_RETURN()

    std::wstring EncodedLaunchExecuteCommand::ResolveUriTarget(std::wstring uri, std::wstring targetAppUserModelId)
    {
        com_ptr<::IShellItem> item;
        THROW_IF_FAILED(SHCreateItemFromParsingName(uri.c_str(), nullptr, IID_PPV_ARGS(&item)));

        com_ptr<::IEnumAssocHandlers> enumHandlers;
        HRESULT bindResult = item->BindToHandler(nullptr, BHID_EnumAssocHandlers, IID_PPV_ARGS(&enumHandlers));
        THROW_HR_IF(bindResult, FAILED(bindResult) && bindResult != HRESULT_FROM_WIN32(ERROR_NO_ASSOCIATION));

        wil::unique_cotaskmem_string progId;
        if (SUCCEEDED(bindResult))
        {
            com_ptr<::IAssocHandler> assocHandler;
            while (S_OK == enumHandlers->Next(1, assocHandler.put(), nullptr))
            {
                // Check if the assocHandler has an AppUserModelId that matches our target.
                auto objWithAppId = assocHandler.try_as<::IObjectWithAppUserModelID>();
                wil::unique_cotaskmem_string appUserModelId;
                if (objWithAppId && SUCCEEDED(objWithAppId->GetAppID(&appUserModelId)) &&
                    appUserModelId.get() == targetAppUserModelId)
                {
                    // Some handlers are not progId based, but we're trying to resolve to a progId.
                    auto objWithProgId = assocHandler.try_as<::IObjectWithProgID>();
                    if (objWithProgId && SUCCEEDED(objWithProgId->GetProgID(&progId)))
                    {
                        break;
                    }
                }

                assocHandler = nullptr;
            }
        }

        // Unable to find target progId handler
        if (!progId.is_valid())
        {
            THROW_HR(HRESULT_FROM_WIN32(ERROR_NO_ASSOCIATION));
        }

        return std::wstring(progId.get());
    }
}
