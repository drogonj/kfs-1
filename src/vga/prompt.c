#include "../../include/kernel.h"

uint8_t prompt_enabled = 0;

void init_prompt() {
    tty_x = 0;
    tty_y = 0;
    clear_tty();
    disable_cursor();
    set_tty_color(VGA_COLOR(LIGHT_BLUE, 0));
    printk(
        "  __   ___   \n" \
        " /. | (__ \\ \n" \
        "(_  _) / _/  \n" \
        "  (_) (____)   " \
    );
    set_tty_color(VGA_COLOR(CYAN, 0));
    printk("kfs-1, a kernel from scratch\n\n");
    set_tty_color(VGA_COLOR(LIGHT_RED, 0));
    printk("$ ");
    set_tty_color(VGA_COLOR(WHITE, 0));
    enable_cursor();
    prompt_enabled = 1;
}

void prompt_newline() {
    kputchar('\n');
    set_tty_color(VGA_COLOR(LIGHT_RED, 0));
    printk("$ ");
    set_tty_color(VGA_COLOR(WHITE, 0));
}