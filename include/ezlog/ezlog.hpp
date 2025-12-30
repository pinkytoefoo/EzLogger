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
#include <cstdlib>
#include <format>
#include <cstring>

#include "ezlog/color.hpp"
#include "ezlog/detail.hpp"

#ifdef EZ_WINDOWS
static const HANDLE g_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#define SET_COLOR(color) SetConsoleTextAttribute(g_handle, ::ezlog::win_attr(color))
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
        ezlog();
        ezlog(level lvl);
        ~ezlog() = default;

        void log(const std::string& msg, color c = color::default_);
        
        void trace(const std::string& msg);
        void info(const std::string& msg);
        void warn(const std::string& msg);
        void error(const std::string& msg);
    private:
        void write(std::string_view msg, color c); 

        void log_if(const std::string& msg, level lvl, color c = color::default_);
        level level_{level::trace};
    };
}
