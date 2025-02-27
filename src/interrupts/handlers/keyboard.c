#include "../../../include/kernel.h"

static void kbd_delete() {
    if (tty_x <= 0) {
        if (tty_y > 0) {
            tty_y -= 1;
        }   
        tty_x = VGA_X_SIZE - 1;
        kputchar(' ');
        tty_y -= 1;
        tty_x = VGA_X_SIZE - 1;
        while ((uint8_t)(vbuff[(tty_y * VGA_X_SIZE) + (tty_x - 1)] & 0xFF) == ' ' && tty_x > 0) {
            tty_x--;
        }
    } else {
        tty_x -= 1;
        kputchar(' ');
        tty_x -= 1;
    }
    set_cursor_pos(tty_x, tty_y);
}

// up: 72 down: 80 left: 75 right: 77
static void kbd_directions(uint8_t code) {
    if (code == 72 && tty_y > 0) {
        tty_y--;
    } else if (code == 80 && tty_y < VGA_Y_SIZE - 1) {
        tty_y++;
    } else if (code == 75) {
        if (tty_x <= 0 && tty_y > 0) {
            tty_x = VGA_X_SIZE - 1;
            tty_y--;
        } else if (tty_x > 0) {
            tty_x--;
        } 
    } else if (code == 77) {
        if (tty_x >= VGA_X_SIZE - 1 && tty_y < VGA_Y_SIZE - 1) {
            tty_x = 0;
            tty_y++;
        } else if (tty_x < VGA_X_SIZE - 1) {
            tty_x++;
        } 
    }
    set_cursor_pos(tty_x, tty_y);
}



void isr_keyboard_handler(uint32_t int_num) {
    uint8_t scancode = inb(0x60);
    
    outb(0x20, 0x20);
    // printk("%d\n", scancode);
    if (scancode == 1) {
        if (prompt_enabled) {
            clear_tty();
            set_cursor_pos(0, 0);
        } else {
            init_prompt();
        }
    } else if (scancode == 28) {
        if (prompt_enabled) {
            prompt_newline();
        } else {
           kputchar('\n'); 
        } 
    } else if (scancode == 14) {
        kbd_delete();
    } else if (scancode < 128 && KBD_MAP[scancode]) {
        printk("%c", KBD_MAP[scancode]);
    } else  if (scancode == 72 || scancode == 80 || scancode == 75 || scancode == 77) {
        kbd_directions(scancode);
    }
}
