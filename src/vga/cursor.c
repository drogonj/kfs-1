#include "../../include/kernel.h"

extern unsigned int tty_x;
extern unsigned int tty_y;

void disable_cursor() {
    __asm__ volatile (
        "mov $0x3D4, %%dx   \n\t"   // VGA CRT Control's port
        "mov $0x0A, %%al    \n\t"   // 0x0A register
        "out %%al, %%dx     \n\t"   // select register
        "inc %%dx           \n\t"   // 0x3D5 register (data)
        "in %%dx, %%al      \n\t"   // get datas
        "or $0x20, %%al     \n\t"   // disable cursor
        "out %%al, %%dx     \n\t"   // apply changes
        : 
        : 
        : "eax", "edx", "memory"
    );
}

void enable_cursor() {
    __asm__ volatile (
        "mov $0x3D4, %%dx   \n\t"
        "mov $0x0A, %%al    \n\t"
        "out %%al, %%dx     \n\t"
        "inc %%dx           \n\t"
        "in %%dx, %%al      \n\t"
        "andb $0xDF, %%al   \n\t"
        "out %%al, %%dx     \n\t"
        : 
        : 
        : "eax", "edx", "memory"
    );
    set_cursor_pos(tty_x, tty_y);
}

void set_cursor_pos(uint16_t x, uint16_t y) {
    uint8_t vga_x_size = VGA_X_SIZE;

    // Cursor position is located on two registers 0x0F (low part) and 0x0E (high part)
    __asm__ volatile (
        "mov %[x], %%bx     \n\t"   // offset setup -> (y * width) + x -> %bx
        "mov %[y], %%ax     \n\t"
        "mov %[width], %%dl \n\t"
        "mul %%dl           \n\t"
        "add %%ax, %%bx     \n\t"
        "                   \n\t"
        "mov $0x3D4, %%dx   \n\t"   // get 0x0F
        "mov $0x0F, %%al    \n\t"
        "out %%al, %%dx     \n\t"
        "                   \n\t"
        "inc %%dl           \n\t"   // jmp to port 0x3D5 and apply %bl(low part)
        "mov %%bl, %%al     \n\t"
        "out %%al, %%dx     \n\t"
        "                   \n\t"
        "dec %%dl           \n\t"   // return to port 0x3D4 and get 0x0E
        "mov $0x0E, %%al    \n\t"
        "out %%al, %%dx     \n\t"
        "                   \n\t"
        "inc %%dl           \n\t"   // apply %bh(high part)
        "mov %%bh, %%al     \n\t"
        "out %%al, %%dx     \n\t"
        :
        : [width] "r" (vga_x_size), [x] "r" (x), [y] "r" (y)
        : "ax", "bx", "dx", "cc", "memory"
    );
}
