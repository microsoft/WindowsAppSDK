// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

// Include all protobuf files here so we can disable any warnings they contain
#pragma warning(push)
#pragma warning(disable : 4244) // 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable : 4127) // conditional expression is constant
#pragma warning(disable : 5054) // operator '*': deprecated between enumerations of different types

#include <Kozani.DVC.pb.h>

#pragma warning(pop)
