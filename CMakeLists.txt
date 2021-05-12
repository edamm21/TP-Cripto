cmake_minimum_required(VERSION 3.16)
project(TP_Cripto)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(TP_Cripto
        src/main.c
        src/args_parser.c
        src/distribution.c
        src/finding.c
        src/header_struct.h
        src/header_parser.c
        src/header_parser.h
        src/common/helper.c
        src/common/helper.h)

target_link_libraries(TP_Cripto m)