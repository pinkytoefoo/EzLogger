#include "ezlog/platform.hpp"

namespace ezlog::platform
{
    bool enable_ansi()
    {
    #ifdef EZ_WINDOWS
        char* wt_session = getenv("WT_SESSION");
        if(wt_session != nullptr && strlen(wt_session) > 0) // 64 should be enough bytes
            return true;
        
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (h == INVALID_HANDLE_VALUE)
            return false;

        DWORD mode = 0;
        if (!GetConsoleMode(h, &mode))
            return false;

        if (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)
            return true;

        if (!SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
            return false;
    #endif
        return true;
    }
}

