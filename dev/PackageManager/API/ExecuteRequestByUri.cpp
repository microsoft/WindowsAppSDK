// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace Microsoft::Windows::Management::Deployment
{
ExecuteRequestByUri_Add::ExecuteRequestByUri_Add(
    winrt::Windows::Foundation::Uri const& packageUri,
    winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions const& options) :
    m_packageUri(packageUri),
    m_options(options),
    m_packageManager(packageManager)
{
}

void ExecuteRequestByUri_Add::Telemetry_Start()
{
    m_packageUriAsString = packageUri.ToString();
    m_logTelemetry = PackageManagementTelemetry::AddPackageByUriAsync::Start(m_packageUriAsString);
}
void ExecuteRequestByUri_Add::Telemetry_Stop()
{
    m_logTelemetry.Stop(m_packageUriAsString);
}
void ExecuteRequestByUri_Add::Telemetry_IgnoreCurrentThread()
{
}
void ExecuteRequestByUri_Add::Telemetry_ContinueOnCurrentThread()
{
}
}
