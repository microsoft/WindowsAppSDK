// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.A.Package.h"
#include "Microsoft.Windows.ApplicationModel.Package.g.cpp"

#include "package_runtime.h"

#include "PackageTelemetry.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    hstring Package::FindPackageFile(hstring const& packageFullName, hstring const& filename)
    {
        wil::unique_process_heap_ptr<WCHAR> packageFile;
        THROW_IF_FAILED_MSG(::FindPackageFile(packageFullName.c_str(), filename.c_str(), wil::out_param(packageFile)),
                            "PackageFullName=%ls Filename=%ls", packageFullName.c_str(), filename.c_str());
        if (!packageFile)
        {
            return winrt::hstring{};
        }
        return winrt::hstring{ packageFile.get() };
    }

    hstring Package::FindPackageFileInPackageGraph(hstring const& packageFullName, hstring const& filename)
    {
        wil::unique_process_heap_ptr<WCHAR> packageFile;
        THROW_IF_FAILED_MSG(::FindPackageFile(packageFullName.c_str(), filename.c_str(), wil::out_param(packageFile)),
                            "PackageFullName=%ls Filename=%ls", packageFullName.c_str(), filename.c_str());
        if (!packageFile)
        {
            return winrt::hstring{};
        }
        return winrt::hstring{ packageFile.get() };
    }
}
