// FileWatcherService.h
#pragma once
#include "pch.h"

#include "FileWatcherService.g.h"   // generated partial class
#include "FileWatcherNative.h"      // your Win32 helper

namespace winrt::ToolkitCore::implementation
{
    // ❶  Derive from the generated CRTP helper
    struct FileWatcherService : FileWatcherServiceT<FileWatcherService>
    {
        FileWatcherService() = default;

        // IFileWatcherService overrides
        void Start(winrt::hstring const& folder);
        void Stop();

    private:
        native::ToolkitCore::FileWatcherNative m_native{};
        winrt::event<FileWatcherChangedHandler> m_changed;
    };
}

// ❷  Factory implementation shim that CppWinRT expects
namespace winrt::ToolkitCore::factory_implementation
{
    struct FileWatcherService : FileWatcherServiceT<FileWatcherService, implementation::FileWatcherService> {};
}
