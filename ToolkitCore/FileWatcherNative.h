#pragma once  
#include <functional>  
#include <atomic>  
#include <string>  
#include <winrt/base.h>      // smart-ptr helpers  
#include <wil/resource.h>    // Include WIL resource header for unique_handle  
#include <FileChange.h>
#include <FileChange.g.h>

namespace native::ToolkitCore
{  
    /// <summary>
    /// Type alias for callback functions that handle file change notifications.
    /// Callbacks receive a FileChange object containing details about the detected change.
    /// </summary>
    /// <remarks>
    /// Callback functions should:
    /// - Complete quickly to avoid blocking the monitoring thread
    /// - Be thread-safe as they're called from background threads
    /// - Handle exceptions gracefully to prevent crashing the monitor
    /// - Avoid long-running operations that could cause event queue backup
    /// </remarks>
    using ChangeCallback = std::function<void(const winrt::ToolkitCore::FileChange&)>;

    /// <summary>
    /// Native C++ implementation of file system monitoring using Win32 APIs.
    /// Provides low-level file change detection with efficient resource management
    /// and thread-safe operation for integration with WinRT components.
    /// </summary>
    /// <remarks>
    /// This class encapsulates the complexity of Win32 file monitoring APIs
    /// (FindFirstChangeNotification, ReadDirectoryChangesW) and provides a
    /// clean, modern C++ interface for higher-level components.
    /// 
    /// Key features:
    /// - Asynchronous monitoring using background threads
    /// - Automatic resource cleanup using RAII principles
    /// - Thread-safe start/stop operations using atomic flags
    /// - Efficient notification handling with minimal overhead
    /// - Integration with Windows Implementation Library (WIL) for resource safety
    /// 
    /// Threading model:
    /// - Start() creates a detached background thread for monitoring
    /// - Background thread polls for changes and invokes callbacks
    /// - Stop() safely shuts down monitoring using atomic signaling
    /// - All public methods are thread-safe for concurrent access
    /// 
    /// Resource management:
    /// - Uses WIL unique_handle for automatic Win32 handle cleanup
    /// - RAII ensures proper cleanup even in exception scenarios
    /// - Atomic flags prevent race conditions during start/stop
    /// </remarks>
    struct FileWatcherNative
    {  
        /// <summary>
        /// Begins monitoring the specified folder for file system changes.
        /// Creates a background thread that continuously monitors for changes
        /// and invokes the provided callback when changes are detected.
        /// </summary>
        /// <param name="folder">
        /// Full path to the directory to monitor. Must exist and be accessible.
        /// The path should be in native Windows format (backslashes).
        /// </param>
        /// <param name="changeCallback">
        /// Function to call when changes are detected. The callback receives
        /// a FileChange object with details about the specific change.
        /// Must remain valid until Stop() is called.
        /// </param>
        /// <exception cref="winrt::hresult_invalid_argument">
        /// Thrown if folder parameter is empty.
        /// </exception>
        /// <exception cref="winrt::hresult_error">
        /// Thrown if the folder doesn't exist, access is denied, or Win32
        /// APIs fail to initialize the file monitoring handle.
        /// </exception>
        /// <remarks>
        /// Implementation uses FindFirstChangeNotification for basic monitoring.
        /// For production use, consider upgrading to ReadDirectoryChangesW for
        /// more detailed change information including specific file names and
        /// operation types.
        /// 
        /// The monitoring includes:
        /// - FILE_NOTIFY_CHANGE_FILE_NAME: File creation, deletion, rename
        /// - FILE_NOTIFY_CHANGE_SIZE: File size changes
        /// - Recursive monitoring of all subdirectories
        /// 
        /// Thread safety:
        /// This method uses atomic operations to prevent race conditions.
        /// If already monitoring, subsequent calls are ignored safely.
        /// </remarks>
        void Start(winrt::hstring const& folder, ChangeCallback changeCallback);  

        /// <summary>
        /// Stops monitoring and releases all associated resources.
        /// Safely shuts down the background monitoring thread and closes Win32 handles.
        /// </summary>
        /// <remarks>
        /// Shutdown process:
        /// 1. Sets atomic flag to signal monitoring thread to exit
        /// 2. Closes the Win32 change notification handle
        /// 3. Waits for background thread to complete (via detached thread cleanup)
        /// 4. Resets all member variables to initial state
        /// 
        /// This method is safe to call multiple times and from multiple threads.
        /// It will gracefully handle cases where monitoring is not active.
        /// 
        /// The method uses a timeout-based approach in the monitoring loop,
        /// so shutdown typically completes within 250ms (the polling interval).
        /// </remarks>
        void Stop();  

    private:  
        /// <summary>
        /// Win32 handle for file change notifications.
        /// Managed using WIL unique_handle for automatic cleanup and exception safety.
        /// </summary>
        wil::unique_handle _handle;  

        /// <summary>
        /// Callback function to invoke when file changes are detected.
        /// Stored as std::function to support lambda captures and various callable types.
        /// </summary>
        ChangeCallback _callback;  

        /// <summary>
        /// Atomic flag indicating whether monitoring is currently active.
        /// Used for thread-safe coordination between start/stop operations
        /// and the background monitoring thread.
        /// </summary>
        std::atomic_bool _running{ false };  
    };  
}