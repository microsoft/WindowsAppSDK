// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace wil
{
#if defined(_INC_WTSAPI) && !defined(__WIL_WTSAPI_WTSVIRTUALCHANNELCLOSE)
#define __WIL_WTSAPI_WTSVIRTUALCHANNELCLOSE
    using unique_channel_handle = wil::unique_any_handle_null<decltype(&::WTSVirtualChannelClose), ::WTSVirtualChannelClose>; 
#endif // __WIL_WTSAPI_WTSVIRTUALCHANNELCLOSE
}

