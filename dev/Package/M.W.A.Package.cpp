// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.Package.h"
#include "Microsoft.Windows.ApplicationModel.Package.g.cpp"

#include "PackageRuntime.h"

#include "PackageTelemetry.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    winrt::hstring Package::FindPackageFile(winrt::hstring const& PackageFullName, winrt::hstring const& filename)
    {
        wil::unique_process_heap_ptr<WCHAR> packageFile;
        THROW_IF_FAILED_MSG(::FindPackageFile(packageFullName.c_str(), filename.c_str(), wil::out_param(packageFile));
                            "PackageFullName=%ls Filename=%s", packageFullName, filename);
        if (!packageFile)
        {
            return winrt::hstring{};
        }
        return winrt::hstring{ packageFile.get() };
    }
}
