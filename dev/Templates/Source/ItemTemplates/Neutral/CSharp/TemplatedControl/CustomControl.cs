using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Documents;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

// To add another templated control to this project (which already has a
// Themes\Generic.xaml), run with `--IncludeDefaultStyle false` or `-I false`:
//
//     dotnet new winui-templatedcontrol -n NewName --IncludeDefaultStyle false
//
// Then open Themes\Generic.xaml and add a <Style TargetType="local:NewName">
// block. Without it, the new control will render blank at runtime.

namespace $rootnamespace$;

public sealed partial class $safeitemname$ : Control
{
    public $safeitemname$()
    {
        DefaultStyleKey = typeof($safeitemname$);
    }
}
