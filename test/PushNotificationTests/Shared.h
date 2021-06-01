// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

namespace Test::PushNotifications
{
    void InstallPackage(const std::wstring& packagePath);
    void UninstallPackage(const std::wstring& packageFullName);
}
