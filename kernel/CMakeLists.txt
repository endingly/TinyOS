file(GLOB_RECURSE KERNEL_SOURCES */*.c *.c)
file(GLOB_RECURSE LD_SCRIPT_FILE ${PROJECT_SOURCE_DIR}/scripts/TinyOS-${CMAKE_BUILD_TYPE}.ld)
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
message(STATUS "[REQUIRED] QEUM path: $ENV{QEUM_EXE}")
message(STATUS "[REQUIRED] objdump path: ${OBJDUMPER}")
message(STATUS "[REQUIRED] grub-mkrescue path: $ENV{GRUB_MKRESCUE_EXE}")
#=====================================================================

execute_process(
    COMMAND mkdir -p boot/iso/grub
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/kernel
)

add_custom_target(
    BUILD_KERNEL_ISO ALL
    COMMAND cp kernel.bin boot/kernel.bin
    COMMAND ${OBJDUMPER} -D kernel.bin > dump
    COMMAND cp ${PROJECT_SOURCE_DIR}/scripts/grub.cfg boot/iso/grub/grub.cfg
    COMMAND $ENV{GRUB_MKRESCUE_EXE} -o boot/iso/kernel.iso
    DEPENDS kernel
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/kernel
    COMMENT "Convert the ELF output file to a iso"
    BYPRODUCTS boot/iso/kernel.iso dump boot/iso/grub/grub.cfg boot/kernel.bin
    VERBATIM
)

add_custom_target(
    RUN_KERNEL_IN_QEMU
    COMMAND $ENV{QEUM_EXE} -cdrom boot/iso/kernel.iso
    DEPENDS BUILD_KERNEL_ISO
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/kernel
    COMMENT "Run the kernel in qemu"
    VERBATIM
)