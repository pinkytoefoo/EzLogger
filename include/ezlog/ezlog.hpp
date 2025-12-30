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
#include "ezlog/core.hpp"

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

    class logger
    {
    public:
        logger();
        logger(level lvl);
        ~logger() = default;
        // TODO: replace with string_view
        void log(const std::string& msg, color c = color::default_);
        template<typename... Args>
        void log(color c, std::format_string<Args...>, Args&&... args)
        {
            write(std::format("{}", std::forward<Args>(args)...), c);
        }

        void trace(const std::string& msg);
        void info(const std::string& msg);
        void warn(const std::string& msg);
        void error(const std::string& msg);
    private:
        void write(std::string_view msg, color c); 
        void log_if(const std::string& msg, level lvl, color c = color::default_);
        level level_{level::trace};
        bool ansi_enabled_{true};
    };
}
