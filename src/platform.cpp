#include "ezlog/platform.hpp"

#if defined(_WIN32)
#   include <Windows.h>
#endif

namespace ezlog::platform
{
    color_backend detect_color_backend()
    {
    #if defined(_WIN32)
        // windows terminal emulator / ansi capable terminalsS
        if (const char* wt = getenv("WT_SESSION"))
            return color_backend::ansi;

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (h == INVALID_HANDLE_VALUE)
            return color_backend::none;

        DWORD mode = 0;
        if (GetConsoleMode(h, &mode) &&
            (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING))
            return color_backend::ansi;

        return color_backend::win32;
    #else
        // assume posix and ansi capable terminal
        return color_backend::ansi;
    #endif
    }
}

