#include "../include/kernel.h"

volatile uint16_t * vbuff = (uint16_t *)0xb8000; // VGA buffer, 80*25 by default

void clear_term() {
    unsigned int vbuff_size = VGA_X_SIZE * VGA_Y_SIZE;

    for (unsigned int i = 0; i < vbuff_size; i++) {
        vbuff[i] = ((uint16_t)0x0F << 8) | ' ';
    }
}

void kmain() {
    clear_term();
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
}
