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
    bool succeeded = false;
    auto args = AppLifecycle::GetActivatedEventArgs();
    auto kind = args.Kind();
    // Check if the process is unpackaged/packaged and test accordingly
    if (IsPackagedProcess())
    {
        // This will be the only way this process is launched via TAEF
        if (kind == ActivationKind::Protocol) {
            auto protocolArgs = args.as<IProtocolActivatedEventArgs>();
            // Switch on this variable to run specific components (uri://ComponentToTest)
            Uri actualUri = protocolArgs.Uri();
            std::wstring expectedUri = c_testProtocolScheme_Packaged + L"://this_is_a_test";
            if (actualUri.Equals(Uri(expectedUri)))
            {
                // Signal TAEF that protocol was activated and valid.
                SignalPhase(c_testProtocolPhaseEventName);
                succeeded = true;
            }
        }
    }
    
    if (!succeeded)
    {
        // Signal TAEF that the test failed
        SignalPhase(c_testFailureEventName);
    }
    return 0;
}
