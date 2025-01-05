<h1 align="center">MRT Core from Windows App SDK</h1>

**MRT Core** (formaly, Core MRT or MRT) was born from the need for [Windows App SDK](https://aka.ms/windowsappsdk) applications to use MRT (Modern Resource Technology), introduced to Windows 8 and evolved as the modern resource management system since then. MRT Core provides support to build resources to Package Resource Index (PRI) files, and load resources from PRI files. The API is exposed to the namespace [Microsoft.Windows.ApplicationModel.Resources](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applicationmodel.resources).

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
- [Pure-C API](mrt/Core/src/MRM.h) over the core runtime
- [WinRT API](mrt/Microsoft.Windows.ApplicationModel.Resources) wrapping the pure-C API
