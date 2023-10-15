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
message(STATUS "xorriso path: $ENV{XORRISO_EXE}")
message(STATUS "grub-mkimage path: $ENV{GRUB_MKIMAGE_EXE}")
message(STATUS "grub-mkrescue path: $ENV{GRUB_MKRESCUE_EXE}")
#=====================================================================
add_custom_target(
    BUILD_KERNEL_ISO ALL
    COMMAND ${OBJDUMPER} -D kernel.bin > dump
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/scripts/grub.cfg iso/boot/grub/grub.cfg
    COMMAND ${CMAKE_COMMAND} -E copy kernel.bin iso/boot/kernel.bin
    COMMAND $ENV{GRUB_MKIMAGE_EXE} -o iso/boot/core.img -O i386-pc -p iso/boot -c iso/boot/grub/grub.cfg multiboot #iso9660 # # 创建了一个空的iso文件
    COMMAND $ENV{XORRISO_EXE} -as mkisofs -R -J -o kernel.iso iso -b /boot/kernel.bin -no-emul-boot #  -boot-load-size 4 -boot-info-table #    
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