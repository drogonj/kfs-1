#ifndef KERNEL_H
# define KERNEL_H

# define VGA_X_SIZE 80
# define VGA_Y_SIZE 25

# include <stdint.h>

// cursor.c
void disable_cursor();
void enable_cursor();
void set_cursor_pos(uint16_t x, uint16_t y);

#endif