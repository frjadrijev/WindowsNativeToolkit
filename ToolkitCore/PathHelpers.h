#pragma once
#include <string>
#include <string_view>

namespace native::ToolkitCore
{
    /// <summary>
    /// Determines whether the specified path refers to an existing directory.
    /// Uses std::filesystem for robust cross-platform directory detection.
    /// </summary>
    /// <param name="path">Path to check. Can be absolute or relative.</param>
    /// <returns>true if the path exists and is a directory; false otherwise</returns>
    /// <remarks>
    /// This function uses the C++17 std::filesystem library for reliable
    /// cross-platform path validation. It properly handles:
    /// - Network paths (UNC format)
    /// - Long paths (>260 characters)
    /// - Unicode characters in paths
    /// - Various path separators (\ and /)
    /// - Relative paths resolved against current working directory
    /// 
    /// Implementation details:
    /// - Uses std::filesystem::is_directory which follows symbolic links to their targets
    /// - Returns false for non-existent paths (no exception thrown)
    /// - Returns false for files, devices, or other non-directory objects
    /// - Handles Unicode paths correctly on all platforms
    /// 
    /// Performance considerations:
    /// - Performs actual filesystem access (I/O operation)
    /// - May be slow for network drives or removable media
    /// - Consider caching results for frequently checked paths
    /// 
    /// Error handling:
    /// - Does not throw for common error conditions (missing files, access denied)
    /// - Returns false for any error condition (conservative approach)
    /// - Filesystem errors are silently handled by the standard library
    /// - Uses noexcept filesystem operations internally
    /// 
    /// Thread safety:
    /// - Function is thread-safe (read-only filesystem access)
    /// - No shared state or global variables accessed
    /// - Multiple threads can safely call this function concurrently
    /// </remarks>
    [[nodiscard]] bool IsDirectory(std::wstring_view path);

    /// <summary>
    /// Normalizes a file system path to its canonical absolute form.
    /// Resolves relative path components, symbolic links, and ensures
    /// consistent path formatting for reliable path comparisons.
    /// </summary>
    /// <param name="path">Path to normalize. Can be absolute or relative.</param>
    /// <returns>
    /// Canonical absolute path with resolved links and normalized separators.
    /// </returns>
    /// <exception cref="std::filesystem::filesystem_error">
    /// Thrown if the path doesn't exist or cannot be accessed due to permissions.
    /// </exception>
    /// <remarks>
    /// Normalization process:
    /// - Converts to absolute path if relative
    /// - Resolves all symbolic links to their targets
    /// - Removes redundant path components (., .., duplicate separators)
    /// - Standardizes path separators for the current platform
    /// - Ensures consistent casing on case-insensitive filesystems
    /// 
    /// Implementation details:
    /// - Uses std::filesystem::canonical which converts relative paths to absolute using current working directory
    /// - Resolves all symbolic links and junction points to final targets
    /// - Removes redundant separators, "." and ".." components
    /// - Standardizes path format for the current operating system
    /// - Validates that the final path actually exists in the filesystem
    /// 
    /// Use cases:
    /// - Path comparison and deduplication
    /// - Storing canonical paths in configuration
    /// - Resolving user-provided relative paths
    /// - Security: preventing directory traversal attacks
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
    [[nodiscard]] std::wstring Normalise(std::wstring_view path);
}