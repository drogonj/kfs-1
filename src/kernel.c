#include "../include/kernel.h"

volatile uint16_t * vbuff = (uint16_t *)0xb8000; // VGA buffer, 80*25 by default

void clear_tty() {
    unsigned int vbuff_size = VGA_X_SIZE * VGA_Y_SIZE;

    for (unsigned int i = 0; i < vbuff_size; i++) {
        vbuff[i] = ((uint16_t)0x0F << 8) | ' ';
    }
    prompt_enabled = 0;
}

void kmain() {
    init_idt();
    init_pic();
    init_prompt();

    asm __volatile__("sti");
    while (1);
}
