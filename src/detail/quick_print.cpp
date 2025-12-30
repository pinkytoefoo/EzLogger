#include <string>

#include "detail/quick_print.hpp"

namespace ezlog::detail
{
    void quick_print(std::string_view s)
    {
        std::fputs(s.data(), stdout);
        std::fputc('\n', stdout);
    }
}
