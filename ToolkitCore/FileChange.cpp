#include "pch.h"
#include "FileChange.h"
#if __has_include("FileChange.g.cpp")
#include "FileChange.g.cpp"
#endif

namespace winrt::ToolkitCore::implementation {

    hstring FileChange::Path() const 
    {
        return m_path;
    }

    void FileChange::Path(hstring const& value) 
    {
        // Validation: reject empty paths to maintain data integrity
        if (value.empty()) 
            throw hresult_invalid_argument();
        m_path = value;
    }

    ChangeType FileChange::Type() const 
    { 
        return m_type; 
    }

    void FileChange::Type(ChangeType value) 
    { 
        m_type = value; 
    } 

    uint64_t FileChange::Timestamp() const 
    { 
        return m_timestamp; 
    }

    void FileChange::Timestamp(uint64_t value) 
    { 
        m_timestamp = value; 
    }
}