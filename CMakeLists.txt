cmake_minimum_required(VERSION 3.15)
project(ezlog LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ezlog STATIC)

target_sources(ezlog
    PRIVATE
        src/ezlog.cpp
        src/platform/platform.cpp
        src/detail/quick_print.cpp
)

target_include_directories(ezlog
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (WIN32)
    target_link_libraries(ezlog PRIVATE kernel32)
endif()

if(MINGW)
    target_link_libraries(ezlog PRIVATE stdc++exp)
endif()

option(EZLOG_BUILD_EXAMPLE "" ON)
if(EZLOG_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()
