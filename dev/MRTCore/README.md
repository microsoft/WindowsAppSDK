<h1 align="center">MRT Core</h1>

**MRT Core** (formaly, Core MRT) is implemented as a part of [Windows App SDK](https://aka.ms/windowsappsdk) so that develoers can utilize MRT (Modern Resource Technology), which was introduced to Windows 8 as a part of UWP and evolved as the modern resource management system. MRT Core provides support to build resources to Package Resource Index (PRI) files and load resources from PRI files.

## Accessibility

- WASDK 1.0 onwards: [Microsoft.Windows.ApplicationModel.Resources](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applicationmodel.resources)
- Prior to WASDK 1.0: [Microsoft.ApplicationModel.Resources](https://learn.microsoft.com/ja-jp/windows/windows-app-sdk/api/winrt/microsoft.applicationmodel.resources?view=windows-app-sdk-0.8)

## Getting started with MRT Core

- [About MRT Core & PRI](https://learn.microsoft.com/windows/apps/windows-app-sdk/mrtcore/mrtcore-overview)
- [Migrate from MRT in UWP to MRT Core in WASDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/migrate-to-windows-app-sdk/guides/mrtcore)
- [Globalization and localization](https://learn.microsoft.com/windows/apps/design/globalizing/globalizing-portal)
- [Qualify your resources](https://learn.microsoft.com/windows/apps/windows-app-sdk/mrtcore/tailor-resources-lang-scale-contrast)
- [Localize your strings](https://learn.microsoft.com/windows/apps/windows-app-sdk/mrtcore/localize-strings)
- [About PRI in Win32](https://learn.microsoft.com/en-us/windows/win32/menurc/pri-indexing-reference)

## Building from source

Open Visual Studio with `MrtCore.sln` and build the solution.

The source code consists of three parts:
- [The core runtime](mrt/mrm)
  - [PRI builder](mrt/mrm/include/mrm/build)
- [Flat-C API](mrt/Core/src/MRM.h) over the core runtime
- [WinRT API](mrt/Microsoft.Windows.ApplicationModel.Resources) wrapping the flat-C API

## Resource name limits

PRI files store each resource name segment's length in one byte. Each segment
must therefore contain at most 255 UTF-16 code units. This limit applies to both
resource names and resource map (scope) names, for ASCII and Unicode resources.
Names containing `/` or `\` are hierarchical paths; the limit applies separately
to each segment, not to the combined path. For example, a 255-character scope
and a 255-character resource name can form a valid 511-character path.

The MRT Core PRI builder rejects an overlong segment with
`HRESULT_FROM_WIN32(ERROR_FILENAME_EXCED_RANGE)` (`0x800700CE`) and logs a
diagnostic identifying the segment and the 255-code-unit limit. Shorten the
segment or split the name into multiple nonempty path segments. The `.resw`
schema's `xsd:string` type and Visual Studio's resource editor do not enforce
this PRI format limit.
