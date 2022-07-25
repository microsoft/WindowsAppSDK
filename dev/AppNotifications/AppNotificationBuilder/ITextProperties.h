#pragma once
#include "pch.h"

MIDL_INTERFACE("48867D7F-0200-405C-8D22-7E8AC5A22110") ITextProperties : IInspectable
{
    virtual int GetMaxLines() = 0;
    virtual winrt::hstring GetLanguage() = 0;
    virtual bool GetCallScenarioAlign() = 0;
};
