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

namespace ezlog
{
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
        void log_if(std::string_view msg, level lvl, color c = color::default_);
        void write(std::string_view msg, color c);
        
        level level_{level::trace};
    };
}
