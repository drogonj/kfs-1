#include "../../../include/kernel.h"

void isr_default_handler(uint32_t int_num) {
    uint8_t scancode = inb(0x60);
    
    outb(0x20, 0x20);
    if (scancode == 1 || scancode == 129) {
        clear_term();
        set_cursor_pos(0, 0);
    } else if (scancode == 28) {
        kputchar('\n');
    } else if (scancode == 14) {
        if (tty_x <= 0) {
            if (tty_y > 0) {
                tty_y -= 1;
            }   
            tty_x = VGA_X_SIZE - 1;
            kputchar(' ');
            tty_x = VGA_X_SIZE - 1;
            tty_y -= 1;
        } else {
            tty_x -= 1;
            kputchar(' ');
            tty_x -= 1;
        }
        set_cursor_pos(tty_x, tty_y);
    } else if (scancode <= 128) {
        printk("%c", scancode);
    } else {

    }
}
