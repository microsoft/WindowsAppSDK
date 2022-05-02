#include "pch.h"

using namespace winrt::Windows::Foundation;

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    int argc{};
    std::wstring cmdLine{ GetCommandLineW() };
    wil::unique_hlocal_ptr<PWSTR[]> argv{ CommandLineToArgvW(cmdLine.c_str(), &argc) };

    if (argc <= 1)
    {
        return HRESULT_FROM_WIN32(ERROR_BAD_ARGUMENTS);
    }
   
    std::filesystem::path packagePath{ argv[1] };
    bool forceDeployment{};

    if (argc == 3)
    {
        if (CompareStringOrdinal(argv[2], -1, L"1", -1, TRUE) == CSTR_EQUAL)
        {
            forceDeployment = true;
        }
    }

    GUID callerActivityId{};
    if (argc == 4)
    {
        // Best effort for telemetry purpose and a failure doesn't affect functionality.
        std::ignore = CLSIDFromString(argv[3], &callerActivityId);
    }

    winrt::Windows::Management::Deployment::PackageManager packageManager;

    auto GetDeploymentOptions = [](bool forceDeployment)
    {
        return (forceDeployment ?
            winrt::Windows::Management::Deployment::DeploymentOptions::ForceTargetApplicationShutdown :
            winrt::Windows::Management::Deployment::DeploymentOptions::None);
    };

    const auto options{ GetDeploymentOptions(forceDeployment) };
    const auto packagePathUri = winrt::Windows::Foundation::Uri(packagePath.c_str());
    const auto deploymentOperation{ packageManager.AddPackageAsync(packagePathUri, nullptr, options) };
    deploymentOperation.get();
    const auto deploymentResult{ deploymentOperation.GetResults() };
    HRESULT hrAddPackage{};
    if (deploymentOperation.Status() != AsyncStatus::Completed)
    {
        hrAddPackage = static_cast<HRESULT>(deploymentOperation.ErrorCode());
    }

    return hrAddPackage;
}
