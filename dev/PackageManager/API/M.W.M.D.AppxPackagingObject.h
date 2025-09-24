#pragma once
#include "Microsoft.Windows.Management.Deployment.AppxPackagingObject.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct AppxPackagingObject : AppxPackagingObjectT<AppxPackagingObject>
    {
        AppxPackagingObject() = default;

    };
}
