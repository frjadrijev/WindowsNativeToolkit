#pragma once

#include "FolderMonitorPageViewModel.g.h"
#include <winrt/ToolkitCore.h>   // only include the projection
//#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>

namespace winrt::WindowsNativeToolkit::implementation
{
    struct FolderMonitorPageViewModel : FolderMonitorPageViewModelT<FolderMonitorPageViewModel>
    {
		FolderMonitorPageViewModel()
        {
            Initialize();
        };
     
        hstring FolderPath() const;
        void FolderPath(hstring const& path);

    private:
        void Initialize();
        void RaisePropertyChanged(hstring const& name);

        ToolkitCore::FileWatcherService m_fileWatcherService;
        winrt::hstring                  m_folder;   
        // auto-generated event field by [bindable]
        Microsoft::UI::Xaml::Data::PropertyChangedEventHandler m_propertyChanged;
    };
}

namespace winrt::WindowsNativeToolkit::factory_implementation
{
    struct FolderMonitorPageViewModel : FolderMonitorPageViewModelT<FolderMonitorPageViewModel, implementation::FolderMonitorPageViewModel>
    {
    };
}   