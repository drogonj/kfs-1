#include "../../../include/kernel.h"

uint16_t tty_color = 0x0F;

void kputchar(char c) {
    if (c == '\n') {
        tty_x = 0;
        tty_y ++;
    } else {
        unsigned int offset = (tty_y * VGA_X_SIZE) + tty_x;
        vbuff[offset] = ((uint16_t)tty_color << 8) | c;
		tty_x ++;
    }

    if (tty_x >= VGA_X_SIZE) {
        tty_x = 0;
        tty_y ++;
    }
    if (tty_y >= VGA_Y_SIZE) {
        tty_x = 0;
        tty_y = 0;
    }
    set_cursor_pos(tty_x, tty_y);
}

void kputstr(char* str) {
    if (!str) {
        return;
    }

    for (unsigned int i = 0; str[i] != '\0'; i++) {
        kputchar(str[i]);
    }
}

void set_tty_color(uint16_t color) {
    tty_color = color;
}