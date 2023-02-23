// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

#include <KozaniRemoteManager_h.h>
#include "KozaniDvc-Constants.h"

using namespace winrt::Windows::Foundation;
using namespace Microsoft::Kozani::Dvc;

int main(int argc, char* argv[]) try
{
    if (argc < 3)
    {
        return E_INVALIDARG;
    }

    if (_stricmp(argv[1], Constants::ConnectionIdSwitch) != 0)
    {
        return E_INVALIDARG;
    }

    auto uninitOnExit = wil::CoInitializeEx();

    PCSTR connectionId = argv[2];
    auto remoteManager = wil::CoCreateInstance<KozaniRemoteManager, IKozaniRemoteManager>(CLSCTX_LOCAL_SERVER);
    return remoteManager->Connect(connectionId);
}
CATCH_RETURN()
