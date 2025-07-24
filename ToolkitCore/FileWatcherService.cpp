#include "pch.h"
#include "FileWatcherService.h"
#if __has_include("FileWatcherService.g.cpp")
#include "FileWatcherService.g.cpp"
#endif

namespace winrt::ToolkitCore::implementation
{
    void FileWatcherService::Start(hstring const& folder)
    {
        m_native.Start(folder, [weak = get_weak()](auto const& fcNative)
        {
            if (auto self = weak.get())
            {
                ToolkitCore::FileChange fcProjected{ fcNative.Path(), fcNative.Type(), fcNative.Timestamp() };
                self->m_changed(*self, fcProjected);
			}
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
