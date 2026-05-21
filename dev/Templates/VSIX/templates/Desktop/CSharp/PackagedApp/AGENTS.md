# WinUI 3 desktop app (two-project packaged)

A two-project WinUI 3 desktop app: a `.csproj` for code and a `.wapproj`
for MSIX packaging. Built on the Windows App SDK.

> [!TIP]
> If you're starting a new app, prefer the single-project **WinUI 3
> desktop app** template — it packages itself directly from the `.csproj`,
> no `.wapproj` required. Use this two-project shape only when you need
> the `.wapproj` indirection (for example, to package multiple processes
> together or to interop with existing `.wapproj`-based build flows).

## Project layout

```
MySolution.sln
├── MyApp/                       # The code project
│   ├── App.xaml, App.xaml.cs
│   ├── MainWindow.xaml, MainWindow.xaml.cs
│   ├── Properties/
│   ├── app.manifest
│   └── MyApp.csproj
└── MyApp.Package/               # The packaging project
    ├── Images/                  # Tile, splash, store logos
    ├── Package.appxmanifest     # App identity and capabilities
    └── MyApp.Package.wapproj
```

The `.wapproj` references the `.csproj` and owns the manifest, visual
assets, and MSIX output. The `.csproj` owns code, XAML, and target
framework.

####Prerequisites.md####

####BuildAndRun.wapproj.vsix.md####

####CommonNextSteps.wapproj.vsix.md####

####PublishGuide.wapproj.vsix.md####

####AppArchitectureGuide.md####

####TestingGuide.md####

####PerformanceGuide.md####

####AccessibilityGuide.md####

####GlobalizationGuide.md####

####SecurityGuide.md####

####DocumentationGuide.md####

---

####FrameworkFooter.vsix.md####
