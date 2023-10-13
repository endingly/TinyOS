#define TINYOS_MULTIBOOT_MAGIC 0x1BADB002
#define TINYOS_MULTIBOOT_FLAG_4KB_ALIGNED_MEM_MAP 0x03

#define TINYOS_CHECKSUM(tinyos_flags) (-(TINYOS_MULTIBOOT_MAGIC + tinyos_flags))