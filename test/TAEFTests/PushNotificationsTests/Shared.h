// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

namespace ProjectReunionCppTest
{
    wil::unique_handle Execute(const std::wstring& command, const std::wstring& args,
        const std::wstring& directory);
    void RunCertUtil(const std::wstring& path, bool removeCert = false);
    void InstallPackage(const std::wstring& packagePath);
    void UninstallPackage(const std::wstring& packageFullName);
    wil::unique_event CreateTestEvent(const std::wstring& eventName);
    void WaitForEvent(const wil::unique_event& successEvent, const wil::unique_event& failedEvent);
    const std::wstring GetDeploymentDir();

    const std::wstring g_deploymentDir = GetDeploymentDir();
}
