#pragma once

#define SD_TYPE(x)      (x << 8)   // [TYPE] Segment type
#define SD_CODE_DATA(x) (x << 12)  // [S] Descriptor type (0 = system, 1 = code/data)
#define SD_DPL(x)       (x << 13)  // [DPL] Descriptor privilege level
#define SD_P(x)         (x << 15)  // [P] Segment present
#define SD_AVL(x)       (x << 20)  // [AVL] Available for system use
#define SD_L(x)         (x << 21)  // [L] Long mode
#define SD_D_B(x)       (x << 22)  // [D/B] Default operation size (0 = 16-bit, 1 = 32-bit)
#define SD_G(x)         (x << 23)  // [G] Granularity

#define SD_LIM_LOW(x)   (x & 0xFFFF)
#define SD_LIM_HIGH(x)  (x & 0xF0000)
#define SD_BASE_LOW(x)  ((x & 0xFFFF) << 16)
#define SD_BASE_MID(x)  (x & 0xFF0000)
#define SD_BASE_HIGH(x) (x & 0xFF000000)

#define SD_DATA_RD        0x00  // Read-Only
#define SD_DATA_RDA       0x01  // Read-Only, accessed
#define SD_DATA_RDWR      0x02  // Read/Write
#define SD_DATA_RDWRA     0x03  // Read/Write, accessed
#define SD_DATA_RDEXPD    0x04  // Read-Only, expand-down
#define SD_DATA_RDEXPDA   0x05  // Read-Only, expand-down, accessed
#define SD_DATA_RDWREXPD  0x06  // Read/Write, expand-down
#define SD_DATA_RDWREXPDA 0x07  // Read/Write, expand-down, accessed
#define SD_CODE_EX        0x08  // Execute-Only
#define SD_CODE_EXA       0x09  // Execute-Only, accessed
#define SD_CODE_EXRD      0x0A  // Execute/Read
#define SD_CODE_EXRDA     0x0B  // Execute/Read, accessed
#define SD_CODE_EXC       0x0C  // Execute-Only, conforming
#define SD_CODE_EXCA      0x0D  // Execute-Only, conforming, accessed
#define SD_CODE_EXRDC     0x0E  // Execute/Read, conforming
#define SD_CODE_EXRDCA    0x0F  // Execute/Read, conforming, accessed

#define GDT_CODE_PL0                                                                    \
  SD_TYPE(SD_CODE_EXRD) | SD_CODE_DATA(1) | SD_DPL(0) | SD_P(1) | SD_AVL(0) | SD_L(0) | \
      SD_D_B(1) | SD_G(1)

#define GDT_DATA_PL0                                                                    \
  SD_TYPE(SD_DATA_RDWR) | SD_CODE_DATA(1) | SD_DPL(0) | SD_P(1) | SD_AVL(0) | SD_L(0) | \
      SD_D_B(1) | SD_G(1)

#define GDT_CODE_PL3                                                                    \
  SD_TYPE(SD_CODE_EXRD) | SD_CODE_DATA(1) | SD_DPL(3) | SD_P(1) | SD_AVL(0) | SD_L(0) | \
      SD_D_B(1) | SD_G(1)

#define GDT_DATA_PL3                                                                    \
  SD_TYPE(SD_DATA_RDWR) | SD_CODE_DATA(1) | SD_DPL(3) | SD_P(1) | SD_AVL(0) | SD_L(0) | \
      SD_D_B(1) | SD_G(1)

/// @brief 初始化 GDT
void _init_gdt();