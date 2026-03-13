# Windows AI Platform Requirements

## Supported Architectures

Windows AI APIs are supported on the following architectures:

| Architecture | Supported |
|-------------|-----------|
| **x64** | Yes |
| **ARM64** | Yes |
| **x86** | No |

x86 applications will receive `REGDB_E_CLASSNOTREG (0x80040154)` at runtime
when attempting to call WCR APIs such as `GetReadyState()`. There is no plan
to add x86 support at this time.

If your application targets x86, you should either:
- Retarget to x64 or ARM64 to use WCR features.
- Guard WCR API calls with architecture checks and provide alternative
  behavior for x86 builds.

## Hardware Requirements

WCR features require **Copilot+ PC** hardware with a Neural Processing Unit
(NPU). On devices without the required hardware, `GetReadyState()` will return
`NotSupportedOnCurrentSystem` (see return type [AIReadyState documentation]([url](https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.windows.ai.aifeaturereadystate?view=windows-app-sdk-1.8)) for more info.

## OS Requirements

- Windows 11 with Copilot+ capable hardware
- Appropriate Windows Update servicing updates installed
- [AI model packages available via Windows Update](https://learn.microsoft.com/en-us/windows/release-health/ai-components-release-information)

## Ready to Get Started?
Check out [Get started building an app with Windows AI APIs](https://learn.microsoft.com/en-us/windows/ai/apis/get-started?tabs=winget%2Cwinui%2Cwinui2) on Microsoft Learn.
