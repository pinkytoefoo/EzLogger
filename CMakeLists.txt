cmake_minimum_required(VERSION 3.15)
project(ezlog LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

option(EZLOG_LIB "Use compiled library" ON)
if(EZLOG_LIB)
    file(GLOB_RECURSE
        LIB_FILES
        src/*.cpp
        include/*.hpp
    )

    add_library(ezlog STATIC ${LIB_FILES})
    target_include_directories(ezlog PUBLIC include)
endif()

option(EZLOG_LIB_EXAMPLE "Build ezlog examples" ON)
option(EZLOG_SINGLEHEADER_EXAMPLE "Build ezlog examples" OFF)
if(EZLOG_SINGLEHEADER_EXAMPLE)
    add_executable(ez_example example/example.cpp)
    target_include_directories(ez_example PUBLIC single_include)
elseif(EZLOG_LIB_EXAMPLE)
    # option(EZLOG_HEADER_ONLY "Use `single_include` only" ON)
    add_executable(ez_example example/example.cpp)
    target_include_directories(ez_example PUBLIC include)
    target_link_libraries(ez_example PRIVATE ezlog)
endif()

if(MINGW)
    target_link_libraries(ez_example PRIVATE "-lstdc++exp")
endif()

