// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include "TelemetryHelper.h"
#include <shlobj.h>  // For IsUserAnAdmin
#include <processthreadsapi.h>  // For process APIs
#include <wil/resource.h>

class StoragePickersTelemetryHelper : public TelemetryHelper
{
public:
    StoragePickersTelemetryHelper() : TelemetryHelper()
    {
        m_asAdmin = IsAsAdmin();
        m_inContainer = IsInContainer();
    }

    inline bool IsRunningAsAdmin() const
    {
        return m_asAdmin;
    }

    inline bool IsRunningInContainer() const
    {
        return m_inContainer;
    }

private:
    bool m_asAdmin;
    bool m_inContainer;

    BOOL IsAsAdmin()
	{
		BOOL fIsRunAsAdmin = FALSE;
		DWORD dwError = ERROR_SUCCESS;
		PSID pAdministratorsGroup = NULL;

		// Allocate and initialize a SID of the administrators group.
		SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
		if (!AllocateAndInitializeSid(&NtAuthority, 2,
			SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0,
			&pAdministratorsGroup))
		{
			dwError = GetLastError();
		}
		else
		{
			// Determine whether the SID of administrators group is enabled in
			// the primary access token of the process.
			if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
			{
				dwError = GetLastError();
			}

			FreeSid(pAdministratorsGroup);
		}

		return fIsRunAsAdmin;
	}

	BOOL IsInContainer()
	{
		BOOL fIsInSandbox = FALSE;
		DWORD dwError = ERROR_SUCCESS;

		// Get the process token
		HANDLE hToken = NULL;
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
		{
			dwError = GetLastError();
			return FALSE;
		}

		// Check if the process is running in an AppContainer
		DWORD dwIsAppContainer = 0;
		DWORD dwSize = sizeof(dwIsAppContainer);
		BOOL ans = GetTokenInformation(hToken, TokenIsAppContainer, &dwIsAppContainer, dwSize, &dwSize);
		if (!ans)
		{
			dwError = GetLastError();
			CloseHandle(hToken);
			return FALSE;
		}

		fIsInSandbox = (dwIsAppContainer != 0);

		CloseHandle(hToken);
		return fIsInSandbox;
	}
};
