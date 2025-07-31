#include "pch.h"
#include "FolderMonitorPageViewModel.h"
#if __has_include("FolderMonitorPageViewModel.g.cpp")
#include "FolderMonitorPageViewModel.g.cpp"
#endif

namespace winrt::WindowsNativeToolkit::implementation
{
    hstring FolderMonitorPageViewModel::FolderPath() const { return m_folder; }
    void FolderMonitorPageViewModel::FolderPath(hstring const& path)
    {
        m_folder = path;
        RaisePropertyChanged(L"FolderPath");
    }

    void FolderMonitorPageViewModel::RaisePropertyChanged(hstring const& name)
    {
        if (m_propertyChanged)
            m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ name });
    }


    // wire-up service
    void FolderMonitorPageViewModel::Initialize()
    {
        m_fileWatcherService.Changed(
            [weak = get_weak()](auto const&, ToolkitCore::FileChange const& fc)
            {
                if (auto self = weak.get())
                {
                    // update properties, collections, etc.
                }
            });

        FolderPath(L"Hello binding – it works!");
    }
}
