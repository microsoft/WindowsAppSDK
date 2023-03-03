// MicroAppHost.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <locale>
#include <wil/stl.h>
#include <wil/resource.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.Input.h>

using namespace winrt;
using namespace Windows::Data::Json;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Shapes;
using namespace Windows::UI::Xaml::Input;

int main()
{
    int argc;
    wil::unique_hlocal_ptr<PWSTR[]> argv{ CommandLineToArgvW(GetCommandLineW(), &argc)};

    std::wifstream registrationJson(argv.get()[1]);
    std::wstring content((std::istreambuf_iterator<wchar_t>(registrationJson)), (std::istreambuf_iterator<wchar_t>()));

    JsonValue jsonValue = JsonValue::Parse(winrt::to_hstring(content.c_str()));

    // Print the contents of the JSON file
    std::wstringstream buffer;
    buffer << jsonValue.Stringify().c_str();
    std::wcout << buffer.str() << std::endl;

    /*for (int i = 0; i < argc; i++)
    {
        std::wcout << "Arg" << i << " " << argv.get()[i] << std::endl;
    }*/
}
