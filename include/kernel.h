#ifndef KERNEL_H
# define KERNEL_H

# define VGA_X_SIZE 80
# define VGA_Y_SIZE 25

# include <stdint.h>
# include <stdarg.h>

# include "./libs.h"
# include "./colors.h"
# include "./idt.h"
# include "./keyboard.h"

// kernel.c
extern volatile uint16_t * vbuff;
void clear_tty();

// vga/prompt.c
extern uint8_t prompt_enabled;
void init_prompt();

// vga/cursor.c
extern uint16_t tty_x;
extern uint16_t tty_y;
void disable_cursor();
void enable_cursor();
void set_cursor_pos(uint16_t x, uint16_t y);

// vga/printk/
extern uint16_t tty_color;
void printk(const char *format, ...);
int	ft_puthex_lower(unsigned long int n, unsigned int len);
int	ft_puthex_upper(unsigned long int n, unsigned int len);
int	ft_putnbr(int n, unsigned int len);
int	ft_putunsignednbr(unsigned int n, unsigned int len);
void ft_putpointer(void *ptr);
void kputchar(char c);
void kputstr(char * str);
void set_tty_color(uint16_t color);

#endif