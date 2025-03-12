#include "../../include/kernel.h"

volatile uint16_t * vbuff = (uint16_t *)0xb8000; // VGA buffer, 80*25 by default

void clear_tty() {
    unsigned int vbuff_size = VGA_X_SIZE * VGA_Y_SIZE;

    for (unsigned int i = 0; i < vbuff_size; i++) {
        vbuff[i] = ((uint16_t)0x0F << 8) | ' ';
    }
    prompt_enabled = 0;
}

// Make blinking bit in VGABuff a background bit allowing bg to have 16 colors instead of 8
void disable_blinking() {
    (void)inb(0x3DA); // mandatory before updating 0x3C0
    outb(0x3C0, 0x10);
    outb(0x3C0, inb(0x3C1) & 0xF7);
    outb(0x3C0, 0x20);
}

void init_vga() {
    clear_tty();
    disable_blinking();
}