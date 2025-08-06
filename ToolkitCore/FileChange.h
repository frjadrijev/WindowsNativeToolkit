#pragma once
#include "FileChange.g.h"

namespace winrt::ToolkitCore::implementation
{
    /// <summary>
    /// Implementation of the FileChange Windows Runtime component.
    /// Represents a single file system change event with details about
    /// the file path, change type, and timestamp when the change occurred.
    /// </summary>
    /// <remarks>
    /// This class is the native C++ implementation behind the WinRT FileChange
    /// component. It provides a lightweight container for file change information
    /// that can be efficiently passed between native code and managed/WinRT code.
    /// 
    /// The class supports both default construction and parameterized construction
    /// to facilitate different usage scenarios:
    /// - Default construction for creating empty change objects
    /// - Parameterized construction for direct initialization with change data
    /// 
    /// Thread Safety:
    /// This class is not inherently thread-safe. External synchronization is
    /// required if instances will be accessed from multiple threads.
    /// </remarks>
    struct FileChange : FileChangeT<FileChange>      // generated CRTP helper
    {
        /// <summary>
        /// Default constructor that creates an empty FileChange instance.
        /// The instance will have an empty path, Added change type, and timestamp of 0.
        /// </summary>
        FileChange() = default;
        
        /// <summary>
        /// Parameterized constructor that creates a FileChange instance with specified values.
        /// This constructor matches the IDL definition and allows direct initialization.
        /// </summary>
        /// <param name="path">The full path to the file or directory that changed</param>
        /// <param name="type">The type of change that occurred (Added, Modified, or Removed)</param>
        /// <param name="timestamp">Timestamp when the change occurred, typically in milliseconds since epoch</param>
        /// <remarks>
        /// This constructor is primarily used by the file watching system to create
        /// change notifications with all relevant information populated at construction time.
        /// </remarks>
        FileChange(hstring const& path, ChangeType type, uint64_t timestamp) : 
            m_path{ path }, m_type{ type }, m_timestamp{ timestamp } {}

        /* -------- Property implementations with validation ------------------- */

        /// <summary>
        /// Gets the file path associated with this change event.
        /// </summary>
        /// <returns>A Windows Runtime string containing the full path to the changed item</returns>
        hstring Path() const { return m_path; }
        
        /// <summary>
        /// Sets the file path associated with this change event.
        /// </summary>
        /// <param name="value">The full path to the changed item. Cannot be empty.</param>
        /// <exception cref="hresult_invalid_argument">Thrown if the path is empty</exception>
        /// <remarks>
        /// The path should be a fully qualified path to ensure unambiguous identification
        /// of the changed file or directory. Relative paths may lead to confusion in
        /// multi-threaded scenarios or when the working directory changes.
        /// </remarks>
        void Path(hstring const& value)
        {
            if (value.empty()) throw hresult_invalid_argument();
            m_path = value;
        }

        /// <summary>
        /// Gets the type of change that occurred.
        /// </summary>
        /// <returns>A ChangeType enum value indicating whether the item was added, modified, or removed</returns>
        ChangeType Type() const { return m_type; }
        
        /// <summary>
        /// Sets the type of change that occurred.
        /// </summary>
        /// <param name="value">The type of change (Added, Modified, or Removed)</param>
        void Type(ChangeType value) { m_type = value; }

        /// <summary>
        /// Gets the timestamp when the change occurred.
        /// </summary>
        /// <returns>
        /// A 64-bit unsigned integer representing the timestamp, typically 
        /// milliseconds since Unix epoch (January 1, 1970)
        /// </returns>
        /// <remarks>
        /// The timestamp format is consistent with JavaScript Date.now() and
        /// .NET DateTime.Ticks / 10000, making it easy to convert for display
        /// or comparison purposes in various runtime environments.
        /// </remarks>
        uint64_t Timestamp() const { return m_timestamp; }
        
        /// <summary>
        /// Sets the timestamp when the change occurred.
        /// </summary>
        /// <param name="value">
        /// Timestamp value, typically milliseconds since Unix epoch.
        /// A value of 0 indicates an unspecified or invalid timestamp.
        /// </param>
        void Timestamp(uint64_t value) { m_timestamp = value; }

    private:
        /// <summary>Full path to the file or directory that changed</summary>
        hstring m_path;
        
        /// <summary>Type of change that occurred (default: Added)</summary>
        ChangeType m_type{ ChangeType::Added };
        
        /// <summary>Timestamp when change occurred (default: 0 = unspecified)</summary>
        uint64_t m_timestamp{ 0 };
    };
}

namespace winrt::ToolkitCore::factory_implementation
{
    /// <summary>
    /// Factory implementation for creating FileChange instances.
    /// This is generated code that provides the factory pattern implementation
    /// required by the Windows Runtime component infrastructure.
    /// </summary>
    struct FileChange : FileChangeT<FileChange, implementation::FileChange> {
    };
}
