#pragma once
#include "pch.h"
#include "platform.h"

NotificationsLongRunningPlatformImpl* GetPlatform();

HRESULT InitializePlatform();

HRESULT ShutdownPlatform();

void CleanPlatform();

bool IsPlatformShutdown();
