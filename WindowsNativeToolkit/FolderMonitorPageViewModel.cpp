#include "pch.h"
#include "FolderMonitorPageViewModel.h"
#if __has_include("FolderMonitorPageViewModel.g.cpp")
#include "FolderMonitorPageViewModel.g.cpp"
#endif

namespace winrt::WindowsNativeToolkit::implementation
{
    hstring FolderMonitorPageViewModel::FolderPath() const 
    { 
        return m_folder; 
    }

    void FolderMonitorPageViewModel::FolderPath(hstring const& path)
    {
        // Update internal folder path storage
        m_folder = path;
        
        // Notify UI bindings that FolderPath property has changed
        RaisePropertyChanged(L"FolderPath");
    }

    void FolderMonitorPageViewModel::RaisePropertyChanged(hstring const& name)
    {
        // Only fire event if handlers are registered (UI bindings exist)
        if (m_propertyChanged)
            m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ name });
    }

    void FolderMonitorPageViewModel::Initialize()
    {
        // Set up file monitoring service event handler using weak reference pattern
        // This prevents circular references and enables proper cleanup
        m_fileWatcherService.Changed(
            [weak = get_weak()](auto const&, ToolkitCore::FileChange const& fc)
            {
                // Use weak reference to safely access ViewModel
                if (auto self = weak.get())
                {
                    // TODO: Process file change events and update UI
                    // Potential enhancements:
                    // - Update file list collections
                    // - Show change notifications
                    // - Update monitoring statistics
                    // - Handle different change types (add, remove, modify)
                }
                // If weak reference is null, ViewModel was destroyed - safely ignore event
            });

        // Set initial demo data to verify data binding functionality
        FolderPath(L"Hello binding – it works!");
    }
}
