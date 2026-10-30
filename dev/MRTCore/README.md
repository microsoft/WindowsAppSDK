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

The managed test projects use .NET 10 LTS. Use Visual Studio 2026 for IDE builds
targeting .NET 10. The shared Foundation pipeline installs SDK 10.0.114 from the
10.0.1xx band, which can load in MSBuild 17.14; later SDK feature bands require
MSBuild 18. The standalone MRT SDK installer reads
`CsWinRTDependencyDotNetCoreSdkPackageVersion` from the root
`Directory.Packages.props`, not the MRT `global.json` MSBuild SDK declaration.

The test runtime packs are pinned to 10.0.14 in `Directory.Packages.props`.
TAEF uses the self-contained `net10` CoreCLR profile on x86, x64, and ARM64.
The minimum test OS remains Windows 10 version 1809; .NET 10 support on that
version is limited to supported Enterprise LTSC editions. Production projection
target frameworks and package layouts are unchanged.

The source code consists of three parts:
- [The core runtime](mrt/mrm)
  - [PRI builder](mrt/mrm/include/mrm/build)
- [Flat-C API](mrt/Core/src/MRM.h) over the core runtime
- [WinRT API](mrt/Microsoft.Windows.ApplicationModel.Resources) wrapping the flat-C API
