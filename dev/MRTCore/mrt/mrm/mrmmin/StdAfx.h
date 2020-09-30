// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#ifndef DOWNLEVEL_PRIOR_TO_WIN8
#include <nt.h>
#include <ntrtl.h>
#include <nturtl.h>
#endif

#include <strsafe.h>

#include "mrm/BaseInternal.h"
#include "mrm/Collections.h"
#include "mrm/common/file/MrmFiles.h"
#include "mrm/common/MrmProfileData.h"
#include "mrm/Checksums.h"
#include "mrm/MrmEnvironment.h"
#include "mrm/MrmQualifiers.h"
#include "mrm/platform/base.h"
#include "mrm/readers/BaseFile.h"
#include "mrm/readers/SectionReaders.h"
#include "mrm/readers/SectionParser.h"
#include "mrm/readers/MrmReaders.h"
#ifdef DOWNLEVEL_PRIOR_TO_WIN8
#include "mrm/readers/BaseFile.h"
#include "mrm/readers/Atoms.h"
#else
#include "mrm/build/Base.h"
#endif
#include "mrm/Results.h"
#include "mrm/readers/MrmManagers.h"
