// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.Tokucho.PurojekutoTenpuretNoFeaturePrefix.PurojekutoTenpuretNoFeaturePrefixManager.g.h"

namespace winrt::Microsoft::TokuchoNamespace::PurojekutoTenpuretNoFeaturePrefix::implementation
{
    struct PurojekutoTenpuretNoFeaturePrefixManager : PurojekutoTenpuretNoFeaturePrefixManagerT<PurojekutoTenpuretNoFeaturePrefixManager>
    {
        PurojekutoTenpuretNoFeaturePrefixManager() = default;

        static winrt::Microsoft::TokuchoNamespace::PurojekutoTenpuretNoFeaturePrefix::PurojekutoTenpuretNoFeaturePrefixManager Open();
        void TODO_ReplaceMeWithRealContent();
    };
}
namespace winrt::Microsoft::TokuchoNamespace::PurojekutoTenpuretNoFeaturePrefix::factory_implementation
{
    struct PurojekutoTenpuretNoFeaturePrefixManager : PurojekutoTenpuretNoFeaturePrefixManagerT<PurojekutoTenpuretNoFeaturePrefixManager, implementation::PurojekutoTenpuretNoFeaturePrefixManager>
    {
    };
}
