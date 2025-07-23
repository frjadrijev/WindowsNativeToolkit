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
    using ChangeCallback = std::function<void(const winrt::ToolkitCore::FileChange&)>;
  
    struct FileWatcherNative
    {  
        void Start(winrt::hstring const& folder, ChangeCallback changeCalback);  
        void Stop();  

    private:  
        wil::unique_handle _handle;  
        ChangeCallback     _callback;  
        std::atomic_bool   _running{ false };  
    };  
}