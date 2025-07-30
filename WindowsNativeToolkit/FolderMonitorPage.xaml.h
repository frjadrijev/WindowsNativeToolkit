#pragma once

#include "FolderMonitorPage.g.h"
#include <FolderMonitorPageViewModel.h>

namespace winrt::WindowsNativeToolkit::implementation
{
    struct FolderMonitorPage : FolderMonitorPageT<FolderMonitorPage>
    {
        FolderMonitorPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
            Initialize();
        }
        WindowsNativeToolkit::FolderMonitorPageViewModel ViewModel() const noexcept;
    private:
        void Initialize(); 
        WindowsNativeToolkit::FolderMonitorPageViewModel m_vm{ nullptr };
    };
}

namespace winrt::WindowsNativeToolkit::factory_implementation
{
    struct FolderMonitorPage : FolderMonitorPageT<FolderMonitorPage, implementation::FolderMonitorPage>
    {
    };
}
