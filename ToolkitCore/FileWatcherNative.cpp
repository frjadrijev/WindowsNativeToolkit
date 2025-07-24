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
    void FileWatcherNative::Start(hstring const& folder,
        ChangeCallback  changeCallback)
    {
        if (folder.empty())
            winrt::throw_hresult(E_INVALIDARG);

        if (_running.exchange(true))
            return;                              // already running

        //
        // Win32 watch handle
        //
        _handle = wil::unique_handle{ FindFirstChangeNotificationW(folder.c_str(), TRUE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE) };

        if (_handle.get() == INVALID_HANDLE_VALUE)
            winrt::throw_last_error();

        _callback = std::move(changeCallback);

        //
        // Worker thread – detach is fine: FileWatcherNative lifetime
        // is managed by the WinRT façade.
        //
        std::thread([this, h = wil::unique_handle{ _handle.release() }, dir = std::wstring{ folder }]()
            {
                while (_running.load())
                {
                    if (WaitForSingleObject(h.get(), 250) == WAIT_OBJECT_0)
                    {
                        //
                        // ► Translate the Win32 notification into a WinRT
                        //   ToolkitCore::FileChange object
                        //
                        // For a real watcher you would call
                        //   ReadDirectoryChangesW
                        // to obtain the FILE_ACTION_* and file name.  Here we
                        // fabricate a “modified” event for the whole folder.
                        //

                        auto ts = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

                        // Build full path (dir\* wildcard)
                        wchar_t pathBuf[MAX_PATH]{};
                        PathCchCombine(pathBuf, std::size(pathBuf), dir.c_str(), L"*");

                        winrt::ToolkitCore::FileChange change{ winrt::hstring(pathBuf), winrt::ToolkitCore::ChangeType::Modified, static_cast<uint64_t>(ts) };
                        _callback(change);

                        // re-arm the Win32 watch
                        FindNextChangeNotification(h.get());
                    }
                }
            }).detach();
    }

    // ────────────────────────────── Stop ───────────────────────────────
    void FileWatcherNative::Stop()
    {
        _running = false;

        if (_handle)
        {
            ::FindCloseChangeNotification(_handle.get());
            _handle.reset();
        }
    }
}
