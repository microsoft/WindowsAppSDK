#include "pch.h"
#include "packages.h"
#include "install.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Management::Deployment;
using namespace Windows::System;

winrt::hresult add_package(Uri packageUri)
{
    PackageManager packageManager;
    auto deploymentOperation{ packageManager.AddPackageAsync(packageUri, nullptr, DeploymentOptions::None) };
    deploymentOperation.get();
    if (deploymentOperation.Status() != AsyncStatus::Completed)
    {
        return deploymentOperation.ErrorCode();
    }

    return S_OK;
}

winrt::hresult provision_package(std::wstring packageFamilyName)
{
    PackageManager packageManager;
    auto deploymentOperation{ packageManager.ProvisionPackageForAllUsersAsync(packageFamilyName.c_str()) };
    deploymentOperation.get();

    if (deploymentOperation.Status() != AsyncStatus::Completed)
    {
        return deploymentOperation.ErrorCode();
    }

    return S_OK;
}

bool is_architecture_applicable(ProcessorArchitecture arch)
{
    SYSTEM_INFO systemInfo;
    GetNativeSystemInfo(&systemInfo);
    ProcessorArchitecture systemArch = static_cast<ProcessorArchitecture>(systemInfo.wProcessorArchitecture);

    if (arch == systemArch)
    {
        return true;
    }

    // On x64 systems, x86 architecture is also applicable
    if (systemArch == ProcessorArchitecture::X64 && arch == ProcessorArchitecture::X86)
    {
        return true;
    }

    return false;
}

wil::com_ptr<IStream> get_resource_stream(std::wstring resourceName, std::wstring resourceType)
{
    HMODULE const hmodule = GetModuleHandle(NULL);
    HRSRC hrsrc = ::FindResource(hmodule, resourceName.c_str(), resourceType.c_str());
    THROW_LAST_ERROR_IF_NULL(hrsrc);
    HGLOBAL hresource = LoadResource(hmodule, hrsrc);
    THROW_LAST_ERROR_IF_NULL(hresource);
    const BYTE* data = reinterpret_cast<BYTE*>(::LockResource(hresource));
    THROW_LAST_ERROR_IF_NULL(data);
    DWORD size = ::SizeofResource(hmodule, hrsrc);
    wil::com_ptr<IStream> stream = ::SHCreateMemStream(data, size);
    return stream;
}

std::unique_ptr<PackageProperties> get_package_properites_from_stream(wil::com_ptr<IStream>& stream)
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
    THROW_IF_FAILED(id->GetPackageFullName(&properties->full_name));
    THROW_IF_FAILED(id->GetPackageFamilyName(&properties->family_name));
    APPX_PACKAGE_ARCHITECTURE arch;
    THROW_IF_FAILED(id->GetArchitecture(&arch));
    properties->architecture = static_cast<ProcessorArchitecture>(arch);
    THROW_IF_FAILED(id->GetVersion(&properties->version));

    return properties;
}

wil::com_ptr<IStream> open_temp_file(_In_ PCWSTR path)
{
    wil::com_ptr<IStream> outstream;
    THROW_IF_FAILED(SHCreateStreamOnFileEx(path, STGM_WRITE | STGM_READ | STGM_SHARE_DENY_WRITE | STGM_CREATE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, wil::out_param(outstream)));
    return outstream;
}

winrt::hresult deploy_package_from_resource(ResourcePackageInfo resource, bool quiet) noexcept
{
    // Get package properties by loading the resource as a stream and reading the manifest.
    wil::com_ptr<IStream> pkgstream;
    std::unique_ptr<PackageProperties> properties;
    try
    {
        pkgstream = get_resource_stream(resource.Id, resource.ResourceType);
        properties = get_package_properites_from_stream(pkgstream);
    }
    catch (wil::ResultException ex)
    {
        return ex.GetErrorCode();
    }

    // Skip non-applicable architectures.
    if (!is_architecture_applicable(properties->architecture))
    {
        return S_OK;
    }


    wchar_t package_filename[MAX_PATH];
    RETURN_LAST_ERROR_IF(0 == GetTempFileName(std::filesystem::temp_directory_path().c_str(), L"PRP", 0u, package_filename));

    if (!quiet)
    {
        printf("Package Full Name: %ls\n", properties->full_name.get());
        printf("Temp package path: %ls\n", package_filename);
    }

    // Write the package to a temp file. The PackageManager APIs require a Uri.
    wil::com_ptr<IStream> outstream;
    try
    {
        outstream = open_temp_file(package_filename);
    }
    catch (wil::ResultException ex)
    {
        return ex.GetErrorCode();
    }
 
    ULARGE_INTEGER streamSize = { 0 };
    RETURN_IF_FAILED(::IStream_Size(pkgstream.get(), &streamSize));
    RETURN_IF_FAILED(pkgstream.get()->CopyTo(outstream.get(), streamSize, nullptr, nullptr));
    RETURN_IF_FAILED(outstream->Commit(STGC_OVERWRITE));
    outstream.reset();

    // Add the package
    Uri packageUri{ package_filename };
    hresult add_result = add_package(packageUri);
    if (!quiet)
    {
        printf("Package deployment result: 0x%08x\n", add_result.value);
    }
    RETURN_IF_FAILED((HRESULT)add_result);

    // Best-effort provision
    // Provisioning is expected to fail if the program is not run elevated or the user is not admin.
    hresult provision_result = provision_package(properties->family_name.get());
    if (!quiet)
    {
        printf("Provisioning result: 0x%08x\n", provision_result.value);
    }
    LOG_IF_FAILED((HRESULT)provision_result);

    // Cleanup the temp file
    LOG_IF_WIN32_BOOL_FALSE(::DeleteFile(package_filename));

    return S_OK;
}
