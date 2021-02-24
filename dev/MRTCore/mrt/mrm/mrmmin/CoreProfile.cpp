// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources
{

CoreProfile::CoreProfile() :
    m_pBuildConfiguration(nullptr), m_initializer(CoreEnvironment::GetEnvironmentInitializer()), m_defaultEnvironmentIndex(0)
{}

CoreProfile::~CoreProfile() { delete m_pBuildConfiguration; }

bool CoreProfile::IsLoadPriFileAllowed(_In_ PCWSTR /*pPriFileFullPath*/) const { return true; }

bool CoreProfile::IsFullyQualifiedReferenceAllowed(_In_ PCWSTR /*pFullyQualifiedReference*/) const { return false; }

bool CoreProfile::IsResourceMapLookupByNameAllowed(_In_opt_ PCWSTR pResourceMapName) const
{
    UNREFERENCED_PARAMETER(pResourceMapName);
    return true;
}

// Default is to allow autoload
bool CoreProfile::IsResourceFileAutoLoadSupported() const { return true; }

// The core implementation reports the folder that contains
// the PRI file itself as the root folder.
HRESULT CoreProfile::GetRootFolderForPriFile(_In_ PCWSTR pPriFileFullPath, _Inout_ StringResult* pPriFileRootOut) const
{
    StringResult strPath;
    RETURN_IF_FAILED(strPath.Init(pPriFileFullPath));

    bool result;
    RETURN_IF_FAILED(strPath.IsAbsolutePath(&result));
    RETURN_HR_IF(E_INVALIDARG, !result);

    size_t position = 0;
    RETURN_HR_IF(E_INVALIDARG, !strPath.TryFindLastOf(L'\\', &position));

    RETURN_IF_FAILED(strPath.Truncate(position));

    RETURN_IF_FAILED(pPriFileRootOut->SetContentsFromOther(&strPath));

    return S_OK;
}

bool CoreProfile::IsLoadResourceMapAllowed(
    _In_ PCWSTR /*pResourceMapName*/,
    _In_ MRMPROFILE_PHASE /*mrmProfilePhase*/,
    _In_opt_ PCWSTR /*jpPriFileFullPath*/)
{
    return true;
}

// Determines if a profile is allowed to inspect other packages. Default is true.
bool CoreProfile::IsUnsafeLoadPriFileAllowed() const { return true; }

bool CoreProfile::IsSupportedFileMagicNumber(_In_ const DEFFILE_MAGIC& fileMagicNumber) const
{
    return (
        (fileMagicNumber.ullMagic == gUniversalPriFileMagic.ullMagic) || (fileMagicNumber.ullMagic == gUniversalRS4PriFileMagic.ullMagic) ||
        (fileMagicNumber.ullMagic == gUniversalVNextPriFileMagic.ullMagic));
}

HRESULT CoreProfile::GetTargetPlatformVersionForFileMagic(
    _In_ const DEFFILE_MAGIC& fileMagicNumber,
    _Out_ MrmPlatformVersionInternal* pPlatformVersionOut)
{
    if (fileMagicNumber.ullMagic == gUniversalPriFileMagic.ullMagic)
    {
        *pPlatformVersionOut = MrmPlatformVersionInternal::WindowsCore;
        return S_OK;
    }
    else if (fileMagicNumber.ullMagic == gUniversalRS4PriFileMagic.ullMagic)
    {
        *pPlatformVersionOut = MrmPlatformVersionInternal::WindowsCoreRS4;
        return S_OK;
    }
    else if (fileMagicNumber.ullMagic == gUniversalVNextPriFileMagic.ullMagic)
    {
        *pPlatformVersionOut = MrmPlatformVersionInternal::WindowsCoreVNext;
        return S_OK;
    }
    else
    {
        RETURN_HR(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE));
    }
}

