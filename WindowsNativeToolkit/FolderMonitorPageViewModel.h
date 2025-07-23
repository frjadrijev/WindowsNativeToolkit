#pragma once

#include "../ToolkitCore/FileWatcherService.h"
#include "FolderMonitorPageViewModel.g.h"


using namespace winrt::ToolkitCore;

namespace winrt::WindowsNativeToolkit::implementation
{
    struct FolderMonitorPageViewModel : FolderMonitorPageViewModelT<FolderMonitorPageViewModel>
    {
        FolderMonitorPageViewModel() = default;

        // ===== INotifyPropertyChanged =====
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> PropertyChanged;

        // ===== public property exposed in IDL =====
        Windows::Foundation::Collections::IObservableVector<hstring> Changes() const { return m_changes; }

    private:
        void RaiseChanged(std::wstring_view prop);

        Windows::Foundation::Collections::IObservableVector<hstring> m_changes{ winrt::single_threaded_observable_vector<hstring>() };

        ToolkitCore::implementation::FileWatcherService m_watcher;
    };
}

namespace winrt::WindowsNativeToolkit::factory_implementation
{
    struct FolderMonitorPageViewModel : FolderMonitorPageViewModelT<FolderMonitorPageViewModel, implementation::FolderMonitorPageViewModel> {};
}


//namespace winrt::WindowsNativeToolkit::ViewModels::implementation 
//{
//    // ViewModel for the Folder Monitor Page, implementing INotifyPropertyChanged to notify UI of changes.
//    struct FolderMonitorPageViewModel : FolderMonitorPageViewModelT<FolderMonitorPageViewModel>
//    {
//		FolderMonitorPageViewModel() = default;
//
//        // Event to notify property changes, implementing INotifyPropertyChanged.
//        winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> PropertyChanged;
//
//        // Returns an observable vector of file change notifications.
//        winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> Changes() const { return _changes; }
//
//    private:
//        // Raise a property change notification for a specified property, indicated by the std::wstring_view parameter p.
//        void RaiseChanged(std::wstring_view prop);
//
//        // Observable collection to hold file change notifications.
//        winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> _changes{ winrt::single_threaded_observable_vector<winrt::hstring>() };
//
//        // Handle file change notifications by appending the file path of the changed file to a collection and raising a change event.
//        void OnFileChanged(winrt::ToolkitCore::Models::implementation::FileChange const& info);
//    };
//}
//
//namespace winrt::WindowsNativeToolkit::ViewModels::factory_implementation
//{
//    struct FolderMonitorPageViewModel : FolderMonitorPageViewModelT<FolderMonitorPageViewModel, implementation::FolderMonitorPageViewModel>
//    {
//    };
//}
