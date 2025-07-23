#pragma once

#include "FolderMonitorPage.g.h"

namespace winrt::WindowsNativeToolkit::implementation
{
    struct FolderMonitorPage : FolderMonitorPageT<FolderMonitorPage>
    {
        FolderMonitorPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WindowsNativeToolkit::factory_implementation
{
    struct FolderMonitorPage : FolderMonitorPageT<FolderMonitorPage, implementation::FolderMonitorPage>
    {
    };
}
