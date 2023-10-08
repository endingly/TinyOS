cmake_minimum_required(VERSION 3.26)

project(TinyOS VERSION 0.1.0 LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES
    "src/*.c"
    "src/*.cpp"
    "src/*.s"
)

add_executable(${PROJECT_NAME} ${SOURCES})