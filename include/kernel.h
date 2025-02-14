#ifndef KERNEL_H
# define KERNEL_H

# define VGA_X_SIZE 80
# define VGA_Y_SIZE 25

# include <stdint.h>

# include "./colors.h"

// vga/cursor.c
void disable_cursor();
void enable_cursor();
void set_cursor_pos(uint16_t x, uint16_t y);

// vga/print.c
void kputchar(char c);
void kputstr(char * str);
void set_tty_color(uint16_t color);

// lib
char *ft_strchr(const char *s, int c);
int	ft_strcmp(const char *s1, const char *s2);
unsigned int ft_strlen(const char *s);

#endif