HRESULT CoreProfile::GetTargetPlatformAndVersionForFileMagic(
    _In_ const DEFFILE_MAGIC& fileMagicNumber,
    _Inout_opt_ StringResult* correspondingPlatformName,
    _Inout_opt_ StringResult* correspondingPlatformVersion)
{
    if (!IsSupportedFileMagicNumber(fileMagicNumber))
    {
        RETURN_HR(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE));
    }

    if (correspondingPlatformName != nullptr)
    {
        RETURN_IF_FAILED(correspondingPlatformName->SetRef(CoreEnvironment::PlatformName));
    }

    if (correspondingPlatformVersion != nullptr)
    {
        RETURN_IF_FAILED(correspondingPlatformVersion->SetRef(CoreEnvironment::DefaultPlatformVersion));
    }

    return S_OK;
}

HRESULT CoreProfile::GetTargetPlatformAndVersion(
    _Inout_opt_ StringResult* correspondingPlatformName,
    _Inout_opt_ StringResult* correspondingPlatformVersion)
{
    if (correspondingPlatformName != nullptr)
    {
        RETURN_IF_FAILED(correspondingPlatformName->SetRef(CoreEnvironment::PlatformName));
    }

    if (correspondingPlatformVersion != nullptr)
    {
        RETURN_IF_FAILED(correspondingPlatformVersion->SetRef(CoreEnvironment::DefaultPlatformVersion));
    }
    return S_OK;
}

int CoreProfile::GetNumEnvironments() const { return m_initializer->pEnvironmentDescription->numVersions; }

HRESULT CoreProfile::GetEnvironmentVersionInfo(
    _In_ int index,
    _Inout_ StringResult* environmentName,
    _Outptr_ IEnvironmentVersionInfo** info) const
{
    *info = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > m_initializer->pEnvironmentDescription->numVersions - 1));

    const MRMFILE_ENVIRONMENT_VERSION_INFO* versionInfo;
    RETURN_IF_FAILED(
        MrmEnvironment::FindInfoForVersion(m_initializer->pEnvironmentDescription, index, &versionInfo, nullptr, environmentName));

    RETURN_IF_FAILED(EnvironmentVersionInfo::CreateInstance(versionInfo, (EnvironmentVersionInfo**)info));

    return S_OK;
}

HRESULT CoreProfile::CreateEnvironment(_In_ int index, _In_ AtomPoolGroup* pAtoms, _Outptr_ IEnvironment** enviroment) const
{
    RETURN_IF_FAILED(MrmEnvironment::CreateInstance(pAtoms, m_initializer, index, (MrmEnvironment**)enviroment));
    return S_OK;
}

bool CoreProfile::TryGetBaseEnvironmentIndex(_Out_ int* baseEnvironmentIndex) const
{
    *baseEnvironmentIndex = m_initializer->indexOfBaseEnvironment;
    return (*baseEnvironmentIndex >= 0);
}

HRESULT CoreProfile::SetEnvironmentInitializer(_In_ const ENVIRONMENT_INITIALIZER* initializer, _In_ int defaultEnvironmentIndex)
{
    RETURN_HR_IF(
        E_INVALIDARG, (defaultEnvironmentIndex < 0) || (defaultEnvironmentIndex > initializer->pEnvironmentDescription->numVersions - 1));

    m_defaultEnvironmentIndex = defaultEnvironmentIndex;
    m_initializer = initializer;
    return S_OK;
}

HRESULT CoreProfile::GetQualifierInfoForEnvironment(
    _In_ PCWSTR sourceName,
    _In_ const IEnvironmentVersionInfo* sourceVersion,
    _In_ const IEnvironment* targetEnvironment,
    _Out_ int* numMappedQualifiers,
    _Outptr_result_buffer_maybenull_(*numMappedQualifiers) const PCWSTR** mappedQualifierNames,
    _Outptr_result_buffer_maybenull_(*numMappedQualifiers) const Atom::SmallIndex** qualifierMappings) const
{
    *numMappedQualifiers = 0;
    *mappedQualifierNames = nullptr;
    *qualifierMappings = nullptr;

    // base implementation doesn't know how to convert across different environments, only within
    // different versions of our environment.
    if ((DefString_ICompare(sourceName, m_initializer->pEnvironmentDescription->pSimpleName) != Def_Equal) ||
        (DefString_ICompare(targetEnvironment->GetUniqueName(), m_initializer->pEnvironmentDescription->pUniqueName) != Def_Equal) ||
        (sourceVersion->GetMajorVersion() != targetEnvironment->GetVersionInfo()->GetMajorVersion()) ||
        (sourceVersion->GetMinorVersion() != targetEnvironment->GetVersionInfo()->GetMinorVersion()))
    {
        RETURN_HR(E_MRM_UNSUPPORTED_ENVIRONMENT);
    }

    return S_OK;
}

