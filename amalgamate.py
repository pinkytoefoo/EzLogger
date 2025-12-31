# !!!! NOT PRODUCTION READY !!!! AT ALL !!!!

top_header_comment="""
//           _             
//   ___ ___| | ___   __ _ 
//  / _ \\_  / |/ _ \\ / _` |
// |  __// /| | (_) | (_| |
//  \\___/___|_|\\___/ \\__, |
//                   |___/ 
"""

files = [
    "include/ezlog/color.hpp",
    "src/detail/color_ansi.hpp",
    "src/detail/color_win32.hpp",
    "src/detail/quick_print.hpp",
    "src/detail/quick_print.cpp",
    "src/platform/platform.hpp",
    "src/platform/platform.cpp",
    "include/ezlog/ezlog.hpp",
    "src/ezlog.cpp"
]

print("writing to single_include/ezlog/auto_ezlog.hpp ...")

with open("single_include/ezlog/auto_ezlog.hpp", "w") as out:
    print("creating header comment ...")
    out.write(top_header_comment)
    out.write("\n\n#pragma once")

    print("\n\nwriting files ...")
    for file in files:
        with open(file, "r") as f:
            print(f"\twriting {file} ...")
            out.write(f.read())

print("done.")