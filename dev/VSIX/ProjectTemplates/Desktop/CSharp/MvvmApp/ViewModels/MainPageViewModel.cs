using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace $safeprojectname$.ViewModels;

/// <summary>
/// Sample ViewModel using CommunityToolkit.Mvvm partial property syntax.
/// Uses <see cref="ObservableProperty"/> for change notification and
/// <see cref="RelayCommand"/> for command binding.
/// </summary>
public partial class MainPageViewModel : ObservableObject
{
    [ObservableProperty]
    public partial string Greeting { get; set; } = "Hello, WinUI!";

    [RelayCommand]
    private void UpdateGreeting()
    {
        Greeting = $"Updated at {DateTime.Now:T}";
    }
}