HRESULT CoreProfile::GetDefaultEnvironmentForFileMagic(
    _In_ const DEFFILE_MAGIC& fileMagicNumber,
    _Inout_opt_ StringResult* nameOut,
    _Inout_opt_ EnvironmentVersionInfo* versionInfoOut) const
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), !IsSupportedFileMagicNumber(fileMagicNumber));

    const MRMFILE_ENVIRONMENT_VERSION_INFO* version;
    RETURN_IF_FAILED(MrmEnvironment::FindInfoForCurrentVersion(m_initializer->pEnvironmentDescription, &version, nullptr, nameOut));

    if (versionInfoOut != nullptr)
    {
        versionInfoOut->SetVersionInfo(version);
    }
    return S_OK;
}

bool CoreProfile::TryGetEnvironmentForChecksum(
    _In_ DefChecksum::Checksum checksum,
    _Inout_opt_ StringResult* nameOut,
    _Inout_opt_ EnvironmentVersionInfo* versionInfoOut) const
{
    const MRMFILE_ENVIRONMENT_VERSION_INFO* version;

    if (!MrmEnvironment::TryFindInfoByChecksum(m_initializer->pEnvironmentDescription, checksum, &version, nullptr, nameOut))
    {
        return false;
    }

    if (versionInfoOut != nullptr)
    {
        versionInfoOut->SetVersionInfo(version);
    }

    return true;
}

bool CoreProfile::IsCompatibleEnvironment(
    _In_ const EnvironmentReference* wantEnvironment,
    _In_ const IEnvironment* haveEnvironment,
    _Outptr_result_maybenull_ const RemapAtomPool** qualifierMapping) const
{
    if (qualifierMapping != nullptr)
    {
        *qualifierMapping = nullptr;
    }

    // MRT guarantees that like-named environments are backwardly compatible within a major version,
    // so that an app which expects e.g. 1.2 will work correctly on a machine that supports 1.3 or later.
    // Environments with a different name or major version or with a later minor version are not
    // guaranteed to be compatible.
    if ((DefString_ICompare(wantEnvironment->GetUniqueName(), haveEnvironment->GetUniqueName()) != Def_Equal) ||
        (wantEnvironment->GetMajorVersion() != haveEnvironment->GetVersionInfo()->GetMajorVersion()) ||
        (wantEnvironment->GetMinorVersion() > haveEnvironment->GetVersionInfo()->GetMinorVersion()))
    {
        return false;
    }

    // Consider validating checksum against known old versions
    return true;
}

HRESULT CoreProfile::GetMergeFolders(_Inout_opt_ StringResult* pAppMergeFolder, _Inout_opt_ StringResult* pSystemMergeFolder) const
{
    if (pAppMergeFolder != nullptr)
    {
        RETURN_IF_FAILED(pAppMergeFolder->SetRef(nullptr));
    }

    if (pSystemMergeFolder == nullptr)
    {
        return S_OK;
    }

    StringResult redirectedMergeFolder;
    if (TryGetRedirectedSystemMergeFolder(&redirectedMergeFolder) && (redirectedMergeFolder.GetRef() != nullptr))
    {
        RETURN_IF_FAILED(pSystemMergeFolder->SetCopy(redirectedMergeFolder.GetRef()));
        return S_OK;
    }

    StringResult constructedPath;
    RETURN_IF_FAILED(GetCachedWindowsFolderName(&constructedPath));

    RETURN_IF_FAILED(constructedPath.ConcatPathElement(MrmWindowsCoreConstDefs::SystemMergeFolderRoot));

    RETURN_IF_FAILED(pSystemMergeFolder->SetContentsFromOther(&constructedPath));

    return S_OK;
}

