#include "pch.h"
#include <iostream>
#include <testdef.h>

using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::ProjectReunion;

void SignalPhase(const std::wstring& phaseEventName)
{
    wil::unique_event phaseEvent;
    if (phaseEvent.try_open(phaseEventName.c_str(), EVENT_MODIFY_STATE, false))
    {
        phaseEvent.SetEvent();
    }
}

bool IsPackagedProcess()
{
    WCHAR idNameBuffer[PACKAGE_FULL_NAME_MAX_LENGTH + 1];
    UINT32 idNameBufferLen = ARRAYSIZE(idNameBuffer);
    if (::GetCurrentPackageFullName(&idNameBufferLen, idNameBuffer) == ERROR_SUCCESS)
    {
        return true;
    }

    return false;
}

int main()
{
    bool succeeded = true;
    SignalPhase(c_testProtocolPhaseEventName);
    return 0;
}
