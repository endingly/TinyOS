#define TINYOS_MULTIBOOT_MAGIC                    0x1BADB002  // Multiboot magic number
#define TINYOS_MULTIBOOT_FLAG_4KB_ALIGNED_MEM_MAP 0x03        // Page align the memory map
#define TINYOS_MULTIBOOT_PAGE_ALIGN               0x01        // Page align the modules
#define TINYOS_CHECKSUM(tinyos_flags)             (-(TINYOS_MULTIBOOT_MAGIC + tinyos_flags))