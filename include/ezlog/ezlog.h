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

// #include <iostream>
#include <string>
#include <format>

#ifdef EZ_WINDOWS
#   define SET_COLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ::ezlog::toWinAttr(color))
#endif

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

    constexpr std::string_view toAnsi(color c) {
        switch (c) {
            case color::red:        return "\e[0;31m";
            case color::green:      return "\e[0;32m";
            case color::yellow:     return "\e[0;33m";
            case color::blue:       return "\e[0;34m";
            case color::magenta:    return "\e[0;35m";
            case color::cyan:       return "\e[0;36m";
            case color::white:      return "\e[0;37m";
            case color::default_:   return "\e[0;39m";
            default:                return "\e[0;00m";
        }
    }

    constexpr WORD toWinAttr(color c) {
        switch (c) {
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

    enum class level
    {
        trace, info, warn, error,
    };

    class ezlog
    {
    public:
        ezlog() = default;
        ~ezlog() = default;
        ezlog(level lvl)
            : lvl_{lvl}
        {
        }

        void log(const std::string& msg, color c = color::default_)
        {
            #ifdef EZ_POSIX
            std::println("{}{}{}", toAnsi(c), msg, toAnsi(color::default_));
            #elifdef EZ_WINDOWS
            SET_COLOR(c);
            std::println("{}", msg);
            SET_COLOR(color::default_);
            #endif
        }
        
        void trace(const std::string& msg)
        {
            _logIf(msg, level::trace);
        }

        void info(const std::string& msg)
        {
            _logIf(msg, level::info, color::green);
        }

        void warn(const std::string& msg)
        {
            _logIf(msg, level::warn, color::yellow);
        }

        void error(const std::string& msg)
        {
            _logIf(msg, level::error, color::red);
        }
    
    private:
        void _logIf(const std::string& msg, level lvl, color c = color::default_)
        {
            if(lvl >= lvl_)
            {
                #ifdef EZ_POSIX
                std::println("{}{}{}", toAnsi(c), msg, toAnsi(color::default_));
                #elifdef EZ_WINDOWS
                SET_COLOR(c);
                std::println("{}", msg);
                SET_COLOR(color::default_);
                #endif
            }
        }

        level lvl_;
    };
}
