## Performance guide

For a responsive, fluid app, it helps to prefer compiled bindings, defer UI
you don't need at startup, virtualize long lists, and keep heavy work off the
UI thread. Small choices made early tend to compound as the app grows.

It is recommended to measure before and after any optimization, ideally with
the [Visual Studio Performance Profiler](https://learn.microsoft.com/visualstudio/profiling/)
or [PerfView](https://github.com/microsoft/perfview). Real measurements are
far more reliable than intuition.

For per-task guidance:

- **Compiled bindings**:
  [`{x:Bind}` markup extension](https://learn.microsoft.com/windows/apps/develop/platform/xaml/x-bind-markup-extension)
  is compiled and type-safe; prefer it over `{Binding}` in new XAML.
- **Deferred element loading**:
  [`x:Load` attribute](https://learn.microsoft.com/windows/apps/develop/platform/xaml/x-load-attribute)
  (or `x:DeferLoadStrategy`) keeps off-screen UI out of the initial visual
  tree until it's needed.
- **Long lists and grids**:
  [Optimize ListView and GridView performance](https://learn.microsoft.com/windows/apps/develop/performance/optimize-gridview-and-listview)
  — use virtualizing controls (`ListView`, `GridView`, or `ItemsRepeater`
  with `StackLayout`) rather than a plain `StackPanel`, and stream items in
  with `ISupportIncrementalLoading` when the data set is large.
- **UI thread responsiveness**:
  [Windows app performance overview](https://learn.microsoft.com/windows/apps/performance/)
  — `async`/`await` for I/O, `Task.Run` for CPU-bound work, and steer clear
  of `.Result` or `.GetAwaiter().GetResult()` on the UI thread.
- **Reused resources**: share an `HttpClient` (via `IHttpClientFactory`) and
  cache HTTP responses or computed values when it makes sense.
- **Shallow visual trees**:
  [Optimize your XAML layout](https://learn.microsoft.com/windows/apps/develop/performance/optimize-xaml-layout)
  — deep panel nesting compounds layout cost.

A couple of common pitfalls to watch for: flooding
`DispatcherQueue.TryEnqueue` from background threads, and calling `FindName`
or walking the visual tree in tight loops — both can erode the gains from
everything above.
