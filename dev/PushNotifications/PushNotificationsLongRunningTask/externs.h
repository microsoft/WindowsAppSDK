#pragma once
#include "pch.h"
#include "platform.h"

wil::unique_event& GetWinMainEvent();

WpnLrpPlatformImpl* GetPlatform();

HRESULT InitializePlatform();

void CleanPlatform();
