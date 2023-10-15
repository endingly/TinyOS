#pragma once

#define SD_TYPE(x)      (x << 8)
#define SD_CODE_DATA(x) (x << 12)
#define SD_DPL(x)       (x << 13)
#define SD_P(x)         (x << 15)
#define SD_AVL(x)       (x << 20)
#define SD_L(x)         (x << 21)
#define SD_D_B(x)       (x << 22)
#define SD_G(x)         (x << 23)

#define SD_LIM_LOW(x)  (x & 0xFFFF)
#define SD_LIM_HIGH(x) (x & 0xF0000)
