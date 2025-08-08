#include "pch.h"                     // PCH  
#include "FileWatcherNative.h"       // own header
// Win32 → WinRT helpers
#include <chrono>
#include <pathcch.h>                 // PathCchCombine
#pragma comment(lib, "Pathcch.lib")

using namespace winrt;
using namespace std::chrono;

namespace native::ToolkitCore
{
    // ────────────────────────────── Start ──────────────────────────────
    void FileWatcherNative::Start(hstring const& folder, ChangeCallback  changeCallback)
    {
        // Validate input parameters
        if (folder.empty())
            winrt::throw_hresult(E_INVALIDARG);

        // Prevent concurrent start requests using atomic exchange
        // If already running, silently return (idempotent operation)
        if (_running.exchange(true))
            return;                              // already running

        //
        // Initialize Win32 file change notification handle
        // Uses FindFirstChangeNotification for basic monitoring
        //
        _handle = wil::unique_handle{
            FindFirstChangeNotificationW(
                folder.c_str(),                  // Directory to monitor
                TRUE,                           // Monitor subdirectories recursively
                FILE_NOTIFY_CHANGE_FILE_NAME |  // File create/delete/rename
                FILE_NOTIFY_CHANGE_SIZE         // File size changes
            )
        };

        // Check for Win32 API failure and convert to WinRT exception
        if (_handle.get() == INVALID_HANDLE_VALUE)
            winrt::throw_last_error();


        // Store callback for use in background thread
        _callback = std::move(changeCallback);

        //
        // Create detached background thread for monitoring loop: FileWatcherNative lifetime
        // is managed by the WinRT façade.
        //
        // Thread capture strategy:
        // - Move handle ownership to thread (h = _handle.release())
        // - Copy folder path for thread-local access (dir = std::wstring{folder})
        // - Capture 'this' pointer for accessing member variables
        //
        // Detached thread is appropriate here because:
        // - FileWatcherNative lifetime is managed by WinRT facade
        // - Thread will exit cleanly when _running flag is cleared
        // - No need to join thread as cleanup is handled by atomic signaling
        //
        std::thread(
            [
                this,
                h = wil::unique_handle
                {
                    _handle.release()
                },
                dir = std::wstring
                {
                    folder
                }
            ]()
            {
                // Main monitoring loop - continues until _running flag is cleared
                while (_running.load())
                {
                    // Wait for change notification with timeout for responsive shutdown
                    if (WaitForSingleObject(h.get(), 250) == WAIT_OBJECT_0)
                    {
                        //
                         // ► File system change detected - create notification event
                         //
                         // NOTE: This is a simplified implementation for demonstration.
                         // Production code should use ReadDirectoryChangesW to get:
                         // - Specific file names that changed
                         // - Exact operation types (FILE_ACTION_ADDED, etc.)
                         // - Multiple changes in a single notification batch
                         //
                         // Current implementation creates a synthetic event for the
                         // entire monitored folder with a wildcard path.
                         //

                        // Generate timestamp using high-resolution system clock
                        auto ts = duration_cast<milliseconds>(
                            system_clock::now().time_since_epoch()
                        ).count();

                        // Build full path with wildcard for folder monitoring
                        // Uses PathCchCombine for safe path manipulation
                        wchar_t pathBuf[MAX_PATH]{};
                        PathCchCombine(pathBuf, std::size(pathBuf), dir.c_str(), L"*");

                        // Create WinRT FileChange object with synthetic data
                        winrt::ToolkitCore::FileChange change{
                            winrt::hstring(pathBuf),                    // Path with wildcard
                            winrt::ToolkitCore::ChangeType::Modified,   // Synthetic change type
                            static_cast<uint64_t>(ts)                   // Current timestamp
                        };

                        // Invoke the registered callback with change details
                        // Callback is responsible for thread-safe handling
                        _callback(change);

                        // Re-arm the Win32 change notification for next event
                        // This is required for FindFirstChangeNotification API
                        FindNextChangeNotification(h.get());
                    }
                    // If timeout occurred (no changes), loop continues for shutdown check
                }
                // Thread exits when _running becomes false
                // Automatic cleanup of local variables (handle, strings)
            }).detach();
    }

    // ────────────────────────────── Stop ───────────────────────────────
    void FileWatcherNative::Stop()
    {
        // Signal background thread to stop monitoring
        // Atomic store ensures visibility across threads immediately
        _running = false;

        // Close Win32 change notification handle if valid
       // This may wake the background thread immediately if it's waiting
        if (_handle)
        {
            ::FindCloseChangeNotification(_handle.get());
            _handle.reset();  // Reset to null for clean state
        }

        // Note: No explicit thread joining required
        // Background thread will exit at next polling check (≤250ms)
        // Detached thread cleanup is handled automatically by runtime
    }
}
