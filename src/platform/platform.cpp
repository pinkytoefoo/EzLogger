#if defined(_WIN32)
#   include <Windows.h>
#endif

#include "platform.hpp"
#include "detail/quick_print.hpp"
#include "detail/color_ansi.hpp"
#include "detail/color_win32.hpp"

namespace ezlog::platform
{
    backend detect_backend()
    {
    #if defined(_WIN32)
        // windows terminal emulator / ansi capable terminalsS
        if (const char* wt = getenv("WT_SESSION"))
            return backend::ansi;

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (h == INVALID_HANDLE_VALUE)
            return backend::none;

        DWORD mode = 0;
        if (GetConsoleMode(h, &mode) &&
            (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING))
            return backend::ansi;

        return backend::win32;
    #else
        // assume posix and ansi capable terminal
        return color_backend::ansi;
    #endif
    }

    void write_color(std::string_view msg, color c, backend b)
    {
        switch(b)
        {
            case backend::ansi:
                detail::quick_print("{}{}{}", ansi(c), msg, ansi(color::default_));
                break;
            case backend::win32:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), win_attr(c));
                detail::quick_print("{}", msg);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), win_attr(color::default_));
                break;
            // if no api, just log the message (no color)
            case backend::none:
                detail::quick_print("{}", msg);
                break;
        }
    }
}

