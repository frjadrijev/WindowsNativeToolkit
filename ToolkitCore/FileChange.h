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
    /// Runtime class characteristics:
    /// This runtime class serves as the primary data container for file system
    /// change notifications, providing a standardized interface for consuming
    /// file monitoring events across different programming languages and frameworks.
    /// 
    /// Design principles:
    /// - Immutable once created (recommend treating as read-only after construction)
    /// - Lightweight and efficient for high-frequency events
    /// - Cross-language compatible through Windows Runtime projection
    /// - Self-contained with all necessary information for processing
    /// 
    /// The class supports both default construction and parameterized construction
    /// to facilitate different usage scenarios:
    /// - Default construction for creating empty change objects
    /// - Parameterized construction for direct initialization with change data
    /// 
    /// Usage patterns:
    /// - Event payloads in file monitoring callbacks
    /// - Data binding sources for UI display
    /// - Logging and audit trail records
    /// - Change analysis and processing pipelines
    /// 
    /// Thread Safety:
    /// This class is not inherently thread-safe. External synchronization is
    /// required if instances will be accessed from multiple threads.
    /// - Safe to access from multiple threads once constructed
    /// - Property reads are atomic through WinRT infrastructure
    /// - Recommend treating instances as immutable after creation
    /// 
    /// Performance characteristics:
    /// - Minimal memory footprint for efficient event queuing
    /// - Fast construction for high-frequency monitoring scenarios
    /// - Efficient marshaling across COM boundaries
    /// - Suitable for real-time processing requirements
    /// 
    /// Cross-language projection:
    /// - C++: winrt::ToolkitCore::FileChange
    /// - C#: ToolkitCore.FileChange  
    /// - JavaScript: ToolkitCore.FileChange (if projected)
    /// - VB.NET: ToolkitCore.FileChange
    /// </remarks>
    struct FileChange : FileChangeT<FileChange>      // generated CRTP helper
    {
        /// <summary>
        /// Default constructor creating an empty FileChange instance.
        /// Initializes all properties to default values for later assignment.
        /// </summary>
        /// <remarks>
        /// Default values:
        /// - Path: empty string
        /// - Type: ChangeType.Added  
        /// - Timestamp: 0 (represents uninitialized/invalid time)
        /// 
        /// Usage scenarios:
        /// - Creating instances for later property assignment
        /// - Placeholder objects in collections or data structures
        /// - Default values in optional parameters
        /// - Testing and mocking scenarios
        /// 
        /// This constructor is required for WinRT activation factory support
        /// and enables creation through generic factory patterns.
        /// </remarks>
        FileChange() = default;
        
        /// <summary>
        /// Parameterized constructor creating a fully-initialized FileChange instance.
        /// Enables direct creation with all properties set to specific values.
        /// This constructor matches the IDL definition and allows direct initialization.
        /// </summary>
        /// <param name="path">
        /// The full path to the file or directory that changed. Should be an absolute path
        /// for unambiguous identification. Empty string is valid for system-wide events.
        /// </param>
        /// <param name="type">
        /// The type of change that occurred (Added, Modified, or Removed).
        /// Determines how the change should be processed and displayed.
        /// </param>
        /// <param name="timestamp">
        /// Timestamp when the change occurred, typically milliseconds since Unix epoch.
        /// Value of 0 indicates timestamp is not available or not applicable.
        /// </param>
        /// <remarks>
        /// This constructor is primarily used by the file watching system to create
        /// change notifications with all relevant information populated at construction time.
        /// 
        /// This constructor is the preferred method for creating FileChange instances
        /// in monitoring scenarios where all information is available at creation time.
        /// 
        /// Parameter validation:
        /// - Path validation is performed in property setter if needed
        /// - Type must be valid ChangeType enumeration value
        /// - Timestamp should be consistent format (recommend Unix epoch milliseconds)
        /// 
        /// Usage patterns:
        /// - File monitoring callback event creation
        /// - Converting from native Win32 file notifications
        /// - Test data generation with known values
        /// - API responses containing change information
        /// 
        /// Performance benefits:
        /// - Single construction call sets all properties
        /// - Avoids multiple property change notifications
        /// - Efficient for high-frequency event generation
        /// - Reduces total allocation overhead
        /// </remarks>
        FileChange(hstring const& path, ChangeType type, uint64_t timestamp) : 
            m_path{ path }, m_type{ type }, m_timestamp{ timestamp } {}

        /* -------- Properties ------------------- */

        /// <summary>
        /// Gets the full path to the file or directory that changed.
        /// Provides the location information necessary to identify the changed item.
        /// </summary>
        /// <returns>
        /// A Windows Runtime string containing the full path to the changed item.
        /// Should be an absolute path for unambiguous identification.
        /// Empty string indicates path is not available or not applicable.
        /// </returns>
        /// <remarks>
        /// Path format considerations:
        /// - Should use native path separators for the target platform
        /// - Recommend absolute paths to avoid ambiguity
        /// - May include UNC paths for network resources
        /// - Consider path length limitations on target platforms
        /// 
        /// Security considerations:
        /// - Paths may contain sensitive information
        /// - Consider sanitization for logging or display
        /// - Validate path format to prevent injection attacks
        /// - Be aware of symbolic link resolution behavior
        /// 
        /// Usage patterns:
        /// - File operation targeting
        /// - UI display and user notification
        /// - Logging and audit trail generation
        /// - Change filtering and pattern matching
        /// 
        /// Performance notes:
        /// - String operations may have allocation overhead
        /// - Consider caching frequently accessed paths
        /// - Path comparison should use appropriate methods for platform
        /// </remarks>
        hstring Path() const;

        /// <summary>
        /// Sets the full path to the file or directory that changed.
        /// Provides the location information necessary to identify the changed item.
        /// </summary>
        /// <param name="value">
        /// The full path to the changed item. Cannot be empty.
        /// String containing the full path to the changed file or directory.
        /// Should be an absolute path for unambiguous identification.
        /// Empty string indicates path is not available or not applicable.
        /// </param>
        /// <exception cref="hresult_invalid_argument">Thrown if the path is empty</exception>
        /// <remarks>
        /// The path should be a fully qualified path to ensure unambiguous identification
        /// of the changed file or directory. Relative paths may lead to confusion in
        /// multi-threaded scenarios or when the working directory changes.
        /// 
        /// Path format considerations:
        /// - Should use native path separators for the target platform
        /// - Recommend absolute paths to avoid ambiguity
        /// - May include UNC paths for network resources
        /// - Consider path length limitations on target platforms
        /// 
        /// Security considerations:
        /// - Paths may contain sensitive information
        /// - Consider sanitization for logging or display
        /// - Validate path format to prevent injection attacks
        /// - Be aware of symbolic link resolution behavior
        /// 
        /// Usage patterns:
        /// - File operation targeting
        /// - UI display and user notification
        /// - Logging and audit trail generation
        /// - Change filtering and pattern matching
        /// 
        /// Performance notes:
        /// - String operations may have allocation overhead
        /// - Consider caching frequently accessed paths
        /// - Path comparison should use appropriate methods for platform
        /// </remarks>
        void Path(hstring const& value);

        /// <summary>
        /// Gets the type of change that occurred.
        /// Categorizes the file system operation for processing and display purposes.
        /// </summary>
        /// <returns>
        /// A ChangeType enum value indicating whether the item was added, modified, or removed.
        /// ChangeType enumeration value indicating whether the item was added,
        /// removed, or modified. Determines appropriate processing and user feedback.
        /// </returns>
        /// <remarks>
        /// Processing guidelines by type:
        /// - Added: May trigger indexing, scanning, or welcome processes
        /// - Removed: May trigger cleanup, archiving, or notification processes  
        /// - Modified: May trigger re-processing, validation, or update processes
        /// 
        /// UI presentation:
        /// - Different icons or colors for different change types
        /// - Filtering options to show/hide specific change types
        /// - Sorting and grouping by change type
        /// - Summary statistics by change type
        /// 
        /// Business logic integration:
        /// - Workflow triggers based on change type
        /// - Security monitoring for unexpected removals
        /// - Performance monitoring for excessive modifications
        /// - Compliance reporting categorized by change type
        /// </remarks>
        ChangeType Type() const;

        /// <summary>
        /// Sets the type of change that occurred.
        /// Categorizes the file system operation for processing and display purposes.
        /// </summary>
        /// <param name="value">
        /// The type of change (Added, Modified, or Removed).
        /// ChangeType enumeration value indicating whether the item was added,
        /// removed, or modified. Determines appropriate processing and user feedback.
        /// </param>
        /// <remarks>
        /// Processing guidelines by type:
        /// - Added: May trigger indexing, scanning, or welcome processes
        /// - Removed: May trigger cleanup, archiving, or notification processes  
        /// - Modified: May trigger re-processing, validation, or update processes
        /// 
        /// UI presentation:
        /// - Different icons or colors for different change types
        /// - Filtering options to show/hide specific change types
        /// - Sorting and grouping by change type
        /// - Summary statistics by change type
        /// 
        /// Business logic integration:
        /// - Workflow triggers based on change type
        /// - Security monitoring for unexpected removals
        /// - Performance monitoring for excessive modifications
        /// - Compliance reporting categorized by change type
        /// </remarks>
        void Type(ChangeType value);

        /// <summary>
        /// Gets the timestamp when the change occurred.
        /// Provides temporal information for sequencing and analysis purposes.
        /// </summary>
        /// <returns>
        /// A 64-bit unsigned integer representing the timestamp, typically 
        /// milliseconds since Unix epoch (January 1, 1970).
        /// 64-bit unsigned integer representing the timestamp, typically milliseconds
        /// since Unix epoch (January 1, 1970 UTC). Value of 0 indicates timestamp
        /// is not available or not applicable.
        /// </returns>
        /// <remarks>
        /// The timestamp format is consistent with JavaScript Date.now() and
        /// .NET DateTime.Ticks / 10000, making it easy to convert for display
        /// or comparison purposes in various runtime environments.
        /// 
        /// Timestamp format:
        /// - Recommended: milliseconds since Unix epoch for cross-platform compatibility
        /// - Compatible with JavaScript Date.now() and .NET DateTime conversions
        /// - Provides sufficient precision for most monitoring scenarios
        /// - Consider time zone implications for distributed systems
        /// 
        /// Usage scenarios:
        /// - Change sequencing and ordering
        /// - Time-based filtering and analysis
        /// - Performance monitoring and metrics
        /// - Audit trail and compliance reporting
        /// - Change frequency analysis
        /// 
        /// Conversion examples:
        /// - C#: DateTimeOffset.FromUnixTimeMilliseconds(timestamp)
        /// - JavaScript: new Date(timestamp)
        /// - C++: std::chrono::milliseconds(timestamp)
        /// 
        /// Precision considerations:
        /// - File system timestamp precision varies by platform
        /// - NTFS: 100-nanosecond precision
        /// - ext4: nanosecond precision  
        /// - FAT32: 2-second precision
        /// - Consider precision requirements for your use case
        /// </remarks>
        uint64_t Timestamp() const;
        
        /// <summary>
        /// Sets the timestamp when the change occurred.
        /// Provides temporal information for sequencing and analysis purposes.
        /// </summary>
        /// <param name="value">
        /// Timestamp value, typically milliseconds since Unix epoch.
        /// A value of 0 indicates an unspecified or invalid timestamp.
        /// 64-bit unsigned integer representing the timestamp, typically milliseconds
        /// since Unix epoch (January 1, 1970 UTC). Value of 0 indicates timestamp
        /// is not available or not applicable.
        /// </param>
        /// <remarks>
        /// Timestamp format:
        /// - Recommended: milliseconds since Unix epoch for cross-platform compatibility
        /// - Compatible with JavaScript Date.now() and .NET DateTime conversions
        /// - Provides sufficient precision for most monitoring scenarios
        /// - Consider time zone implications for distributed systems
        /// 
        /// Usage scenarios:
        /// - Change sequencing and ordering
        /// - Time-based filtering and analysis
        /// - Performance monitoring and metrics
        /// - Audit trail and compliance reporting
        /// - Change frequency analysis
        /// 
        /// Conversion examples:
        /// - C#: DateTimeOffset.FromUnixTimeMilliseconds(timestamp)
        /// - JavaScript: new Date(timestamp)
        /// - C++: std::chrono::milliseconds(timestamp)
        /// 
        /// Precision considerations:
        /// - File system timestamp precision varies by platform
        /// - NTFS: 100-nanosecond precision
        /// - ext4: nanosecond precision  
        /// - FAT32: 2-second precision
        /// - Consider precision requirements for your use case
        /// </remarks>
        void Timestamp(uint64_t value);

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
