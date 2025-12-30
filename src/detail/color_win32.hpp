#pragma once

#include "ezlog/color.hpp"

namespace ezlog
{
    #if defined(_WIN32)
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
    #else
    constexpr unsigned short win_attr(color c) { return -1; }
    #endif
}