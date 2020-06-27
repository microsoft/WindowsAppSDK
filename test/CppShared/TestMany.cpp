// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <winrt/Microsoft.SampleWinRT.h>
#include <SampleFlatC.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectReunionCppTest
{
	TEST_CLASS(FlatApiTests)
	{
	public:
		
		TEST_METHOD(Creates)
		{
            wil::unique_sampleflat_handle temp;
            Assert::IsTrue(SUCCEEDED(::SampleFlatApiCreate(L"kittens", &temp)));
            Assert::IsTrue(SUCCEEDED(::SampleFlatApiCreate(L"puppies", &temp)));
            Assert::IsTrue(FAILED(::SampleFlatApiCreate(nullptr, &temp)));
        }

        TEST_METHOD(CloseNullOk)
        {
            CloseSampleFlatApi(nullptr);
        }

        TEST_METHOD(StringRoundTrip)
        {
            const wchar_t* tasty = L"muffins";
            wil::unique_sampleflat_handle temp;
            THROW_IF_FAILED(::SampleFlatApiCreate(tasty, &temp));
            wil::unique_cotaskmem_string stored;
            Assert::IsTrue(SUCCEEDED(::GetSampleFlatApiString(temp.get(), &stored)));
            Assert::IsNotNull(stored.get());
            Assert::AreEqual(tasty, stored.get());
        }
    };

    TEST_CLASS(WinRtApiTests)
    {
        TEST_METHOD(ContainerTests)
        {
            Assert::IsFalse(winrt::Microsoft::SampleWinRT::Common::IsAppContainer());
            Assert::IsFalse(winrt::Microsoft::SampleWinRT::Common::HasIdentity());
        }
    };
}
