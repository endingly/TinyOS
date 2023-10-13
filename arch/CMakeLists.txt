file(
    GLOB_RECURSE ARCH_SOURCES 
    ${TINYOS_ARCH}/*.c
    ${TINYOS_ARCH}/*.S
    ${TINYOS_ARCH}/*.h
)
foreach(item IN LISTS ARCH_SOURCES)
    message(CHECK_START "find source file in arch/${TINYOS_ARCH}: ${item}")
endforeach()

add_library(arch STATIC ${ARCH_SOURCES})
add_library(${PROJECT_NAME}::arch ALIAS arch)
target_compile_options(arch PUBLIC -c)