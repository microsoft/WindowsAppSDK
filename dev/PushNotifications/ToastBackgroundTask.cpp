#include "pch.h"
#include <ToastBackgroundTask.h>
#include "externs.h"

HRESULT __stdcall ToastBackgroundTask::Activate(
    LPCWSTR appUserModelId,
    LPCWSTR invokedArgs,
    [[maybe_unused]] NOTIFICATION_USER_INPUT_DATA const* data,
    [[maybe_unused]] ULONG dataCount)
{
    return S_OK;
}
