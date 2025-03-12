#ifndef KERNEL_H
# define KERNEL_H

# define VGA_X_SIZE 80
# define VGA_Y_SIZE 25

# include <stdint.h>

# include "./libs.h"
# include "./colors.h"
# include "./gdt.h"
# include "./idt.h"
# include "./keyboard.h"

// vga/vga.c
extern volatile uint16_t * vbuff;
void disable_blinking();
void clear_tty();
void init_vga();

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
void pr_scroll_down();

// vga/cursor.c
extern uint16_t tty_x;
extern uint16_t tty_y;
void disable_cursor();
void enable_cursor();
void set_cursor_pos(uint16_t x, uint16_t y);
void set_cursor_shape(uint8_t start_cursor, uint8_t end_cursor);

// vga/printk.c
extern uint8_t tty_color;
void set_tty_color(uint8_t color);
void kputchar(char c);
void kputstr(char * str);
void kputhex(unsigned long int n);
void kputnbr(int n);
void kputunsignednbr(unsigned int n);
void kputpointer(void *ptr);
void printk(const char *fmt, ...);

#endif