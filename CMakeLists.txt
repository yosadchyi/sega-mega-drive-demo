cmake_minimum_required(VERSION 3.10)
project(Demo C)

set(CMAKE_C_STANDARD 11)

include_directories(/opt/toolchains/gen/m68k-elf/include)
include_directories(res)
include_directories(src)

add_executable(Demo
        res/gfx.h
        src/boot/rom_head.c
        src/main.c
        src/main.h
        build.sh)
