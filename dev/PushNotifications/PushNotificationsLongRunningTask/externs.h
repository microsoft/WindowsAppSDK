#pragma once
#include "pch.h"
#include "platform.h"

wil::unique_event& GetWinMainEvent();

WpnLrpPlatformImpl* GetPlatform();

HRESULT InitializePlatform();

HRESULT ShutdownPlatform();

void CleanPlatform();

wil::unique_threadpool_timer SetTimerForEvent();
