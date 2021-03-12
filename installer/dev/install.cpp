#include "pch.h"
#include "packages.h"
#include "install.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Management::Deployment;
using namespace Windows::System;

namespace ProjectReunionInstaller {

    winrt::hresult AddPackage(const Uri& packageUri)
    {
        PackageManager packageManager;
        const auto deploymentOperation{ packageManager.AddPackageAsync(packageUri, nullptr, DeploymentOptions::None) };
        deploymentOperation.get();
        if (deploymentOperation.Status() != AsyncStatus::Completed)
        {
            return deploymentOperation.ErrorCode();
        }
        return S_OK;
    }

    winrt::hresult ProvisionPackage(const std::wstring& packageFamilyName)
    {
        PackageManager packageManager;
        const auto deploymentOperation{ packageManager.ProvisionPackageForAllUsersAsync(packageFamilyName.c_str()) };
        deploymentOperation.get();

        if (deploymentOperation.Status() != AsyncStatus::Completed)
        {
            return deploymentOperation.ErrorCode();
        }
        return S_OK;
    }

    bool IsArchitectureApplicable(const ProcessorArchitecture& arch)
    {
        SYSTEM_INFO systemInfo{};
        GetNativeSystemInfo(&systemInfo);
        const auto systemArchitecture{ static_cast<ProcessorArchitecture>(systemInfo.wProcessorArchitecture) };

        // Neutral package architecture is applicable on all systems.
        if (arch == ProcessorArchitecture::Neutral)
        {
            return true;
        }

        // Same-arch is always applicable.
        if (arch == systemArchitecture)
        {
            return true;
        }

        // On x64 systems, x86 architecture is also applicable.
        if (systemArchitecture == ProcessorArchitecture::X64 && arch == ProcessorArchitecture::X86)
        {
            return true;
        }

        // On Arm64 systems, all current package architectures are applicable.
        if (systemArchitecture == ProcessorArchitecture::Arm64)
        {
            return true;
        }

        return false;
    }

    wil::com_ptr<IStream> CreateMemoryStream(const BYTE* data, size_t size)
    {
        wil::com_ptr<IStream> retval;
        retval.attach(::SHCreateMemStream(data, size));
        return retval;
    }

    wil::com_ptr<IStream> GetResourceStream(const std::wstring& resourceName, const std::wstring& resourceType)
    {
        HMODULE const hModule = GetModuleHandle(NULL);
        HRSRC hResourceSource = ::FindResource(hModule, resourceName.c_str(), resourceType.c_str());
        THROW_LAST_ERROR_IF_NULL(hResourceSource);
        HGLOBAL hResource = LoadResource(hModule, hResourceSource);
        THROW_LAST_ERROR_IF_NULL(hResource);
        const BYTE* data = reinterpret_cast<BYTE*>(::LockResource(hResource));
        THROW_LAST_ERROR_IF_NULL(data);
        const DWORD size{ ::SizeofResource(hModule, hResourceSource) };
        return CreateMemoryStream(data, size);
    }

    std::unique_ptr<PackageProperties> GetPackagePropertiesFromStream(wil::com_ptr<IStream>& stream)
    {
        // Get PackageId from the manifest.
        auto factory = wil::CoCreateInstance<AppxFactory, IAppxFactory>();
        wil::com_ptr<IAppxPackageReader> reader;
        THROW_IF_FAILED(factory->CreatePackageReader(stream.get(), wil::out_param(reader)));
        wil::com_ptr<IAppxManifestReader> manifest;
        THROW_IF_FAILED(reader->GetManifest(wil::out_param(manifest)));
        wil::com_ptr<IAppxManifestPackageId> id;
        THROW_IF_FAILED(manifest->GetPackageId(&id));

        // Populate properties from the manifest PackageId
        auto properties = std::make_unique<PackageProperties>();
        THROW_IF_FAILED(id->GetPackageFullName(&properties->fullName));
        THROW_IF_FAILED(id->GetPackageFamilyName(&properties->familyName));
        APPX_PACKAGE_ARCHITECTURE arch{};
        THROW_IF_FAILED(id->GetArchitecture(&arch));
        properties->architecture = static_cast<ProcessorArchitecture>(arch);
        THROW_IF_FAILED(id->GetVersion(&properties->version));

        return properties;
    }

    wil::com_ptr<IStream> OpenFileStream(PCWSTR path)
    {
        wil::com_ptr<IStream> outstream;
        THROW_IF_FAILED(SHCreateStreamOnFileEx(path, STGM_WRITE | STGM_READ | STGM_SHARE_DENY_WRITE | STGM_CREATE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, wil::out_param(outstream)));
        return outstream;
    }

    void DeployPackageFromResource(const ProjectReunionInstaller::ResourcePackageInfo& resource, const bool quiet)
    {
        // Get package properties by loading the resource as a stream and reading the manifest.
        auto packageStream = GetResourceStream(resource.id, resource.resourceType);
        auto packageProperties = GetPackagePropertiesFromStream(packageStream);

        // Skip non-applicable architectures.
        if (!IsArchitectureApplicable(packageProperties->architecture))
        {
            return;
        }

        wchar_t packageFilename[MAX_PATH];
        THROW_LAST_ERROR_IF(0 == GetTempFileName(std::filesystem::temp_directory_path().c_str(), L"PRP", 0u, packageFilename));

        // GetTempFileName will create the temp file by that name due to the unique parameter being specified.
        // From here on out if we leave scope for any reason we will attempt to delete that file.
        auto removeTempFileOnScopeExit = wil::scope_exit([&]
            {
                LOG_IF_WIN32_BOOL_FALSE(::DeleteFile(packageFilename));
            });

        if (!quiet)
        {
            std::wcout << "Package Full Name: " << packageProperties->fullName.get() << std::endl;
            std::wcout << "Temp package path: " << packageFilename << std::endl;
        }

        // Write the package to a temp file. The PackageManager APIs require a Uri.
        wil::com_ptr<IStream> outStream{ OpenFileStream(packageFilename) };
        ULARGE_INTEGER streamSize{};
        THROW_IF_FAILED(::IStream_Size(packageStream.get(), &streamSize));
        THROW_IF_FAILED(packageStream->CopyTo(outStream.get(), streamSize, nullptr, nullptr));
        THROW_IF_FAILED(outStream->Commit(STGC_OVERWRITE));
        outStream.reset();

        // Add the package
        Uri packageUri{ packageFilename };
        hresult hrAddResult = AddPackage(packageUri);
        if (!quiet)
        {
            std::wcout << "Package deployment result : 0x" << std::hex << hrAddResult.value << std::endl;
        }
        THROW_IF_FAILED(static_cast<HRESULT>(hrAddResult));

        // Provisioning is expected to fail if the program is not run elevated or the user is not admin.
        hresult hrProvisionResult = ProvisionPackage(packageProperties->familyName.get());
        if (!quiet)
        {
            std::wcout << "Provisioning result : 0x" << std::hex << hrProvisionResult.value << std::endl;
        }
        LOG_IF_FAILED(static_cast<HRESULT>(hrProvisionResult));

        return;
    }

    HRESULT DeployPackages(bool quiet) noexcept try
    {
        for (const auto& package : ProjectReunionInstaller::c_packages)
        {
            DeployPackageFromResource(package, quiet);
        }

        return S_OK;
    }
    CATCH_RETURN()
}
