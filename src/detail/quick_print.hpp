#pragma once

#include <string>
#include <format>

namespace ezlog::detail
{
    void quick_print(std::string_view s);

    template<typename... Args>
    void quick_print(std::format_string<Args...> str, Args&&... args)
    {
        std::fputs(std::format(str, std::forward<Args>(args)...).c_str(), stdout);
        std::fputc('\n', stdout);
    }
}
