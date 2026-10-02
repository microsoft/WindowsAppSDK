// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

namespace Test::AppLifecycle
{
    winrt::Windows::Storage::StorageFile CreateDocFile(std::wstring filename);
    winrt::Windows::Storage::StorageFile OpenDocFile(std::wstring filename);
    wil::unique_handle Execute(const std::wstring& command, const std::wstring& args,
        const std::wstring& directory);
    void InstallPackage(const std::wstring& packagePath);
    void UninstallPackage(const std::wstring& packageFullName);
    wil::unique_event CreateTestEvent(const std::wstring& eventName);
    void WaitForEvent(const wil::unique_event& successEvent, const wil::unique_event& failedEvent);
    const std::wstring GetDeploymentDir();
    void WriteContentFile(std::wstring filename);
    void DeleteContentFile(std::wstring filename);

    const std::wstring g_deploymentDir = GetDeploymentDir();
}
