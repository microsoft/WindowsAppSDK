# Windows Copilot Runtime (WCR) Platform Requirements

## Supported Architectures

Windows Copilot Runtime APIs are supported on the following architectures:

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
`NotReady` or `Unavailable`.

## Affected APIs

The following WCR APIs are subject to these platform requirements:

- `Microsoft.Windows.AI.Generative.LanguageModel` (Phi Silica)
- `Microsoft.Windows.AI.Generative.ImageDescriptionGenerator`
- `Microsoft.Windows.AI.Imaging.ImageSuperResolution`
- `Microsoft.Windows.AI.ContentModeration.TextRecognizer`

## OS Requirements

- Windows 11 with Copilot+ capable hardware
- Appropriate Windows Update servicing updates installed
- AI model packages available via Windows Update
