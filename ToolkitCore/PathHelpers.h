#pragma once
#include <string>
#include <string_view>

namespace native::ToolkitCore
{
    /// <summary>
    /// Determines whether the specified path refers to an existing directory.
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
    /// Performance considerations:
    /// - Performs actual filesystem access (I/O operation)
    /// - May be slow for network drives or removable media
    /// - Consider caching results for frequently checked paths
    /// 
    /// Exception handling:
    /// - Returns false for inaccessible paths (permissions, network issues)
    /// - Does not throw exceptions for common error conditions
    /// - Uses noexcept filesystem operations internally
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
    /// Empty string if the path is invalid or inaccessible.
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
    /// Use cases:
    /// - Path comparison and deduplication
    /// - Storing canonical paths in configuration
    /// - Resolving user-provided relative paths
    /// - Security: preventing directory traversal attacks
    /// 
    /// Performance notes:
    /// - Performs filesystem I/O to resolve links and validate existence
    /// - More expensive than simple string manipulation
    /// - Consider caching results for frequently used paths
    /// 
    /// Platform behavior:
    /// - Windows: Resolves NTFS junction points and symbolic links
    /// - Uses native path separators (\\ on Windows)
    /// - Handles long path names and Unicode correctly
    /// </remarks>
    [[nodiscard]] std::wstring Normalise(std::wstring_view path);
}