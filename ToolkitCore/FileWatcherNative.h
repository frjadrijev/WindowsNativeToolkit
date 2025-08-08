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
        /// Starts file system monitoring for the specified folder.
        /// Creates a background thread that uses Win32 change notifications
        /// to detect file system modifications and invoke the provided callback.
        /// </summary>
        /// <param name="folder">Directory path to monitor (WinRT hstring)</param>
        /// <param name="changeCallback">Function to call when changes are detected</param>
        /// <remarks>
        /// Implementation details:
        /// 
        /// Win32 API Usage:
        /// - Uses FindFirstChangeNotification for basic change detection
        /// - Monitors FILE_NOTIFY_CHANGE_FILE_NAME and FILE_NOTIFY_CHANGE_SIZE
        /// - Enables recursive monitoring (TRUE parameter) for subdirectories
        /// 
        /// Threading Strategy:
        /// - Creates detached background thread for monitoring loop
        /// - Thread polls with 250ms timeout to allow responsive shutdown
        /// - Uses move semantics to transfer handle ownership to thread
        /// - Copies folder path for thread-local access
        /// 
        /// Limitations:
        /// - Uses simplified change detection (whole folder events)
        /// - For production, consider upgrading to ReadDirectoryChangesW
        /// - Current implementation creates synthetic "Modified" events
        /// - Timestamp uses system_clock for cross-platform compatibility
        /// 
        /// Error Handling:
        /// - Validates input parameters before proceeding
        /// - Checks for duplicate start requests using atomic exchange
        /// - Throws WinRT exceptions for Win32 API failures
        /// - Uses RAII for automatic resource cleanup
        /// </remarks>
        void Start(winrt::hstring const& folder, ChangeCallback changeCallback);  

        /// <summary>
        /// Stops file system monitoring and performs cleanup.
        /// Uses atomic signaling to safely shut down the background thread
        /// and releases all Win32 resources.
        /// </summary>
        /// <remarks>
        /// Shutdown sequence:
        /// 1. Set atomic _running flag to false (signals thread to exit)
        /// 2. Close Win32 change notification handle (may wake waiting thread)
        /// 3. Reset handle to null state for clean reinitialization
        /// 
        /// Thread safety considerations:
        /// - Uses atomic operations to coordinate with background thread
        /// - Handle operations are safe because background thread has its own copy
        /// - Method can be called multiple times safely (idempotent)
        /// - No explicit thread joining required due to timeout-based polling
        /// 
        /// Performance notes:
        /// - Shutdown typically completes within 250ms (polling timeout)
        /// - Background thread will exit at next timeout check
        /// - Win32 handle closure may immediately wake the waiting thread
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