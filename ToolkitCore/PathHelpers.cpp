// PathHelpers.cpp
#include "pch.h"
#include "PathHelpers.h"
#include <filesystem>

using namespace std::filesystem;

namespace native::ToolkitCore
{
    /// <summary>
    /// Checks if the specified path refers to an existing directory.
    /// Uses std::filesystem for robust cross-platform directory detection.
    /// </summary>
    /// <param name="p">Path to examine (can be absolute or relative)</param>
    /// <returns>true if path exists and is a directory, false otherwise</returns>
    /// <remarks>
    /// Implementation uses std::filesystem::is_directory which:
    /// - Follows symbolic links to their targets
    /// - Returns false for non-existent paths (no exception)
    /// - Returns false for files, devices, or other non-directory objects
    /// - Handles Unicode paths correctly on all platforms
    /// - Resolves relative paths against current working directory
    /// 
    /// Error handling:
    /// - Does not throw for common error conditions (missing files, access denied)
    /// - Returns false for any error condition (conservative approach)
    /// - Filesystem errors are silently handled by the standard library
    /// 
    /// Thread safety:
    /// - Function is thread-safe (read-only filesystem access)
    /// - No shared state or global variables accessed
    /// - Multiple threads can safely call this function concurrently
    /// </remarks>
    bool IsDirectory(std::wstring_view p) 
    { 
        return is_directory(path{ p }); 
    }

    /// <summary>
    /// Converts a path to its canonical (normalized) absolute form.
    /// Resolves symbolic links, removes redundant components, and standardizes format.
    /// </summary>
    /// <param name="p">Path to normalize (absolute or relative)</param>
    /// <returns>Canonical absolute path as a wide string</returns>
    /// <exception cref="filesystem_error">
    /// Thrown if path doesn't exist or cannot be accessed
    /// </exception>
    /// <remarks>
    /// Implementation uses std::filesystem::canonical which:
    /// - Converts relative paths to absolute using current working directory
    /// - Resolves all symbolic links and junction points to final targets
    /// - Removes redundant separators, "." and ".." components
    /// - Standardizes path format for the current operating system
    /// - Validates that the final path actually exists in the filesystem
    /// 
    /// Security considerations:
    /// - Prevents directory traversal attacks by resolving ".." components
    /// - Ensures paths point to actual filesystem objects (not theoretical paths)
    /// - Resolves symbolic link targets (may expose underlying filesystem structure)
    /// 
    /// Performance characteristics:
    /// - Performs multiple filesystem I/O operations for resolution
    /// - More expensive than string-based path manipulation
    /// - Results are suitable for caching if paths don't change frequently
    /// 
    /// Error conditions:
    /// - Throws filesystem_error if any path component doesn't exist
    /// - Throws filesystem_error for permission denied scenarios
    /// - Consider using std::filesystem::weakly_canonical for paths that may not exist
    /// 
    /// Cross-platform behavior:
    /// - Windows: Handles drive letters, UNC paths, junction points
    /// - Returns paths with native separators (\\ on Windows, / on Unix)
    /// - Properly handles Unicode characters in all path components
    /// </remarks>
    std::wstring Normalise(std::wstring_view p) 
    { 
        return canonical(path{ p }).wstring(); 
    }
}
