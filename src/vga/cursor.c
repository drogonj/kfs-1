#include "../../include/kernel.h"

uint16_t tty_x = 0;
uint16_t tty_y = 0;

// void disable_cursor() {
//     __asm__ volatile (
//         "mov $0x3D4, %%dx   \n\t"   // VGA CRT Control's port
//         "mov $0x0A, %%al    \n\t"   // 0x0A register
//         "out %%al, %%dx     \n\t"   // select register
//         "inc %%dx           \n\t"   // 0x3D5 register (data)
//         "in %%dx, %%al      \n\t"   // get datas
//         "or $0x20, %%al     \n\t"   // disable cursor
//         "out %%al, %%dx     \n\t"   // apply changes
//         : 
//         : 
//         : "eax", "edx", "memory"
//     );
// }

void disable_cursor() {
    outb(0x3D4, 0x0A);
    uint8_t val = inb(0x3D5);
    outb(0x3D5, 0x20 | val);
}

void enable_cursor() {
    outb(0x3D4, 0x0A);
    uint8_t val = inb(0x3D5);
    outb(0x3D5, 0xDF & val);
    outb(0x3D4, 0x0B);
    val = inb(0x3D5);
    outb(0x3D5, 0xDF & val);
    set_cursor_pos(tty_x, tty_y);
}

// Cursor position is located on two single byte's registers 0x0F (low part) and 0x0E (high part)
void set_cursor_pos(uint16_t x, uint16_t y) {
    uint16_t offset = (y * VGA_X_SIZE) + x;
    tty_x = x;
    tty_y = y;
    outb(0x3D4, 0x0F);
    outb(0x3D5, offset & 0xFF);
    outb(0x3D4, 0x0E);
    outb(0x3D5, (offset >> 8) & 0xFF);
}

void set_cursor_shape(uint8_t start_cursor, uint8_t end_cursor) {
    if (start_cursor > 15 || end_cursor > 15)
        return;
        
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | start_cursor);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | end_cursor);
}
