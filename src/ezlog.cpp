#include "ezlog/ezlog.hpp"
#include "detail/quick_print.hpp"
#include "platform/platform.hpp"
#include "detail/color_ansi.hpp"
#include "detail/color_win32.hpp"

namespace ezlog
{
    static platform::backend g_backend = platform::detect_backend();

    logger::logger() 
        : level_{level::trace}
    {
    }
    
    logger::logger(level lvl)
        : level_{lvl}
    {
    }
    
    void logger::log(std::string_view msg, color c)
    {
        write(msg, c);
    }

    void logger::trace(std::string_view msg)
    {
        log_if(msg, level::trace);
    }

    void logger::info(std::string_view msg)
    {
        log_if(msg, level::info, color::green);
    }

    void logger::warn(std::string_view msg)
    {
        log_if(msg, level::warn, color::yellow);
    }

    void logger::error(std::string_view msg)
    {
        log_if(msg, level::error, color::red);
    }

    void logger::write(std::string_view msg, color c)
    {
        platform::write_color(msg, c, g_backend);
    }

    void logger::log_if(std::string_view msg, level lvl, color c)
    {
        if(lvl >= level_)
            write(msg, c);
    }
}
