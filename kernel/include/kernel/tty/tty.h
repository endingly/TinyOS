typedef unsigned short vga_atrributes;

#define TINYOS_VGA_BLACK 0
#define TINYOS_VGA_BLUE 1
#define TINYOS_VGA_GREEN 2
#define TINYOS_VGA_CYAN 3
#define TINYOS_VGA_RED 4
#define TINYOS_VGA_MAGENTA 5
#define TINYOS_VGA_BROWN 6
#define TINYOS_VGA_LIGHT_GREY 7
#define TINYOS_VGA_DARK_GREY 8
#define TINYOS_VGA_LIGHT_BLUE 9
#define TINYOS_VGA_LIGHT_GREEN 10
#define TINYOS_VGA_LIGHT_CYAN 11
#define TINYOS_VGA_LIGHT_RED 12
#define TINYOS_VGA_LIGHT_MAGENTA 13
#define TINYOS_VGA_LIGHT_BROWN 14
#define TINYOS_VGA_WHITE 15

/// @brief set color for terminal
/// @param fg foreground color
/// @param bg background color
void tty_set_color(vga_atrributes fg, vga_atrributes bg);

/// @brief push a char to terminal
/// @param c a char of ascii
void tty_push_char(char c);

/// @brief push a string to teriminal
/// @param str a string of ascii
void tty_push_str(char* str);

/// @brief teriminal scroll up
void tty_scroll_up();

/// @brief teriminal clear
void tty_clear();