#pragma once

namespace ezlog::platform
{
    enum class color_backend
    {
        none,
        ansi,
        win32     
    };

    color_backend detect_color_backend();
}
