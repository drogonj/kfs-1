#include "../../include/kernel.h"

uint8_t prompt_enabled = 0;

uint8_t pr_map[VGA_X_SIZE * VGA_Y_SIZE] = {0}; // A map to add some info for each block of the prompt
                                               // 0000 0000
                                               //         + Static Character (0: no 1: yes)

void init_prompt() {
    tty_x = 0;
    tty_y = 0;
    for (unsigned int i = 0; i < VGA_X_SIZE * VGA_Y_SIZE; i++) {
        pr_map[i] = 0;
    }
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
    printk("kfs-1, a kernel from scratch\n");
    pr_newline();
    enable_cursor();
    prompt_enabled = 1;
}

void pr_newline() {
    kputchar('\n');
    set_tty_color(VGA_COLOR(LIGHT_RED, 0));
    printk("$ ");
    set_tty_color(VGA_COLOR(WHITE, 0));
    pr_add_char_param(tty_y * VGA_X_SIZE + (tty_x - 1), 0x1);
}

void pr_add_char_param(unsigned int offset, uint8_t param) {
    pr_map[offset] |= param;
}

void pr_remove_char_param(unsigned int offset, uint8_t param) {
    pr_map[offset] &= (~param); 
}

uint8_t pr_char_contain_param(unsigned int x, unsigned int y, uint8_t param) {
    unsigned int offset = y * VGA_X_SIZE + x;
    if (pr_map[offset] & param) {
        return (1);
    } else {
        return (0);
    }
}

uint32_t pr_get_last_char() {
    unsigned int i = VGA_X_SIZE * VGA_Y_SIZE - 1;

    for (; i >= 0; i--) {
        if ((uint8_t)(vbuff[i] & 0xFF) != ' ' || i == 0) {
            break;
        }
    }
    return (i);
}

void pr_decrement_line() {
    unsigned int offset = tty_y * VGA_X_SIZE + tty_x;
    unsigned int last = pr_get_last_char();

    for (unsigned int i = offset - 1; i <= last; i++) {
        vbuff[i] = (uint16_t)(vbuff[i+1]);
    }
}

void pr_increment_line() {
    unsigned int offset = tty_y * VGA_X_SIZE + tty_x;
    unsigned int last = pr_get_last_char();

    for (unsigned int i = last; i >= offset; i--) {
        if (last >= VGA_X_SIZE * VGA_Y_SIZE - 1) {
            pr_scroll_down();
            last-=VGA_X_SIZE;
        }
        vbuff[i + 1] = (uint16_t)(vbuff[i]);
    }
}

void pr_scroll_down() {
    unsigned int i = 0;

    while (i < VGA_X_SIZE * (VGA_Y_SIZE - 1)) {
        vbuff[i] = (uint16_t)(vbuff[i + VGA_X_SIZE]);
        i++;
    }
    while (i < VGA_X_SIZE * VGA_Y_SIZE) {
        vbuff[i] = (0x0F << 8) | ' ';
        i++;
    }
    tty_y--;
}
