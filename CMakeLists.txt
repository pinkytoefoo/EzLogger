cmake_minimum_required(VERSION 3.15)
project(ezlog LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(EZLOG_BUILD_LIB "Build ezlog static library" ON)
option(EZLOG_BUILD_EXAMPLE "Build ezlog example" ON)
option(EZLOG_SINGLE_HEADER_EXAMPLE "Use single_include for example" OFF)

if (EZLOG_BUILD_LIB)
    add_library(ezlog STATIC
        src/ezlog.cpp
        src/detail.cpp
        src/platform.cpp
    )

    target_include_directories(ezlog
        PUBLIC
            src
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
endif()

if (EZLOG_BUILD_EXAMPLE)
    add_executable(ez_example example/example.cpp)

    if (EZLOG_SINGLE_HEADER_EXAMPLE)
        target_include_directories(ez_example PRIVATE single_include)
    else()
        target_link_libraries(ez_example PRIVATE ezlog)
    endif()
endif()

if (MINGW)
    target_link_libraries(ezlog PRIVATE stdc++exp)
endif()
