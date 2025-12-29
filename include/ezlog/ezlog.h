#pragma once

#include <cstdlib>
#include <print>

// TODO: implement this some way
// bool checkTerminalEmulator()
// {
//     char* wtSession = getenv("WT_SESSION");
//     return (wtSession != nullptr && std::string(wtSession).length() > 0);
// }

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

#ifdef EZ_WINDOWS
static const HANDLE g_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#define SET_COLOR(color) SetConsoleTextAttribute(g_handle, ::ezlog::win_attr(color))
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

    // TODO: move these two functions into a seperate namespace
    // user does not need access to these helper functions
    constexpr std::string_view ansi(color c);
    constexpr unsigned short win_attr(color c);

    enum class level
    {
        trace, info, warn, error,
    };

    class ezlog
    {
    public:
        ezlog()
            : level_{level::trace}
        {
            char* wt_session = getenv("WT_SESSION");
            if(wt_session != nullptr && strnlen(wt_session, 64) > 0) // 64 should be enough bytes
            {
                #define EZ_POSIX
            }
        }
        ezlog(level lvl)
        : level_{lvl}
        {
        }
        ~ezlog() = default;

        void log(const std::string& msg, color c = color::default_)
        {
            write(msg, c);
        }
        
        void trace(const std::string& msg)
        {
            log_if(msg, level::trace);
        }

        void info(const std::string& msg)
        {
            log_if(msg, level::info, color::green);
        }

        void warn(const std::string& msg)
        {
            log_if(msg, level::warn, color::yellow);
        }

        void error(const std::string& msg)
        {
            log_if(msg, level::error, color::red);
        }
    
    private:
        void write(std::string_view msg, color c)
        {
            #ifdef EZ_POSIX
            detail::quick_print("{}{}{}", ansi(c), msg, ansi(color::default_));
            #elifdef EZ_WINDOWS
            SET_COLOR(c);
            detail::quick_print("{}", msg);
            SET_COLOR(color::default_);
            #endif
        }

        void log_if(const std::string& msg, level lvl, color c = color::default_)
        {
            if(lvl >= level_)
                write(msg, c);
        }

        level level_{level::trace};
    };

    // TODO: this is a copout to avoid windows not being able to find ansi definition
    // make this cleaner (line 124)
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
}
