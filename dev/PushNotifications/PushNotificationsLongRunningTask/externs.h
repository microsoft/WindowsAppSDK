#pragma once
#include "pch.h"
#include "platform.h"

wil::unique_event& GetWinMainEvent();

WpnLrpPlatformImpl* RetrievePlatform();

HRESULT InitializePlatform();

HRESULT ShutdownPlatform();

void CleanPlatform();