HRESULT CoreProfile::GetCachedWindowsFolderName(_Inout_opt_ StringResult* cachedWindowsFoldername) const
{
    if (m_cachedWindowsFolderName.IsEmpty())
    {
        WCHAR windowsPath[MAX_PATH];
        RETURN_LAST_ERROR_IF(GetSystemWindowsDirectory(windowsPath, ARRAYSIZE(windowsPath)) == 0);

        RETURN_IF_FAILED(m_cachedWindowsFolderName.SetCopy(windowsPath));
    }

    RETURN_IF_FAILED(cachedWindowsFoldername->SetCopy(m_cachedWindowsFolderName.GetRef()));

    return S_OK;
}

HRESULT CoreProfile::GetOsAppsFolderName(_Inout_opt_ StringResult* osAppsFoldername) const
{
    StringResult constructedPath;
    RETURN_IF_FAILED(GetCachedWindowsFolderName(&constructedPath));

    RETURN_IF_FAILED(constructedPath.ConcatPathElement(MrmWindowsCoreConstDefs::OSAppsFolderName));

    RETURN_IF_FAILED(osAppsFoldername->SetContentsFromOther(&constructedPath));

    return S_OK;
}

MrmBuildConfiguration* CoreProfile::GetBuildConfiguration()
{
    if (m_pBuildConfiguration == nullptr)
    {
        (void)MrmBuildConfiguration::CreateDefault(&m_pBuildConfiguration);
    }

    return m_pBuildConfiguration;
}

HRESULT CoreProfile::GetDefaultUniqueName(_In_ PCWSTR pSimpleName, _Inout_ StringResult* pUniqueNameOut) const
{
    WCHAR buf[MAX_PATH];

    if (FAILED(_DefStringCchPrintf(buf, ARRAYSIZE(buf), MrmWindowsCoreConstDefs::DefaultUriFormat, pSimpleName)))
    {
        RETURN_HR(E_MRM_BAD_NAME);
    }

    RETURN_IF_FAILED(pUniqueNameOut->SetCopy(buf));

    return S_OK;
}

int CoreProfile::GetNumThreadAwareQualifiers() const { return 0; }

HRESULT CoreProfile::GetThreadAwareQualifierName(_In_ int index, _Inout_ StringResult* pResult) const
{
    UNREFERENCED_PARAMETER(index);
    UNREFERENCED_PARAMETER(pResult);
    return E_UNEXPECTED;
}

bool CoreProfile::TryGetApplicationSetting(_In_ PCWSTR /*subkeyName*/, _In_ PCWSTR /*settingName*/, _Inout_ StringResult* /*returnedValue*/)
    const
{
    // core profile has no application specific settings
    return false;
}

HRESULT CoreProfile::SetApplicationSetting(_In_ PCWSTR /*subkeyName*/, _In_ PCWSTR /*settingName*/, _In_ PCWSTR /*settingValue*/) const
{
    // core profile cannot set application specific settings
    return HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
}

// CoreProfile implementation has no packages.
HRESULT CoreProfile::GetPackageInfo(
    _In_ int /*index*/,
    _Inout_opt_ StringResult* /*pPackageUniqueNameOut*/,
    _Inout_opt_ StringResult* /*pPackageSimpleNameOut*/,
    _Inout_opt_ StringResult* /*pPackageRootOut*/) const
{
    // core profile has no concept of packages.
    return E_NOTIMPL;
}

bool CoreProfile::TryGetRedirectedSystemMergeFolder(_Inout_ StringResult* redirectedMergeFolder) const
{
    WCHAR path[MAX_PATH];
    DWORD size = sizeof(path);

    if (ERROR_SUCCESS == RegGetValueW(
                             HKEY_LOCAL_MACHINE,
                             MRT_MERGE_KEY_NAME,
                             MRT_MERGE_REDIRECTED_VALUE_NAME,
                             RRF_RT_REG_SZ | RRF_RT_REG_EXPAND_SZ,
                             nullptr,
                             path,
                             &size))
    {
        if (SUCCEEDED(redirectedMergeFolder->SetCopy(path)))
        {
            return true;
        }
    }

    return false;
}

} // namespace Microsoft::Resources