cmake_minimum_required(VERSION 3.16)
project(TP_Cripto C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(TP_Cripto
        src/main.c
        src/args_parser.c
        src/config.c
        src/distribution.c
        src/finding.c)
