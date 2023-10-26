file(GLOB_RECURSE KERNEL_SOURCES */*.c *.c)
file(GLOB_RECURSE LD_SCRIPT_FILE ${PROJECT_SOURCE_DIR}/scripts/TinyOS-${CMAKE_BUILD_TYPE}.ld)
add_executable(kernel ${KERNEL_SOURCES})
target_include_directories(
    kernel PUBLIC
    include
)
target_compile_options(
    kernel PUBLIC
    -mgeneral-regs-only
    $<$<CONFIG:Release>:-fomit-frame-pointer>
)
target_link_options(
    kernel PUBLIC
    -T ${LD_SCRIPT_FILE} -ffreestanding -nostdlib
)
target_link_libraries(kernel PRIVATE ${PROJECT_NAME}::boot)
set_target_properties(
    kernel PROPERTIES 
    OUTPUT_NAME kernel.bin
)
#=====================================================================
#================= find some tools ===================================
message(STATUS "[REQUIRED] QEUM path: $ENV{QEUM_EXE}")
message(STATUS "grub-mkrescue path: $ENV{GRUB_MKRESCUE_EXE}")
#=====================================================================
include(custom_command)