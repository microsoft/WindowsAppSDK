#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::Windows::Storage::Pickers;

namespace winrt::StoragePickersTestApp::implementation
{
    winrt::Windows::Foundation::IAsyncAction MainWindow::OnPickFileClick(Windows::Foundation::IInspectable const& /*sender*/, RoutedEventArgs const& /*args*/)
    {
        // Get the AppWindow ID for the picker
        auto windowId = this->AppWindow().Id();

        // Create the FileOpenPicker with the window ID
        FileOpenPicker picker(windowId);
        picker.FileTypeFilter().Append(L"*");

        // Pick a single file
        auto file = co_await picker.PickSingleFileAsync();

        if (file)
        {
            FilePathTextBox().Text(file.Path());
        }
        else
        {
            FilePathTextBox().Text(L"No file selected");
        }
    }
}
