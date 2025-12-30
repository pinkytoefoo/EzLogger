#include "ezlog/ezlog.hpp"
#include "ezlog/detail.hpp"
#include "ezlog/platform.hpp"

namespace ezlog
{
    logger::logger() 
        : level_{level::trace}
    {
        ansi_enabled_ = platform::enable_ansi();
    }
    
    logger::logger(level lvl)
        : level_{lvl}
    {
        ansi_enabled_ = platform::enable_ansi();
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
        if(ansi_enabled_)
            detail::quick_print("{}{}{}", ansi(c), msg, ansi(color::default_));
        else   
        {
        #ifdef EZ_WINDOWS
            SET_COLOR(c);
            detail::quick_print("{}", msg);
            SET_COLOR(color::default_);
        #else 
            detail::quick_print("{}", msg);
        #endif
        }
    }

    void logger::log_if(std::string_view msg, level lvl, color c)
    {
        if(lvl >= level_)
            write(msg, c);
    }

    #ifdef EZ_POSIX
    constexpr std::string_view ansi(color c)
    {
        switch (c)
        {
            case color::red:        return "\033[31m";
            case color::green:      return "\033[32m";
            case color::yellow:     return "\033[33m";
            case color::blue:       return "\033[34m";
            case color::magenta:    return "\033[35m";
            case color::cyan:       return "\033[36m";
            case color::white:      return "\033[37m";
            // case color::default_:   return "\033[38m";
            default:                return "\033[00m";
        }
    }
    #elifdef EZ_WINDOWS 
    constexpr unsigned short win_attr(color c)
    {
        switch (c)
        {
            case color::black:          return 0x0000;
            case color::blue:           return 0x0001;
            case color::green:          return 0x0002;
            case color::bright_blue:    return 0x0003;
            case color::red:            return 0x0004;
            case color::magenta:        return 0x0005;
            case color::yellow:         return 0x0006;
            case color::white:          return 0x0007;
            case color::default_:       return 0x0007;
            default:                    return 0x0007;
        }
    }
    #endif

    // delegate this to `platform` or `detail` namespace / file
    // void check_win_posix_friendly()
    // {
    //     char* wt_session = getenv("WT_SESSION");
    //     if(wt_session != nullptr && strlen(wt_session) > 0) // 64 should be enough bytes
    //     {
    //         #define EZ_POSIX
    //     }
    // }
}
