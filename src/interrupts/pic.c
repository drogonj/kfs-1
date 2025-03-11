#include "../../include/kernel.h"

// https://github.com/littleosbook/littleosbook/blob/master/interrupts.md contain Interrupts mask list

void init_pic(void) {
    // ICW1
    outb(0x20, 0x1B);
    outb(0xA0, 0x1B);

    // ICW2
    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    // ICW3
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    // ICW4
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // Mask interrupts (except Keyboard)
    outb(0x21, 0xFD);
    outb(0xA1, 0xFF);
}
