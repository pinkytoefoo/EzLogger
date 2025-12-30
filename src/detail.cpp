#include "ezlog/detail.hpp"
#include "ezlog/color.hpp"

#include <string>
#include <format>

namespace detail
{
    void quick_print(std::string_view s)
    {
        std::fputs(s.data(), stdout);
        std::fputc('\n', stdout);
    }

    template<typename... Args>
    void quick_print(std::format_string<Args...> str, Args&&... args)
    {
        std::fputs(std::format(str, std::forward<Args>(args)...).c_str(), stdout);
        std::fputc('\n', stdout);
    }
}
