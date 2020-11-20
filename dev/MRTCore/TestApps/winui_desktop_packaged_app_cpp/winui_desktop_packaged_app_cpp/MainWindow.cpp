// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "MainWindow.h"
#include "MainWindow.g.cpp"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Microsoft::ApplicationModel::Resources;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::winui_desktop_packaged_app_cpp::implementation
{
    MainWindow::MainWindow()
    {       
        InitializeComponent();
    }

    MainWindow::~MainWindow()
    {
#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
        MrmDestroyResourceContext(m_overrideResourceContextMrm);
#endif
    }

#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
    void MainWindow::InitializeResourceLoaders(winrt::Microsoft::ApplicationModel::Resources::ResourceManager resourceManagerWinRT, MrmManagerHandle resourceManagerMrm)
#else
    void MainWindow::InitializeResourceLoaders(winrt::Microsoft::ApplicationModel::Resources::ResourceManager resourceManagerWinRT)
#endif 
    {
        m_resourceManagerWinRT = resourceManagerWinRT;

#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
        m_resourceManagerMrm = resourceManagerMrm;
#endif

        // Create custom resource context for the window. Set the language to German.
        m_overrideResourceContext = m_resourceManagerWinRT.CreateResourceContext();
        m_overrideResourceContext.QualifierValues().Insert(L"Language", L"de-DE");

#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
        check_hresult(MrmCreateResourceContext(m_resourceManagerMrm, &m_overrideResourceContextMrm));
        check_hresult(MrmSetQualifier(m_overrideResourceContextMrm, L"Language", L"de-DE"));
#endif
    }

    void MainWindow::defaultWinrtApi_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto stringResourceCandidate = m_resourceManagerWinRT.MainResourceMap().GetValue(L"Resources/SampleString");
        output().Text(stringResourceCandidate.ValueAsString());
    }

    void MainWindow::overrideWinrtApi_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto stringResourceCandidate = m_resourceManagerWinRT.MainResourceMap().GetValue(L"Resources/SampleString", m_overrideResourceContext);
        output().Text(stringResourceCandidate.ValueAsString());
    }

    void MainWindow::defaultCApi_Click(IInspectable const&, RoutedEventArgs const&)
    {
#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
        wchar_t* resourceString = nullptr;
        check_hresult(MrmLoadStringResource(m_resourceManagerMrm, nullptr, nullptr, L"Resources/SampleString", &resourceString));
        output().Text(hstring(resourceString));
        MrmFreeResource(resourceString);
#endif
    }

    void MainWindow::overrideCApi_Click(IInspectable const&, RoutedEventArgs const&)
    {
#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
        wchar_t* resourceString = nullptr;
        check_hresult(MrmLoadStringResource(m_resourceManagerMrm, m_overrideResourceContextMrm, nullptr, L"Resources/SampleString", &resourceString));
        output().Text(hstring(resourceString));
        MrmFreeResource(resourceString);
#endif
    }

    void MainWindow::fallbackWinrt_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto stringResourceCandidate = m_resourceManagerWinRT.MainResourceMap().GetValue(L"Resources/LegacyString");
        output().Text(stringResourceCandidate.ValueAsString());
    }
}
