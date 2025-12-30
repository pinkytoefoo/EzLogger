//           _             
//   ___ ___| | ___   __ _ 
//  / _ \_  / |/ _ \ / _` |
// |  __// /| | (_) | (_| |
//  \___/___|_|\___/ \__, |
//                   |___/ 

#pragma once


#include <string>
#include <cstdlib>
#include <format>
#include <cstring>

#include "ezlog/color.hpp"
#include "ezlog/detail.hpp"
#include "ezlog/platform.hpp"

#if defined(EZ_WINDOWS)
#   include <Windows.h>
static const HANDLE g_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#   define SET_COLOR(color) SetConsoleTextAttribute(g_handle, ::ezlog::win_attr(color))
#elif defined(EZ_POSIX)
#   include <unistd.h>
#endif

namespace ezlog
{
    // TODO: move these two functions into a seperate namespace
    // user does not need access to these helper functions
    constexpr std::string_view ansi(color c);
    constexpr unsigned short win_attr(color c);

    enum class level
    {
        trace, info, warn, error,
    };

    // TODO: add name_ and a way to set how messages are printed
    // e.g. set_pattern("%n [%l]: %s");
    // %n could be name and %l could be level and %s could be the message
    // modify the `write` method to use that set pattern
    class logger
    {
    public:
        logger();
        logger(level lvl);
        ~logger() = default;

        void log(std::string_view, color c = color::default_);
        template<typename... Args>
        void log(color c, std::format_string<Args...>, Args&&... args)
        {
            write(std::format("{}", std::forward<Args>(args)...), c);
        }

        void trace(std::string_view msg);
        void info(std::string_view msg);
        void warn(std::string_view msg);
        void error(std::string_view msg);
    private:
        void write(std::string_view msg, color c); 
        void log_if(std::string_view msg, level lvl, color c = color::default_);
        level level_{level::trace};
        bool ansi_enabled_{true};
    };
}
