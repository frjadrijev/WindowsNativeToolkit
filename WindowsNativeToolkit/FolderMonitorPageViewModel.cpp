#include "pch.h"
#include "FolderMonitorPageViewModel.h"
#if __has_include("FolderMonitorPageViewModel.g.cpp")
#include "FolderMonitorPageViewModel.g.cpp"
#endif

using namespace winrt::ToolkitCore;

namespace winrt::WindowsNativeToolkit::implementation
{
    FolderMonitorPageViewModel::FolderMonitorPageViewModel()
    {
        // start FileWatcher once, forward notifications into the observable vector
        m_watcher.Start(LR"(C:\Temp)", [weak = get_weak()](ToolkitCore::FileChange const& fc) // <-- Fix: Use correct namespace/type
            {
                if (auto self = weak.get())
                {
                    self->m_changes.Append(winrt::hstring{ fc.path });
                    self->RaiseChanged(L"Changes");
                }
            }
        );
    }

    void FolderMonitorPageViewModel::RaiseChanged(std::wstring_view prop)
    {
        PropertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ prop });
    }
}
