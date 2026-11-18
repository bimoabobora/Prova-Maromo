
cmake_minimum_required(VERSION 3.20)

project(Prova_Maromo C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(Prova_Maromo ${SOURCES}
        main.c
        modulo.c
        modulo.h)

target_include_directories(Prova_Maromo PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
