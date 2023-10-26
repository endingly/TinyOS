#pragma once
// 设置 CPU 特权等级、使能描述符、设置门类型(16位中断门)
#define IDT_ATTR(dpl) ((0x70 << 8) | (dpl & 3) << 13 | 1 << 15)

/// @brief 初始化 IDT
void _init_idt();
