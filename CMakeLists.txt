cmake_minimum_required(VERSION 3.26)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_OUTPUT_EXTENSION ".o")
set(CMAKE_ASM_OUTPUT_EXTENSION ".o")
project(TinyOS VERSION 0.1.0 LANGUAGES C CXX ASM)

# project setttings
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include_directories(include)
add_subdirectory(arch)
add_subdirectory(kernel)
add_subdirectory(hal)