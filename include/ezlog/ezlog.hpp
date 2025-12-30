//           _             
//   ___ ___| | ___   __ _ 
//  / _ \_  / |/ _ \ / _` |
// |  __// /| | (_) | (_| |
//  \___/___|_|\___/ \__, |
//                   |___/ 

#pragma once

#if defined(_WIN32)
#   include <Windows.h>
#endif

#include <string>
#include <cstdlib>
#include <format>
#include <cstring>

#include "ezlog/color.hpp"
#include "ezlog/detail.hpp"
#include "ezlog/platform.hpp"

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
        void log(color c, std::format_string<Args...> str, Args&&... args)
        {
            write(std::format(str, std::forward<Args>(args)...), c);
        }

        void trace(std::string_view msg);
        void info(std::string_view msg);
        void warn(std::string_view msg);
        void error(std::string_view msg);
    private:
        void write(std::string_view msg, color c); 
        void log_if(std::string_view msg, level lvl, color c = color::default_);

        level level_{level::trace};
        platform::color_backend backend_{platform::color_backend::ansi};
    #if defined(_WIN32)
        HANDLE console_{nullptr};
    #endif
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
            case color::intensify:      return 0x0008;
            default:                    return 0x0007;
        }
    }
}
