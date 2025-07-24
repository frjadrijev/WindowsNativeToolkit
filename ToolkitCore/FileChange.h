#pragma once
#include "FileChange.g.h"

namespace winrt::ToolkitCore::implementation
{
    struct FileChange : FileChangeT<FileChange>      // generated CRTP helper
    {
        // default ctor – nothing to do
        FileChange() = default;
        // NEW: parameterised ctor that matches the IDL
        FileChange(hstring const& path, ChangeType type, uint64_t timestamp) : 
            m_path{ path }, m_type{ type }, m_timestamp{ timestamp } {}

        /* -------- property overrides (auto-generated versions are fine;
           keep overrides only if you need validation) ------------------- */

        hstring Path()  const { return m_path; }
        void    Path(hstring const& value)
        {
            if (value.empty()) throw hresult_invalid_argument();
            m_path = value;
        }

        ChangeType Type() const { return m_type; }
        void       Type(ChangeType value) { m_type = value; }

        uint64_t Timestamp() const { return m_timestamp; }
        void     Timestamp(uint64_t value) { m_timestamp = value; }

    private:
        hstring     m_path;
        ChangeType  m_type{ ChangeType::Added };
        uint64_t    m_timestamp{ 0 };
    };
}

namespace winrt::ToolkitCore::factory_implementation
{
    struct FileChange : FileChangeT<FileChange, implementation::FileChange> {
    };
}
