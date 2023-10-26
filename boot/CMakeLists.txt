file(
    GLOB_RECURSE BOOT_SOURCES 
    src/*.c
    src/*.S
    src/*.s
)
# 头文件合集
add_library(boot STATIC ${BOOT_SOURCES})
target_include_directories(
    boot 
    PUBLIC include 
    PRIVATE ${CMAKE_SOURCE_DIR}/kernel/include
)
add_library(${PROJECT_NAME}::boot ALIAS boot)
target_compile_options(
    boot PUBLIC
    -c
    -Wno-shift-count-overflow
    -Wno-int-conversion
)