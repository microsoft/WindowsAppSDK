// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#ifndef _PREFAST_
#pragma warning(disable : 4068)
#endif

#ifdef VS_PROJECT
#include "annotations.h"
#pragma warning(disable : 4127)
#pragma warning(disable : 4267)
#endif

#include "mrm/BaseInternal.h"
#include "mrm/readers/BaseFile.h"
#include "mrm/readers/MrmManagers.h"
#include "mrm/readers/SectionParser.h"
#include "mrm/build/Base.h"
#include "mrm/build/MrmBuilders.h"
#include "mrm/build/SectionCopiers.h"
#include "mrm/platform/Base.h"
