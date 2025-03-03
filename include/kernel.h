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
extern uint8_t pr_map[];
void init_prompt();
void pr_newline();
void pr_add_char_param(unsigned int offset, uint8_t param);
void pr_remove_char_param(unsigned int offset, uint8_t param);
uint32_t pr_get_last_char();
void pr_decrement_line();
void pr_increment_line();

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