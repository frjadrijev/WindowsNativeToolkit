#include "pch.h"
#include "FileWatcherService.h"
#if __has_include("FileWatcherService.g.cpp")
#include "FileWatcherService.g.cpp"
#endif

namespace winrt::ToolkitCore::implementation
{
    void FileWatcherService::Start(hstring const& folder)
    {
        // Start native watcher with internal callback that converts native events to WinRT events
        m_native.Start(folder, [weak = get_weak()](auto const& fcNative)
        {
            // Use weak reference to prevent circular references and enable proper cleanup
            if (auto self = weak.get())
            {
                // Convert native FileChange to projected WinRT FileChange
                ToolkitCore::FileChange fcProjected{ fcNative.Path(), fcNative.Type(), fcNative.Timestamp() };
                
                // Fire the WinRT event with this service as sender and projected change data
                self->m_changed(*self, fcProjected);
            }
            // If weak reference is null, service was destroyed - silently ignore event
        });
    }

    void FileWatcherService::Stop()
    {
        m_native.Stop();
    }

    event_token FileWatcherService::Changed(FileWatcherChangedHandler const& handler)
    {
        return m_changed.add(handler);
    }
    
    void FileWatcherService::Changed(event_token const& token)
    {
        m_changed.remove(token);
    }
}
