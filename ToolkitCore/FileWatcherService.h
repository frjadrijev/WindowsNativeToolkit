#pragma once
#include "pch.h"

#include "FileWatcherService.g.h"   // generated partial class
#include "FileWatcherNative.h"      // your Win32 helper
#include <winrt/ToolkitCore.h>      // projection for FileChange etc.

namespace winrt::ToolkitCore::implementation
{
    struct FileWatcherService : FileWatcherServiceT<FileWatcherService>
    {
        FileWatcherService() = default;

        // IFileWatcherService overrides
        void Start(winrt::hstring const& folder);
        void Stop();

        winrt::event_token FileWatcherService::Changed(FileWatcherChangedHandler const& handler);
        void FileWatcherService::Changed(winrt::event_token const& token);

    private:
        native::ToolkitCore::FileWatcherNative m_native{};
        winrt::event<FileWatcherChangedHandler> m_changed;
    };
}

namespace winrt::ToolkitCore::factory_implementation
{
    struct FileWatcherService : FileWatcherServiceT<FileWatcherService, implementation::FileWatcherService> {};
}
