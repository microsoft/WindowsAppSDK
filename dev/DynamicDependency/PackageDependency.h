// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace MddCore
{
class PackageDependency
{
public:
    PackageDependency() = default;

    PackageDependency(
        const PSID user,
        const std::wstring& packageFamilyName,
        const PACKAGE_VERSION minVersion,
        const MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
        const MddPackageDependencyLifetimeKind lifetimeKind,
        const std::wstring& lifetimeArtifact,
        const MddCreatePackageDependencyOptions options) :
        m_packageFamilyName(packageFamilyName),
        m_minVersion(minVersion),
        m_packageDependencyProcessorArchitectures(packageDependencyProcessorArchitectures),
        m_lifetimeKind(lifetimeKind),
        m_lifetimeArtifact(lifetimeArtifact),
        m_options(options)
    {
        User(user);
    }

    ~PackageDependency() = default;

    PackageDependency(const PackageDependency& other) :
        m_packageFamilyName(other.m_packageFamilyName),
        m_minVersion(other.m_minVersion),
        m_packageDependencyProcessorArchitectures(other.m_packageDependencyProcessorArchitectures),
        m_lifetimeKind(other.m_lifetimeKind),
        m_lifetimeArtifact(other.m_lifetimeArtifact),
        m_options(other.m_options),
        m_packageDependencyId(other.m_packageDependencyId)
    {
        User(other.m_user.get());
    }

    PackageDependency(PackageDependency&& other) :
        m_user(std::move(other.m_user)),
        m_packageFamilyName(std::move(other.m_packageFamilyName)),
        m_minVersion(std::move(other.m_minVersion)),
        m_packageDependencyProcessorArchitectures(std::move(other.m_packageDependencyProcessorArchitectures)),
        m_lifetimeKind(std::move(other.m_lifetimeKind)),
        m_lifetimeArtifact(std::move(other.m_lifetimeArtifact)),
        m_options(std::move(other.m_options)),
        m_packageDependencyId(std::move(other.m_packageDependencyId))
    {
    }

    PackageDependency& operator=(const PackageDependency& other)
    {
        if (this != &other)
        {
            Reset();
            User(other.m_user.get());
            m_packageFamilyName = other.m_packageFamilyName;
            m_minVersion = other.m_minVersion;
            m_packageDependencyProcessorArchitectures = other.m_packageDependencyProcessorArchitectures;
            m_lifetimeKind = other.m_lifetimeKind;
            m_lifetimeArtifact = other.m_lifetimeArtifact;
            m_options = other.m_options;
            m_packageDependencyId = other.m_packageDependencyId;
        }
        return *this;
    }

    PackageDependency& operator=(PackageDependency&& other)
    {
        if (this != &other)
        {
            Reset();
            m_user = std::move(other.m_user);
            m_packageFamilyName = std::move(other.m_packageFamilyName);
            m_minVersion = std::move(other.m_minVersion);
            m_packageDependencyProcessorArchitectures = std::move(other.m_packageDependencyProcessorArchitectures);
            m_lifetimeKind = std::move(other.m_lifetimeKind);
            m_lifetimeArtifact = std::move(other.m_lifetimeArtifact);
            m_options = std::move(other.m_options);
            m_packageDependencyId = std::move(other.m_packageDependencyId);
        }
        return *this;
    }

    void Reset()
    {
        m_user.reset();
        m_packageFamilyName.clear();
        m_minVersion = PACKAGE_VERSION{};
        m_packageDependencyProcessorArchitectures = MddPackageDependencyProcessorArchitectures::None;
        m_lifetimeKind = MddPackageDependencyLifetimeKind::Process;
        m_lifetimeArtifact.clear();
        m_options = MddCreatePackageDependencyOptions::None;
        m_packageDependencyId.clear();
    }

    void GenerateId();

    void User(PSID user)
    {
        if (user)
        {
            const auto sidLength = GetLengthSid(user);
            wil::unique_any_psid sid(reinterpret_cast<PSID>(new BYTE[sidLength]));
            THROW_IF_WIN32_BOOL_FALSE(CopySid(sidLength, sid.get(), user));
            m_user = std::move(sid);
        }
        else
        {
            m_user.reset();
        }
    }

    const std::wstring& Id() const
    {
        return m_packageDependencyId;
    }

private:
    wil::unique_any_psid m_user;
    std::wstring m_packageFamilyName;
    PACKAGE_VERSION m_minVersion{};
    MddPackageDependencyProcessorArchitectures m_packageDependencyProcessorArchitectures = MddPackageDependencyProcessorArchitectures::None;
    MddPackageDependencyLifetimeKind m_lifetimeKind = MddPackageDependencyLifetimeKind::Process;
    std::wstring m_lifetimeArtifact;
    MddCreatePackageDependencyOptions m_options = MddCreatePackageDependencyOptions::None;
    std::wstring m_packageDependencyId;
};
}
