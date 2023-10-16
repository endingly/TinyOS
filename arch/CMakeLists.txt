file(
    GLOB_RECURSE ARCH_SOURCES 
    ${TINYOS_ARCH}/*.c
    ${TINYOS_ARCH}/*.S
)
# 头文件合集
file(GLOB_RECURSE ARCH_HEADERS ${TINYOS_ARCH}/*.h)
add_library(arch STATIC ${ARCH_SOURCES})
target_include_directories(arch PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_library(${PROJECT_NAME}::arch ALIAS arch)
target_compile_options(arch PUBLIC -c)