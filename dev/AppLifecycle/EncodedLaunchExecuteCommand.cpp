// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EncodedLaunchExecuteCommand.h"
#include "ActivationRegistrationManager.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    IFACEMETHODIMP EncodedLaunchExecuteCommand::Execute() noexcept try
    {
        THROW_HR_IF_NULL(E_INVALIDARG, m_selection);

        com_ptr<IShellItem> item;
        THROW_IF_FAILED(m_selection->GetItemAt(0, item.put()));

        LPWSTR buffer = nullptr;
        THROW_IF_FAILED(item->GetDisplayName(SIGDN_URL, &buffer));
        std::wstring_view rawUri{ buffer };

        Uri uri{ rawUri };
        auto host = uri.Host();

        auto separator = rawUri.find(L':');
        THROW_HR_IF(E_INVALIDARG, separator == std::wstring::npos);

        std::wstring encodedLaunchUri{ c_encodedLaunchSchemeName };
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
            // hInstApp is really a HINSTANCE which is a handle.  This is for legacy ShellExecute
            // reasons, but is repurposed to hold non-pointer type data sometimes.  This is one of
            // those times.
            auto resultCode = reinterpret_cast<size_t>(executionInfo.hInstApp);
            DWORD error = static_cast<int32_t>(resultCode);

            switch (error)
            {
            case SE_ERR_FNF:
                THROW_WIN32(ERROR_FILE_NOT_FOUND);
                break;
            case SE_ERR_PNF:
                THROW_WIN32(ERROR_PATH_NOT_FOUND);
                break;
            case SE_ERR_ACCESSDENIED:
                THROW_WIN32(ERROR_ACCESS_DENIED);
                break;
            case SE_ERR_OOM:
                THROW_WIN32(ERROR_NOT_ENOUGH_MEMORY);
                break;
            case SE_ERR_DLLNOTFOUND:
                THROW_WIN32(ERROR_MOD_NOT_FOUND);
                break;
            case SE_ERR_SHARE:
                THROW_WIN32(ERROR_SHARING_VIOLATION);
                break;
            case SE_ERR_DDETIMEOUT:
                THROW_WIN32(ERROR_TIMEOUT);
                break;
            case SE_ERR_DDEFAIL:
                THROW_WIN32(ERROR_DDE_FAIL);
                break;
            case SE_ERR_DDEBUSY:
                THROW_WIN32(ERROR_BUSY);
                break;
            case SE_ERR_ASSOCINCOMPLETE:
                // No great error for an incomplete association, so treat it as it doesn't exist.
                __fallthrough;
                break;
            case SE_ERR_NOASSOC:
                THROW_WIN32(ERROR_NO_ASSOCIATION);
                break;

            default:
                THROW_HR(E_UNEXPECTED);
                break;
            }
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
                if (objWithAppId && SUCCEEDED(objWithAppId->GetAppID(&appUserModelId)))
                {
                    if (CompareStringOrdinal(appUserModelId.get(), -1, targetAppUserModelId.c_str(),
                        -1, TRUE) == CSTR_EQUAL)
                    {
                        // Some handlers are not progId based, but we're trying to resolve to a progId.
                        auto objWithProgId = assocHandler.try_as<::IObjectWithProgID>();
                        if (objWithProgId && SUCCEEDED(objWithProgId->GetProgID(&progId)))
                        {
                            break;
                        }
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
