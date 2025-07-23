// PathHelpers.cpp
#include "pch.h"
#include "PathHelpers.h"
#include <filesystem>

using namespace std::filesystem;

namespace native::ToolkitCore
{
    bool IsDirectory(std::wstring_view p) { return is_directory(path{ p }); }
    std::wstring Normalise(std::wstring_view p) { return canonical(path{ p }).wstring(); }
}
