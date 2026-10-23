using Microsoft.UI.Xaml;

namespace $safeprojectname$;

// VSTest owns the process; its UI dispatcher needs an application without an apphost XAML resource root.
public sealed class VSTestApplication : Application
{
}
