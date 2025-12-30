#pragma once

#include <string>
#include <format>

#include "ezlog/color.hpp"
#include "detail/color_ansi.hpp"
#include "detail/color_win32.hpp"

namespace ezlog::platform
{
    enum class backend
    {
        none,
        ansi,
        win32     
    };

    backend detect_backend();

    void write_color(std::string_view msg, color c, backend b);
    template<typename... Args>
    void write_color_fmt(color c, backend b, std::format_string<Args...> str, Args&&... args)
    {
        switch(b)
        {
            case backend::ansi:
                quick_print(str, ansi(c), std::forward<Args>(args)..., ansi(color::default_));
                break;
            case backend::win32:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), win_attr(c));
                quick_print(str, std::forward<Args>(args)...);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), win_attr(color::default_));
                break;
            // if no api, just log the message (no color)
            case backend::none:
                quick_print(str, std::forward<Args>(args)...);
                break;
        }
    }
}
