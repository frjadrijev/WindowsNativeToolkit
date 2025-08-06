#pragma once
#include "pch.h"

#include "FileWatcherService.g.h"   // generated partial class
#include "FileWatcherNative.h"      // your Win32 helper
#include <winrt/ToolkitCore.h>      // projection for FileChange etc.

namespace winrt::ToolkitCore::implementation
{
    /// <summary>
    /// Implementation of the FileWatcherService Windows Runtime component.
    /// Provides a managed wrapper around native Win32 file system monitoring
    /// capabilities, exposing them through a clean WinRT interface.
    /// </summary>
    /// <remarks>
    /// This class bridges the gap between low-level Win32 file monitoring APIs
    /// and the higher-level Windows Runtime event model. It manages the lifetime
    /// of native resources and ensures proper cleanup when the service is stopped
    /// or the object is destroyed.
    /// 
    /// Architecture:
    /// - Uses composition to delegate actual monitoring to FileWatcherNative
    /// - Provides event marshaling from native callbacks to WinRT events
    /// - Implements weak reference pattern to prevent circular references
    /// - Thread-safe event handling with proper synchronization
    /// 
    /// Lifecycle:
    /// 1. Construction creates the service in stopped state
    /// 2. Start() begins monitoring and activates the native watcher
    /// 3. File changes trigger callbacks that fire WinRT events
    /// 4. Stop() cleanly shuts down monitoring and releases resources
    /// 5. Destruction automatically stops monitoring if still active
    /// </remarks>
    struct FileWatcherService : FileWatcherServiceT<FileWatcherService>
    {
        /// <summary>
        /// Default constructor that creates a new FileWatcherService instance.
        /// The service starts in a stopped state and requires explicit Start() call.
        /// </summary>
        FileWatcherService() = default;

        // IFileWatcherService interface implementations

        /// <summary>
        /// Begins monitoring the specified folder for file system changes.
        /// This method activates the underlying native file watcher and starts
        /// raising events for detected changes.
        /// </summary>
        /// <param name="folder">
        /// Full path to the directory to monitor. Must exist and be accessible.
        /// Monitoring includes all subdirectories recursively.
        /// </param>
        /// <exception cref="hresult_invalid_argument">
        /// Thrown when folder parameter is empty or contains invalid characters.
        /// </exception>
        /// <exception cref="hresult_error">
        /// Thrown when the folder doesn't exist, access is denied, or the native
        /// watcher fails to initialize for any other reason.
        /// </exception>
        /// <remarks>
        /// This method is safe to call multiple times - subsequent calls while
        /// already monitoring will be ignored. To monitor a different folder,
        /// call Stop() first, then Start() with the new path.
        /// 
        /// The monitoring operation runs on a background thread and will continue
        /// until Stop() is called or the object is destroyed.
        /// </remarks>
        void Start(winrt::hstring const& folder);

        /// <summary>
        /// Stops monitoring the current folder and releases all associated resources.
        /// This method cleanly shuts down the background monitoring thread and
        /// ensures no further events will be raised.
        /// </summary>
        /// <remarks>
        /// This method is safe to call multiple times and will gracefully handle
        /// cases where monitoring is not currently active. It blocks until the
        /// monitoring thread has completely shut down, ensuring no race conditions.
        /// 
        /// After calling Stop(), the service can be restarted by calling Start()
        /// again with the same or different folder path.
        /// </remarks>
        void Stop();

        /// <summary>
        /// Adds an event handler for file system change notifications.
        /// </summary>
        /// <param name="handler">
        /// Delegate to invoke when file changes are detected. The handler receives
        /// the FileWatcherService instance and a FileChange object with details.
        /// </param>
        /// <returns>
        /// Event token that can be used to unregister the handler later.
        /// Store this token to enable proper cleanup of event subscriptions.
        /// </returns>
        /// <remarks>
        /// Event handlers are called on a background thread, not the UI thread.
        /// If updating UI elements, marshal the call to the appropriate dispatcher.
        /// 
        /// Multiple handlers can be registered and will all be called for each
        /// detected change. Handlers should complete quickly to avoid blocking
        /// the monitoring thread and potentially missing subsequent changes.
        /// </remarks>
        winrt::event_token Changed(FileWatcherChangedHandler const& handler);

        /// <summary>
        /// Removes a previously registered event handler for file system changes.
        /// </summary>
        /// <param name="token">
        /// Event token returned from a previous call to the Changed() registration method.
        /// If the token is invalid or the handler was already removed, this call is ignored.
        /// </param>
        /// <remarks>
        /// Always unregister event handlers before allowing handler objects to be
        /// destroyed to prevent access violations when events are fired.
        /// 
        /// This method is thread-safe and can be called from any thread.
        /// </remarks>
        void Changed(winrt::event_token const& token);

    private:
        /// <summary>
        /// Native file watcher implementation that handles low-level Win32 APIs.
        /// This member provides the actual file system monitoring functionality
        /// while this class provides the WinRT wrapper and event management.
        /// </summary>
        native::ToolkitCore::FileWatcherNative m_native{};
        
        /// <summary>
        /// WinRT event container for managing Changed event subscriptions.
        /// Provides thread-safe registration, unregistration, and invocation
        /// of event handlers with proper lifetime management.
        /// </summary>
        winrt::event<FileWatcherChangedHandler> m_changed;
    };
}

namespace winrt::ToolkitCore::factory_implementation
{
    /// <summary>
    /// Factory implementation for creating FileWatcherService instances.
    /// This is auto-generated code that provides the activation factory
    /// required by the Windows Runtime component system.
    /// </summary>
    struct FileWatcherService : FileWatcherServiceT<FileWatcherService, implementation::FileWatcherService> {};
}
