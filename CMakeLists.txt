cmake_minimum_required(VERSION 3.15)
project(ezlog LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

option(BUILD_EXAMPLES "Build ezlog examples" ON)
if(BUILD_EXAMPLES)
    add_executable(ezlog example/example.cpp)
endif()

if(MINGW)
    target_link_libraries(ezlog PRIVATE "-lstdc++exp")
endif()

target_include_directories(ezlog PRIVATE include)