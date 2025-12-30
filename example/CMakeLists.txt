project(ez_example)

add_executable(ez_example example/example.cpp)

if (EZLOG_SINGLE_HEADER_EXAMPLE)
    target_include_directories(ez_example PRIVATE single_include)
else()
    target_link_libraries(ez_example PRIVATE ezlog)
endif()