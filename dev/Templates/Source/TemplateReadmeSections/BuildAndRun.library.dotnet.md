## Build

```powershell
dotnet build
```

There is no `dotnet run` for a class library — it has no entry point. To
exercise it, reference it from a WinUI 3 desktop app project (see
**Consume the library** below) or from a WinUI 3 unit test project
(`dotnet new winui-unittest`).
