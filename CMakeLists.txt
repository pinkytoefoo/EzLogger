cmake_minimum_required(VERSION 3.15)

project(ezlog)

# option(BUILD_EXAMPLES ON)
# if(BUILD_EXAMPLES)
add_executable(ezlog example/example.cpp)
# endif()

target_include_directories(ezlog PRIVATE include)
