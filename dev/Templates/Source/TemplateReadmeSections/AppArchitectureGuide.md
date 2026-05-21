## App architecture guide

- Use the [MVVM pattern](https://learn.microsoft.com/dotnet/architecture/maui/mvvm) — pairs naturally with `{x:Bind}` and keeps view models unit-testable.
- Keep view models free of `Microsoft.UI.Xaml.*` references so they run without a UI thread.
- Reduce boilerplate with [CommunityToolkit.Mvvm](https://learn.microsoft.com/dotnet/communitytoolkit/mvvm/) (`[ObservableProperty]`, `[RelayCommand]`, `[NotifyPropertyChangedFor]`).
- Wire up DI with `Microsoft.Extensions.DependencyInjection` in `App.OnLaunched`; resolve services from page constructors.
- Navigate with `Frame.Navigate(typeof(MyPage), parameter)`; control lifetime via `NavigationCacheMode`.

For more, see [Navigation design basics](https://learn.microsoft.com/windows/apps/design/basics/navigation-basics) and [Async/await in WinUI](https://learn.microsoft.com/windows/apps/develop/threading-async/).
