cmake_minimum_required(VERSION 3.31)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        sniffer.c
        ports.c
        main.c
)
target_link_libraries(untitled ws2_32)
