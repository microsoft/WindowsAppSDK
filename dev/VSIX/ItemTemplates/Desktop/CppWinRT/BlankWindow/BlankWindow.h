#pragma once

#include "$safeitemname$.g.h"

namespace winrt::$rootnamespace$::implementation
{
    struct $safeitemname$ : $safeitemname$T<$safeitemname$>
    {
        $safeitemname$()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
            ExtendsContentIntoTitleBar(true); // provides default WinUI custom title bar experience
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::$rootnamespace$::factory_implementation
{
    struct $safeitemname$ : $safeitemname$T<$safeitemname$, implementation::$safeitemname$>
    {
    };
}
