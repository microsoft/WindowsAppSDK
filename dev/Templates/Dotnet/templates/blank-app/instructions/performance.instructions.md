---
description: 'Performance requirements for data binding, layout, threading, and collection virtualization'
applyTo: '**/*.cs, **/*.xaml'
---

# Performance

These rules apply to **every feature and change**. They are not optional add-ons.

---

## Rules

- **Use `x:Bind`** (compiled bindings) instead of `{Binding}` — it's faster and type-safe.
- Use **`x:Load`** (or `x:DeferLoadStrategy`) to defer loading of UI elements not immediately visible.
- Avoid heavy work on the UI thread — use `Task.Run` for CPU-bound work and `async/await` for I/O.
- Use **virtualizing panels** (`ItemsRepeater` with `StackLayout`, or `ListView`) for long lists — never use `StackPanel` with hundreds of items.
- **Cache** expensive computations and HTTP responses when appropriate.
- Minimize XAML visual tree depth — deep nesting hurts layout performance.
- Use **incremental loading** (`ISupportIncrementalLoading`) for large data sets.
- Profile with **Visual Studio Diagnostics Tools** and **PerfView** before and after optimizations.
- Be cautious with `DispatcherQueue.TryEnqueue` — don't flood the dispatcher queue.

## Anti-patterns

- Blocking the UI thread with `.Result` or `.GetAwaiter().GetResult()`.
- Loading all data upfront when only a subset is needed.
- Creating new `HttpClient` instances per request (use `IHttpClientFactory`).
- Using `FindName()` or `VisualTreeHelper` in tight loops.

## Validation

- Build & register the MSIX package — see **Build, Run & Deploy** in `.github/agents/Agents.md`.

### Verification Checklist

- [ ] No blocking calls on the UI thread
- [ ] `x:Bind` is used instead of `{Binding}`
- [ ] Large lists use virtualization

## Must Read & Research

> **Agent Rule:** Before any performance-sensitive change (data binding, layout, collections, async), you **must** fetch and review these references using `fetch_webpage`. Apply what you learn.

| # | Reference | When to consult |
|---|---|---|
| 1 | [Performance best practices for WinUI 3](https://learn.microsoft.com/en-us/windows/apps/performance/) | Any change touching UI rendering, data loading, or threading |
| 2 | [x:Bind markup extension](https://learn.microsoft.com/en-us/windows/uwp/xaml-platform/x-bind-markup-extension) | Adding or modifying XAML data bindings |
| 3 | [x:Load attribute](https://learn.microsoft.com/en-us/windows/uwp/xaml-platform/x-load-attribute) | Deferring UI element loading |
| 4 | [Optimize XAML layout](https://learn.microsoft.com/en-us/windows/apps/performance/optimize-xaml-layout) | Restructuring XAML panels, reducing visual tree depth |
| 5 | [ListView optimization](https://learn.microsoft.com/en-us/windows/apps/performance/optimize-listview) | Working with lists, collections, or `ItemsRepeater` |


