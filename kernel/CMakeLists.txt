file(GLOB_RECURSE KERNEL_SOURCES */*.c *.c)
file(GLOB_RECURSE LD_SCRIPT_FILE ${PROJECT_SOURCE_DIR}/scripts/TinyOS-${CMAKE_BUILD_TYPE}.ld)
message(STATUS "LD_SCRIPT_FILE: ${LD_SCRIPT_FILE}")
add_executable(kernel ${KERNEL_SOURCES})
target_compile_options(
    kernel PUBLIC
    $<$<CONFIG:Debug>:-fomit-frame-pointer>
)
target_link_options(
    kernel PUBLIC
    -T ${LD_SCRIPT_FILE} -ffreestanding -nostdlib
)
target_link_libraries(kernel PRIVATE ${PROJECT_NAME}::arch)
set_target_properties(
    kernel PROPERTIES 
    OUTPUT_NAME kernel.bin
)
#=====================================================================
#================= find some tools ===================================
message(STATUS "[OPTIONAL] xorriso path: $ENV{XORRISO_EXE}")
message(STATUS "[REQUIRED] QEUM path: $ENV{QEUM_EXE}")
message(STATUS "[REQUIRED] objdump path: ${OBJDUMPER}")
message(STATUS "[OPTIONAL] grub-mkimage path: $ENV{GRUB_MKIMAGE_EXE}")
#=====================================================================

if(EXISTS ${CMAKE_BINARY_DIR}/kernel/kernel.iso)
    message(STATUS "Remove old kernel.iso")
    file(REMOVE ${CMAKE_BINARY_DIR}/kernel/kernel.iso)
endif()
add_custom_target(
    BUILD_KERNEL_ISO ALL
    COMMAND ${OBJDUMPER} -D kernel.bin > dump
    COMMAND $ENV{GRUB_MKIMAGE_EXE} -O i386-pc -o kernel.iso -p ./
    COMMAND $ENV{XORRISO_EXE} -as mkisofs -o kernel.iso -b kernel.iso -no-emul-boot -boot-load-size 4 -boot-info-table ./ 
    DEPENDS kernel
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/kernel
    COMMENT "Convert the ELF output file to a iso"
    BYPRODUCTS kernel.iso dump
    VERBATIM
)

add_custom_target(
    RUN_KERNEL_IN_QEMU
    COMMAND $ENV{QEUM_EXE} -cdrom kernel.iso
    DEPENDS BUILD_KERNEL_ISO
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/kernel
    COMMENT "Run the kernel in qemu"
    VERBATIM
)