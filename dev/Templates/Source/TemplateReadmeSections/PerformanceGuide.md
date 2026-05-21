## Performance guide

- Prefer compiled bindings: use [`{x:Bind}`](https://learn.microsoft.com/windows/apps/develop/platform/xaml/x-bind-markup-extension) over `{Binding}`.
- Defer off-screen UI with [`x:Load`](https://learn.microsoft.com/windows/apps/develop/platform/xaml/x-load-attribute) (or `x:DeferLoadStrategy`).
- Virtualize long lists: `ListView` / `GridView` / `ItemsRepeater` with `StackLayout`; stream large data sets with `ISupportIncrementalLoading`.
- Keep heavy work off the UI thread: `async` / `await` for I/O, `Task.Run` for CPU; never call `.Result` or `.GetAwaiter().GetResult()`.
- Reuse `HttpClient` (via `IHttpClientFactory`); avoid deep panel nesting and `FindName` / visual-tree walks in tight loops.
- Measure before and after with the [Visual Studio Performance Profiler](https://learn.microsoft.com/visualstudio/profiling/) or [PerfView](https://github.com/microsoft/perfview).

For more, see [Windows app performance overview](https://learn.microsoft.com/windows/apps/performance/).
