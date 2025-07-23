#include "pch.h"
#include "FileWatcherService.h"
#if __has_include("FileWatcherService.g.cpp")
#include "FileWatcherService.g.cpp"
#endif
#include <winrt/ToolkitCore.h>      // projection for FileChange etc.

namespace winrt::ToolkitCore::implementation
{
    void FileWatcherService::Start(hstring const& folder)
    {
        m_native.Start(folder, [weak = get_weak()](auto const& fcNative)
            {
                if (auto self = weak.get())
                {
                    // *** 1. activate a WinRT FileChange ***
                    ToolkitCore::FileChange fcProjected = make<ToolkitCore::FileChange>();
                    // *** 2. copy data across ***
                    fcProjected.Path(fcNative.Path());
                    fcProjected.Type(static_cast<ChangeType>(fcNative.Type()));
                    fcProjected.Timestamp(fcNative.Timestamp());
                    // *** 3. raise the event ***
                    self->m_changed(*self, fcProjected);
				}
            });
    }

    void FileWatcherService::Stop()
    {
        m_native.Stop();
    }
}
