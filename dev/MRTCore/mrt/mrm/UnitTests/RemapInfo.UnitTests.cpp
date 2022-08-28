// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "Helpers.h"
#include "mrm/build/Base.h"
#include "mrm/build/FileListBuilder.h"
#include "mrm/readers/mrmmanagers.h"
#include "mrm/readers/MrmReaders.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

using namespace std;

namespace UnitTests
{
class RemapInfoUnitTests : public WEX::TestClass<RemapInfoUnitTests>
{
    TEST_CLASS(RemapInfoUnitTests);

    TEST_METHOD(SimpleRemapInfoTests);

private:
    bool VerifyRemapInfo(Microsoft::Resources::RemapUInt16* pRemapInfo, const int nSize, bool bCloned);
};

void RemapInfoUnitTests::SimpleRemapInfoTests()
{
    const int size1 = 0;
    const int size2 = 1;
    const int size3 = 63;
    const int size4 = 64;
    const int size5 = 70;

    bool bCloned = false;
    RemapUInt16* pRemapInfo1;
    VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(size1, &pRemapInfo1));
    VERIFY(pRemapInfo1 != nullptr);
    VERIFY(VerifyRemapInfo(pRemapInfo1, size1, bCloned));

    RemapUInt16* pRemapInfo2;
    VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(size2, &pRemapInfo2));
    VERIFY(pRemapInfo2 != nullptr);
    VERIFY(VerifyRemapInfo(pRemapInfo2, size2, bCloned));

    RemapUInt16* pRemapInfo3;
    VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(size3, &pRemapInfo3));
    VERIFY(pRemapInfo3 != nullptr);
    VERIFY(VerifyRemapInfo(pRemapInfo3, size3, bCloned));

    RemapUInt16* pRemapInfo4;
    VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(size4, &pRemapInfo4));
    VERIFY(pRemapInfo4 != nullptr);
    VERIFY(VerifyRemapInfo(pRemapInfo4, size4, bCloned));

    RemapUInt16* pRemapInfo5;
    VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(size5, &pRemapInfo5));
    VERIFY(pRemapInfo5 != nullptr);
    VERIFY(VerifyRemapInfo(pRemapInfo5, size5, bCloned));

    bCloned = true;
    RemapUInt16* pRemapInfo1clone;
    VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pRemapInfo1, &pRemapInfo1clone));
    VERIFY(pRemapInfo1clone != nullptr);
    VERIFY(VerifyRemapInfo(pRemapInfo1clone, size1, bCloned));

    RemapUInt16* pRemapInfo2clone;
    VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pRemapInfo2, &pRemapInfo2clone));
    VERIFY(pRemapInfo2clone != nullptr);
    VERIFY(VerifyRemapInfo(pRemapInfo2clone, size2, bCloned));

    RemapUInt16* pRemapInfo3clone;
    VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pRemapInfo3, &pRemapInfo3clone));
    VERIFY(pRemapInfo3clone != nullptr);
    VERIFY(VerifyRemapInfo(pRemapInfo3clone, size3, bCloned));

    RemapUInt16* pRemapInfo4clone;
    VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pRemapInfo4, &pRemapInfo4clone));
    VERIFY(pRemapInfo4clone != nullptr);
    VERIFY(VerifyRemapInfo(pRemapInfo4clone, size4, bCloned));

    RemapUInt16* pRemapInfo5clone;
    VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pRemapInfo5, &pRemapInfo5clone));
    VERIFY(pRemapInfo5clone != nullptr);
    VERIFY(VerifyRemapInfo(pRemapInfo5clone, size5, bCloned));

    delete pRemapInfo1;
    pRemapInfo1 = nullptr;
    delete pRemapInfo2;
    pRemapInfo2 = nullptr;
    delete pRemapInfo3;
    pRemapInfo3 = nullptr;
    delete pRemapInfo4;
    pRemapInfo4 = nullptr;
    delete pRemapInfo5;
    pRemapInfo5 = nullptr;
    delete pRemapInfo1clone;
    pRemapInfo1clone = nullptr;
    delete pRemapInfo2clone;
    pRemapInfo2clone = nullptr;
    delete pRemapInfo3clone;
    pRemapInfo3clone = nullptr;
    delete pRemapInfo4clone;
    pRemapInfo4clone = nullptr;
    delete pRemapInfo5clone;
    pRemapInfo5clone = nullptr;
}

bool RemapInfoUnitTests::VerifyRemapInfo(RemapUInt16* pRemapInfo, const int nSize, bool bCloned)
{
    VERIFY(pRemapInfo->Size() == nSize);
    for (int nItr = 0; nItr < nSize; nItr++)
    {
        VERIFY(pRemapInfo->IsPresent(static_cast<UINT16>(nItr)) == bCloned);
        VERIFY(pRemapInfo->TrySetMapping(static_cast<UINT16>(nItr), static_cast<UINT16>(nItr * 3)) == true);
        VERIFY(pRemapInfo->IsPresent(static_cast<UINT16>(nItr)) == true);
    }

    UINT16 nMapping;
    for (int nItr = 0; nItr < nSize; nItr++)
    {
        VERIFY(pRemapInfo->IsPresent(static_cast<UINT16>(nItr)) == true);
        VERIFY(pRemapInfo->TryGetMapping(static_cast<UINT16>(nItr), &nMapping) == true);
        VERIFY(nMapping == static_cast<UINT16>(nItr * 3));
        VERIFY(pRemapInfo->IsPresent(static_cast<UINT16>(nItr)) == true);
    }

    if (bCloned)
    {
        // Expand remapinfo size
        VERIFY_SUCCEEDED(pRemapInfo->EnsureSize(nSize * 3));
        VERIFY(pRemapInfo->Size() == nSize * 3);

        // Verify old bits are intact
        for (int nItr = 0; nItr < nSize; nItr++)
        {
            VERIFY(pRemapInfo->IsPresent(static_cast<UINT16>(nItr)) == true);
            VERIFY(pRemapInfo->TryGetMapping(static_cast<UINT16>(nItr), &nMapping) == true);
            VERIFY(nMapping == static_cast<UINT16>(nItr * 3));
            VERIFY(pRemapInfo->IsPresent(static_cast<UINT16>(nItr)) == true);
        }

        // Set new bits
        for (int nItr = nSize; nItr < nSize * 3; nItr++)
        {
            VERIFY(pRemapInfo->IsPresent(static_cast<UINT16>(nItr)) == false);
            VERIFY(pRemapInfo->TrySetMapping(static_cast<UINT16>(nItr), static_cast<UINT16>(nItr * 3)) == true);
            VERIFY(pRemapInfo->IsPresent(static_cast<UINT16>(nItr)) == true);
        }

        // Verify all
        for (int nItr = 0; nItr < nSize * 3; nItr++)
        {
            VERIFY(pRemapInfo->IsPresent(static_cast<UINT16>(nItr)) == true);
            VERIFY(pRemapInfo->TryGetMapping(static_cast<UINT16>(nItr), &nMapping) == true);
            VERIFY(nMapping == static_cast<UINT16>(nItr * 3));
            VERIFY(pRemapInfo->IsPresent(static_cast<UINT16>(nItr)) == true);
        }
    }

    return true;
}

} // namespace UnitTests
