// ezlog c-compatible logging functions
//           _             
//   ___ ___| | ___   __ _ 
//  / _ \_  / |/ _ \ / _` |
// |  __// /| | (_) | (_| |
//  \___/___|_|\___/ \__, |
//                   |___/ 

#pragma once

#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#   define EZ_POSIX
#elif defined(_WIN32) || defined(_WIN64)
#   define EZ_WINDOWS
#endif

#if defined(EZ_WINDOWS)
#   include <Windows.h>
#elif defined(EZ_POSIX)
#   include <unistd.h>
#endif

#include <string>
#include <format>
#include <cstring>

#ifdef EZ_WINDOWS
#   define SET_WINDOWS_COLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), win_attr(color))
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef enum {
    DEFAULT,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    BRIGHT_RED,
    BRIGHT_GREEN,
    BRIGHT_YELLOW,
    BRIGHT_BLUE,
    BRIGHT_MAGENTA,
    BRIGHT_CYAN,
    BRIGHT_WHITE,
} color;

typedef enum {
    LEVEL_TRACE,
    LEVEL_INFO,
    LEVEL_WARN,
    LEVEL_ERROR,
} level;

static const char* ansi(color c) {
    switch (c) {
        case BLACK:                 return "\x1b[30m";
        case RED:                   return "\x1b[31m";
        case GREEN:                 return "\x1b[32m";
        case YELLOW:                return "\x1b[33m";
        case BLUE:                  return "\x1b[34m";
        case MAGENTA:               return "\x1b[35m";
        case CYAN:                  return "\x1b[36m";
        case WHITE:                 return "\x1b[37m";
        case BRIGHT_RED:            return "\x1b[91m";
        case BRIGHT_GREEN:          return "\x1b[92m";
        case BRIGHT_YELLOW:         return "\x1b[93m";
        case BRIGHT_BLUE:           return "\x1b[94m";
        case BRIGHT_MAGENTA:        return "\x1b[95m";
        case BRIGHT_CYAN:           return "\x1b[96m";
        case BRIGHT_WHITE:          return "\x1b[97m";
        case DEFAULT:
        default:
            return "\x1b[0m";
    }
}

#if defined(_WIN32)
static unsigned short win_attr(color c) {
    switch (c) {
        case color::BLACK:          return 0x0000;
        case color::BLUE:           return 0x0001;
        case color::GREEN:          return 0x0002;
        case color::BRIGHT_BLUE:    return 0x0003;
        case color::RED:            return 0x0004;
        case color::MAGENTA:        return 0x0005;
        case color::YELLOW:         return 0x0006;
        case color::WHITE:          return 0x0007;
        case color::DEFAULT:        return 0x0007;
        default:                    return 0x0007;
    }
}
#endif

static void quick_print_format(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    fputc('\n', stdout);
    va_end(args);
}

static void write(const char* str, color c) {
#if defined(EZ_POSIX)
    quick_print_format("%s%s%s", ansi(c), str, ansi(color::default_));
#elif defined(EZ_WINDOWS)
    SET_WINDOWS_COLOR(c);
    quick_print_format(str);
    SET_WINDOWS_COLOR(color::DEFAULT);
#else
    quick_print(str); // if no platform detected, print without color
#endif
}

void ez_trace(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    write(buffer, color::DEFAULT);
}

void ez_info(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    write(buffer, color::GREEN);
}

void ez_warn(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    write(buffer, color::YELLOW);
}

void ez_error(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    write(buffer, color::RED);
}
