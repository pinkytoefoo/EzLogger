// ezlog capabilities, but compatible with c
//           _             
//   ___ ___| | ___   __ _ 
//  / _ \_  / |/ _ \ / _` |
// |  __// /| | (_) | (_| |
//  \___/___|_|\___/ \__, |
//                   |___/ 

#pragma once

#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#   define EZ_POSIX
#elif defined(_WIN32) || defined(_WIN64)
#   define EZ_WINDOWS
#endif

#if defined(EZ_WINDOWS)
#   include <Windows.h>
#elif defined(EZ_POSIX)
#   include <unistd.h>
#endif

#include <string>
#include <format>
#include <cstring>

#ifdef EZ_WINDOWS
#   define SET_WINDOWS_COLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ::ezlog::win_attr(color))
#endif

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

namespace ezlog
{
    enum class color
    {
        default_,
        black,
        red,
        green,
        yellow,
        blue,
        magenta,
        cyan,
        white,
        bright_red,
        bright_green,
        bright_yellow,
        bright_blue,
        bright_magenta,
        bright_cyan,
        bright_white,
    };

    constexpr std::string_view ansi(color c);
    constexpr unsigned short win_attr(color c);

    enum class level
    {
        trace, info, warn, error,
    };

    class logger
    {
    public:
        logger()
            : level_{level::trace}
        {
            if(const char* wt = getenv("WT_SESSION"))
            {
                #define EZ_POSIX
            }
        }
        logger(level lvl)
            : level_{lvl}
        {
            if(const char* wt = getenv("WT_SESSION"))
            {
                #define EZ_POSIX
            }
        }
        ~logger() = default;

        template<typename... Args>
        void log(color c, std::format_string<Args...> str, Args&&... args)
        {
            write(std::format(str, std::forward<Args>(args)...), c);
        }
        template<typename... Args>
        void trace(std::format_string<Args...> str, Args&&... args)
        {
            log_if(std::format(str, std::forward<Args>(args)...), level::trace, color::default_);
        }
        template<typename... Args>
        void info(std::format_string<Args...> str, Args&&... args)
        {
            log_if(std::format(str, std::forward<Args>(args)...), level::info, color::green);
        }
        template<typename... Args>
        void warn(std::format_string<Args...> str, Args&&... args)
        {
            log_if(std::format(str, std::forward<Args>(args)...), level::warn, color::yellow);
        }
        template<typename... Args>
        void error(std::format_string<Args...> str, Args&&... args)
        {
            log_if(std::format(str, std::forward<Args>(args)...), level::error, color::red);
        }
    private:
        void write(std::string_view msg, color c)
        {
        #if defined(EZ_POSIX)
            detail::quick_print("{}{}{}", ansi(c), msg, ansi(color::default_));
        #elif defined(EZ_WINDOWS)
            SET_WINDOWS_COLOR(c);
            detail::quick_print("{}", msg);
            SET_WINDOWS_COLOR(color::default_);
        #else
            detail::quick_print("{}", msg); // if no platform detected, print without color
        #endif
        }

        void log_if(std::string_view msg, level lvl, color c = color::default_)
        {
            if(lvl >= level_)
                write(msg, c);
        }

        level level_{level::trace};
    };

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
}