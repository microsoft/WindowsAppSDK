#pragma once
#include "pch.h"
#include "platform.h"

wil::unique_event& GetWinMainEvent();

NotificationsLongRunningPlatformImpl* GetPlatform();

HRESULT InitializePlatform();

HRESULT ShutdownPlatform();

void CleanPlatform();

bool IsPlatformShutdown();

void SetTimerForEvent();
void CancelTimerForEvent();
