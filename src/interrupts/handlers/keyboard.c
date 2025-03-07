#include "../../../include/kernel.h"

extern uint16_t tty_x;
extern uint16_t tty_y;

uint8_t shift_pressed = 0;
uint8_t ctrl_pressed = 0;

void kbd_change_tty_color() {
    static uint8_t select = 0xF;
    
    if (select == 0)
        select = 0x10;

    set_tty_color(shift_pressed ? VGA_COLOR(tty_color >> 4, --select) : VGA_COLOR(--select, tty_color & 0x00FF));
}

void kbd_delete() {
    if (tty_x <= 0) {
        if (tty_y <= 0 || (uint8_t)(pr_map[(tty_y-1) * VGA_X_SIZE + (VGA_X_SIZE-1)] & 0xF)) {
            return;
        }
        unsigned int currentOffset = tty_y * VGA_X_SIZE + tty_x;
        if (prompt_enabled && currentOffset <= pr_get_last_char()) {
            pr_decrement_line();
        } else {
            kputchar(' ');
        }
        tty_y -= 1;
        tty_x = VGA_X_SIZE - 1;
        while ((uint8_t)(vbuff[(tty_y * VGA_X_SIZE) + (tty_x - 1)] & 0xFF) == ' ' && tty_x > 0) {
            tty_x--;
        }
    } else {
        if ((uint8_t)(pr_map[tty_y * VGA_X_SIZE + (tty_x-1)] & 0xF)) {
            return;
        }
        unsigned int currentOffset = tty_y * VGA_X_SIZE + tty_x;
        if (prompt_enabled && currentOffset <= pr_get_last_char()) {
            pr_decrement_line();
        } else {
            tty_x -= 1;
            kputchar(' ');
        }
        tty_x -= 1;
    }
    set_cursor_pos(tty_x, tty_y);
}

// up: 72 down: 80 left: 75 right: 77
void kbd_directions(uint8_t code) {
    if (code == 72 && tty_y > 0 && !prompt_enabled) {                      // UP
        tty_y--;
    } else if (code == 80 && tty_y < VGA_Y_SIZE - 1 && !prompt_enabled) {  // DOWN
        tty_y++;
    } else if (code == 75) {                                               // LEFT
        if (tty_x <= 0 && tty_y > 0 && !(uint8_t)(pr_map[(tty_y-1) * VGA_X_SIZE + (VGA_X_SIZE-1)] & 0xF)) {
            tty_x = VGA_X_SIZE - 1;
            tty_y--;
        } else if (tty_x > 0 && !(uint8_t)(pr_map[tty_y * VGA_X_SIZE + (tty_x-1)] & 0xF)) {
            tty_x--;
        } 
    } else if (code == 77) {                                              // RIGHT
        if (tty_x >= VGA_X_SIZE - 1 && tty_y < VGA_Y_SIZE - 1) {
            if (prompt_enabled && pr_get_last_char() < tty_y * VGA_X_SIZE + tty_x) {
                return;
            }
            tty_x = 0;
            tty_y++;
        } else if (tty_x < VGA_X_SIZE - 1) {
            if (prompt_enabled && pr_get_last_char() < tty_y * VGA_X_SIZE + tty_x) {
                return;
            }
            tty_x++;
        } 
    }
    set_cursor_pos(tty_x, tty_y);
}

void isr_keyboard_handler() {
    uint8_t scancode = inb(0x60);

    //printk("%d\n", scancode);
    if (scancode == 1) {            // ESC
        if (prompt_enabled) {
            clear_tty();
            set_cursor_pos(0, 0);
        } else {
            init_prompt();
        }
    } else if (scancode == 28) {    // Enter / Return
        if (prompt_enabled) {
            pr_newline();
        } else {
           kputchar('\n'); 
        }
    } else if (scancode == 14) {    // Delete
        kbd_delete();
    } else if (scancode == 42) {    // L_Shift
        shift_pressed = 1;
    } else if (scancode == 170) {   // L_Shift unpressed
        shift_pressed = 0;
    } else if (scancode == 29) {    // L_Ctrl
        ctrl_pressed = 1;
    } else if (scancode == 157) {   // L_Ctrl unpressed
        ctrl_pressed = 0;
    } else if (scancode == 0x52){   // KEYPAD_0
        kbd_change_tty_color();
    } else if (ctrl_pressed && scancode == 0x26 && prompt_enabled) {    // CTRL + l
        clear_tty();
        init_prompt();
    } else if (scancode < 128 && KBD_MAP[scancode]) {
        if (prompt_enabled && tty_y * VGA_X_SIZE + tty_x <= pr_get_last_char()) {
            pr_increment_line();
        }
        printk("%c", shift_pressed ? KBD_MAP_SHIFT[scancode] : KBD_MAP[scancode]);
    } else  if (scancode == 72 || scancode == 80 || scancode == 75 || scancode == 77) { // Up/Left/Right/Down
        kbd_directions(scancode);
    }
    outb(0x20, 0x20); // Send EOI
}
