add_custom_target(
    BUILD_KERNEL_ISO ALL
    COMMAND ${OBJDUMPER} -D kernel.bin > dump
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/scripts/grub.cfg iso/boot/grub/grub.cfg
    COMMAND ${CMAKE_COMMAND} -E copy kernel.bin iso/boot/kernel.bin
    COMMAND $ENV{GRUB_MKRESCUE_EXE} -o kernel.iso iso
    DEPENDS kernel
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/kernel
    COMMENT "Convert the ELF output file to a iso"
    BYPRODUCTS kernel.iso 
               dump 
               iso/boot/core.img 
               iso/boot/grub/grub.cfg 
               iso/boot/kernel.bin
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