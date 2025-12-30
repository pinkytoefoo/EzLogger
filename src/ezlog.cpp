#include "ezlog/ezlog.hpp"
#include "ezlog/detail.hpp"
#include "ezlog/platform.hpp"

namespace ezlog
{
    logger::logger() 
        : level_{level::trace}, backend_{platform::detect_color_backend()}
    {
    }
    
    logger::logger(level lvl)
        : level_{lvl}, backend_{platform::detect_color_backend()}
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
        using namespace platform;
        switch(backend_)
        {
            case color_backend::ansi:
                detail::quick_print("{}{}{}", ansi(c), msg, ansi(color::default_));
                break;
            case color_backend::win32:
                SetConsoleTextAttribute(console_, win_attr(c));
                detail::quick_print("{}", msg);
                SetConsoleTextAttribute(console_, win_attr(color::default_));
                break;
            // if no api, just log the message (no color)
            case color_backend::none:
                detail::quick_print("{}", msg);
                break;
        }
    }

    void logger::log_if(std::string_view msg, level lvl, color c)
    {
        if(lvl >= level_)
            write(msg, c);
    }
}
