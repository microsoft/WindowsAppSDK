## App architecture guide

For organizing application code, separating presentation, state, and
domain logic into distinct layers tends to scale better than putting
everything in code-behind. The
[MVVM (Model-View-ViewModel) pattern](https://learn.microsoft.com/dotnet/architecture/maui/mvvm)
is the de facto choice for XAML stacks: it pairs naturally with
`{x:Bind}`, makes view models unit-testable, and decouples UI from
business logic.

It is recommended to keep view-model classes free of any
`Microsoft.UI.Xaml.*` references — that's what makes them testable
without a UI thread. The
[CommunityToolkit.Mvvm](https://learn.microsoft.com/dotnet/communitytoolkit/mvvm/)
package eliminates most of the boilerplate (`[ObservableProperty]`,
`[RelayCommand]`, `[NotifyPropertyChangedFor]`) and is the toolkit
used in the WinUI samples.

For per-task guidance:

- **Page-to-page navigation**: `Frame.Navigate(typeof(MyPage),
  parameter)` with `NavigationCacheMode` controlling lifetime —
  [Implement basic navigation](https://learn.microsoft.com/windows/apps/design/basics/navigate-between-two-pages).
- **Top-level layout (nav pane, tabs, breadcrumb)**:
  [Navigation design basics](https://learn.microsoft.com/windows/apps/design/basics/navigation-basics).
- **Dependency injection**: `Microsoft.Extensions.DependencyInjection`
  works the same in WinUI 3 as in ASP.NET Core; wire it up in
  `App.OnLaunched` and resolve services from page constructors —
  [Dependency injection in .NET](https://learn.microsoft.com/dotnet/core/extensions/dependency-injection).
- **Async commands and threading**:
  [Programming guide for async/await in WinUI](https://learn.microsoft.com/windows/apps/develop/threading-async/).
