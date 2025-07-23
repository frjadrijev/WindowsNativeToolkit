#pragma once
#include <string>
#include <string_view>

namespace native::ToolkitCore
{
    [[nodiscard]] bool IsDirectory(std::wstring_view path);
    [[nodiscard]] std::wstring Normalise(std::wstring_view path);
}