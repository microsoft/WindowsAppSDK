// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ProjectReunionDeployment.h"
#include "ProjectReunionDeploymentStatus.h"
#include "Deployment.ProjectReunionDeployment.g.cpp"

// Prototype for RtlGetVersion to avoid including a driver kit header.
NTSTATUS WINAPI RtlGetVersion(PRTL_OSVERSIONINFOW);

namespace winrt::Microsoft::ProjectReunion::Deployment::implementation
{

    Microsoft::ProjectReunion::Deployment::ProjectReunionDeploymentStatus ProjectReunionDeployment::GetStatus(Windows::ApplicationModel::PackageVersion const& packageVersion)
    {
        return make<winrt::Microsoft::ProjectReunion::Deployment::implementation::ProjectReunionDeploymentStatus>(GetIsOSUpdatesRequired(), false);
    }

    winrt::Windows::Foundation::Uri ProjectReunionDeployment::GetProjectReunionPackageLink()
    {
        return winrt::Windows::Foundation::Uri(PROJECT_REUNION_PACKAGE_INSTALL_URI);
    }

    winrt::Windows::Foundation::Uri ProjectReunionDeployment::GetProjectReunionInstallInformationLink()
    {
        return winrt::Windows::Foundation::Uri(PROJECT_REUNION_INSTALL_INFORMATION_URI);
    }

    // Determine if this platform has OS Updates related to Project Reunion.
    // We assume that any updates which Project Reunion require will be known to Project Reunion
    // at the time they are required, and requiredUpdates will be updated to include an entry
    // for that update. When a required OS update is shipped, it should add a key with the
    // specified identifier to the registry under PROJECT_REUNION_OS_UPDATE_REGISTRY_PATH to mark
    // the update as being present.
    bool ProjectReunionDeployment::GetIsOSUpdatesRequired()
    {
        struct UpdateEntry
        {
            DWORD buildMin;
            DWORD buildMax;
            PCWSTR identifier;
        };

        const UpdateEntry const requiredUpdates[] =
        {
            {
                0,
                1,
                PROJECT_REUNION_OS_UPDATE_REGISTRY_PATH L"\\" L"SampleRequiredUpdateIdentifier"
            }
        };

        // Getting build number from RtlGetVersion. This is because GetVersionEx lies and is deprecated.
        // Ntdll has the function, but the header is in the driver kit, so we will load it directly.
        wil::unique_hmodule dll(LoadLibrary(L"ntdll.dll"));
        THROW_LAST_ERROR_IF_NULL(dll);
        auto fnRtlGetVersion = GetProcAddressByFunctionDeclaration(dll.get(), RtlGetVersion);
        THROW_LAST_ERROR_IF_NULL(fnRtlGetVersion);
        RTL_OSVERSIONINFOW osVersionInfo{};
        THROW_IF_NTSTATUS_FAILED(fnRtlGetVersion(&osVersionInfo));

        // Look for identifiers of any applicable updates.
        for (int i = 0; i < ARRAYSIZE(requiredUpdates); ++i)
        {
            if (osVersionInfo.dwBuildNumber >= requiredUpdates[i].buildMin &&
                osVersionInfo.dwBuildNumber <= requiredUpdates[i].buildMax)
            {
                wil::unique_hkey key;
                auto regOpenResult = ::RegOpenKeyExW(HKEY_LOCAL_MACHINE, requiredUpdates[i].identifier, 0, KEY_READ, &key);
                if (regOpenResult != ERROR_SUCCESS)
                {
                    if ((regOpenResult == ERROR_PATH_NOT_FOUND) || (regOpenResult == ERROR_FILE_NOT_FOUND))
                    {
                        return true;
                    }
                    else
                    {
                        THROW_IF_WIN32_ERROR(regOpenResult);
                    }
                }
            }
        }

        return false;
    }
}
