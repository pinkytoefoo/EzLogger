#pragma once

#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
# define EZ_WINDOWS
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#   define EZ_POSIX
#endif

#if defined(EZ_WINDOWS)
#   include <Windows.h>
#elif defined(EZ_POSIX)
#   include <unistd.h>
#endif

#include <string>
#include <format>

namespace ezlog
{
    void info(const std::string& msg)
    {
        // std::cout << "\033[32m" << msg << '\n' << "\033[00m";
        std::cout << "\e[4;32m" << msg << '\n' << "\e[0;0m";
    }
    // class EzLogger
    // {
    // public:
    //
    // private:
    //
    // };
}

#ifdef EZ_WINDOWS
#define F_DARKBLUE     0x0001
#define F_GREEN        0x0002
#define F_LIGHTBLUE    0x0003
#define F_RED          0x0004
#define F_PURPLE       0x0005
#define F_DARKYELLOW   0x0006
#define F_WHITE        0x0007
#define F_INTESIFY     0x0008
#define F_BLUE         0x0009
#define F_LIGHTGREEN   0x000A
#define F_CYAN         0x000B
#define F_LIGHTPURPLE  0x000C
#define F_LIGHTRED     0x000D
#define F_LIGHTYELLOW  0x000E

namespace EzLogger
{
    enum LogLevel
	{
		EZ_TRACE, EZ_INFO, EZ_WARN, EZ_ERROR
	};

	class EzLogger
	{
	public:
		EzLogger() = default;
        ~EzLogger() = default;
		EzLogger(LogLevel loglevel, const std::string& type)
            : m_LogLevel(loglevel), m_Type(type)
        {

        }

		void SetLogLevel(LogLevel loglevel) { m_LogLevel = loglevel; }
        void SetType(const std::string& type) { m_Type = type; }
        std::string& GetType() { return m_Type; }

        void SetPattern(const std::string& pattern)
        {
            m_Format = pattern;
            for(size_t i = 0; i < m_Format.size(); i++)
            {
                switch(m_Format.at(i))
                {
                    case '%':
                        if(m_Format.at(i + 1) == 't')
                        {
                            m_Format.replace(i, i + 2, m_Type);
                        }
                        break;
                }
            }
        }

        void Log(uint8_t color, const char* msg, ...)
        {
            va_list args;
            va_start(args, msg);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            const std::string& new_msg = m_Format + msg + "\n";
            vprintf(new_msg.c_str(), args);
            va_end(args);
        }

        void Trace(const char* msg, ...)
        {
            va_list args;
            va_start(args, msg);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), F_WHITE);
            const std::string& new_msg = m_Format + msg + "\n";
            vprintf(new_msg.c_str(), args);
            va_end(args);
        }

        void Info(const char* msg, ...)
        {
            if(m_LogLevel >= LogLevel::EZ_INFO)
            {
                va_list args;
                va_start(args, msg);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), F_GREEN);
                // if(m_Format.empty())
                //     return;
                std::string new_msg = m_Format + msg + '\n';
                vprintf(new_msg.c_str(), args);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), F_WHITE);
                va_end(args);
            }
        }

        void Warn(const char* msg, ...)
        {
            if(m_LogLevel >= LogLevel::EZ_WARN)
            {
                va_list args;
                va_start(args, msg);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), F_DARKYELLOW);
                const std::string& new_msg = m_Format + msg + "\n";
                vprintf(new_msg.c_str(), args);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), F_WHITE);
                va_end(args);
            }
        }

        void Error(const char* msg, ...)
        {
            if(m_LogLevel >= LogLevel::EZ_ERROR)
            {
                va_list args;
                va_start(args, msg);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), F_RED);
                const std::string& new_msg = m_Format + msg + "\n";
                vprintf(new_msg.c_str(), args);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), F_WHITE);
                va_end(args);
            }
        }
	private:
		LogLevel m_LogLevel = LogLevel::EZ_TRACE;
        std::string m_Type, m_Format;
	};
}
#endif
