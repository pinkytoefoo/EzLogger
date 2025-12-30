#pragma once

#include <string>
#include <format>

namespace detail
{
    void quick_print(std::string_view s);

    template<typename... Args>
    void quick_print(std::format_string<Args...> str, Args&&... args);
}
