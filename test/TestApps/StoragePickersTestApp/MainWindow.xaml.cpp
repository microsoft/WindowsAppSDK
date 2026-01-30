// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

namespace winrt::StoragePickersTestApp::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
    }

    void MainWindow::LogResult(winrt::hstring const& message)
    {
        ResultsText().Text(message);
    }

    void MainWindow::TestFileOpenPicker_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        LogResult(L"FileOpenPicker clicked - functionality temporarily disabled for testing");
    }

    void MainWindow::TestFileSavePicker_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        LogResult(L"FileSavePicker clicked - functionality temporarily disabled for testing");
    }

    void MainWindow::TestFolderPicker_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        LogResult(L"FolderPicker clicked - functionality temporarily disabled for testing");
    }
}
