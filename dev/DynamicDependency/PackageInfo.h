// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(PACKAGEINFO_H)
#define PACKAGEINFO_H

namespace MddCore
{
class PackageInfo
{
public:
    static PackageInfo FromPackageInfoReference(
        PACKAGE_INFO_REFERENCE packageInfoReference,
        const UINT32 flags = PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_BUNDLE,
        const PackagePathType packagePathType = PackagePathType_Effective)
    {
        UINT32 bufferLength{};
        const LONG rc{ ::GetPackageInfo2(packageInfoReference, flags, packagePathType, &bufferLength, nullptr, nullptr) };
        THROW_HR_IF(HRESULT_FROM_WIN32(rc), rc != ERROR_INSUFFICIENT_BUFFER);
        std::unique_ptr<BYTE[]> buffer(new BYTE[bufferLength]);
        UINT32 count{};
        THROW_IF_WIN32_ERROR(::GetPackageInfo2(packageInfoReference, flags, packagePathType, &bufferLength, buffer.get(), &count));

        auto packageInfo{ PackageInfo(buffer.get(), count) };
        buffer.release();
        return packageInfo;
    }

    PackageInfo() = default;

    PackageInfo(PackageInfo&& other) :
        m_packageInfoBuffer(std::move(other.m_packageInfoBuffer)),
        m_count(other.m_count)
    {
        m_packageInfo = reinterpret_cast<PACKAGE_INFO*>(m_packageInfoBuffer.get());

        other.m_packageInfo = nullptr;
    }

    PackageInfo(void* buffer, size_t count) :
        m_packageInfoBuffer(static_cast<BYTE*>(buffer)),
        m_count(count)
    {
        m_packageInfo = reinterpret_cast<PACKAGE_INFO*>(m_packageInfoBuffer.get());
    }

    ~PackageInfo() = default;

    PackageInfo& operator=(PackageInfo&& other)
    {
        if (this != &other)
        {
            m_packageInfoBuffer = std::move(other.m_packageInfoBuffer);
            m_packageInfo = reinterpret_cast<PACKAGE_INFO*>(m_packageInfoBuffer.get());
            m_count = other.m_count;

            other.m_packageInfo = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

    void Reset()
    {
        m_packageInfo = nullptr;
        m_packageInfoBuffer.reset();
        m_count = 0;
    }

    const PACKAGE_INFO* Packages() const
    {
        return m_packageInfo;
    }

    const PACKAGE_INFO& Package(const size_t index) const
    {
        THROW_HR_IF(E_BOUNDS, index >= m_count);
        return m_packageInfo[index];
    }

    size_t Count() const
    {
        return m_count;
    }

private:
    PACKAGE_INFO* m_packageInfo{};
    std::unique_ptr<BYTE[]> m_packageInfoBuffer;
    size_t m_count{};
};
}

#endif // PACKAGEINFO_H
