// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

static const int c_phaseTimeout = (30 * 1000); // 30 seconds
static const std::wstring c_testFailureEventName = L"ReunionTestFailureEventName";

static const std::wstring c_testProtocolScheme = L"reuniontestprotocol";
static const std::wstring c_testProtocolScheme_Packaged = L"reuniontestprotocol-packaged";
static const std::wstring c_testProtocolPhaseEventName = L"ReunionTestProtocolPhaseEventName";

static const std::wstring c_testFileExtension = L".reuniontestfile";
static const std::wstring c_testFileExtension_Packaged = L".reuniontestfile-packaged";
static const std::wstring c_testFilePhaseEventName = L"ReunionTestFilePhaseEventName";

static const std::wstring c_testStartupPhaseEventName = L"ReunionTestStartupPhaseEventName";
