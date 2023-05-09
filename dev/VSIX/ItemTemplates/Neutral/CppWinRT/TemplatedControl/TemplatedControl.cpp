#include "pch.h"
#include "$safeitemname$.h"
#include "$safeitemname$.g.cpp"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::$rootnamespace$::implementation
{
    $safeitemname$::$safeitemname$()
    {
        DefaultStyleKey(winrt::box_value(xaml_typename<class_type>()));
    }
}
