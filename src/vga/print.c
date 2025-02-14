#include "../../include/kernel.h"

extern volatile uint16_t * vbuff;

uint16_t tty_color = 0x0F;
unsigned int tty_x = 0;
unsigned int tty_y = 0;

uint8_t map_color(const char* name) {
    if (ft_strcmp(name, "BLACK") == 0) return BLACK;
    if (ft_strcmp(name, "BLUE") == 0) return BLUE;
    if (ft_strcmp(name, "GREEN") == 0) return GREEN;
    if (ft_strcmp(name, "CYAN") == 0) return CYAN;
    if (ft_strcmp(name, "RED") == 0) return RED;
    if (ft_strcmp(name, "MAGENTA") == 0) return MAGENTA;
    if (ft_strcmp(name, "BROWN") == 0) return BROWN;
    if (ft_strcmp(name, "LIGHT_GREY") == 0) return LIGHT_GREY;
    if (ft_strcmp(name, "DARK_GREY") == 0) return DARK_GREY;
    if (ft_strcmp(name, "LIGHT_BLUE") == 0) return LIGHT_BLUE;
    if (ft_strcmp(name, "LIGHT_GREEN") == 0) return LIGHT_GREEN;
    if (ft_strcmp(name, "LIGHT_CYAN") == 0) return LIGHT_CYAN;
    if (ft_strcmp(name, "LIGHT_RED") == 0) return LIGHT_RED;
    if (ft_strcmp(name, "LIGHT_MAGENTA") == 0) return LIGHT_MAGENTA;
    if (ft_strcmp(name, "YELLOW") == 0) return YELLOW;
    if (ft_strcmp(name, "WHITE") == 0) return WHITE;
    return LIGHT_GREY;
}


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
}

// detect pattern ";;COLOR;" and change tty_color
void kputstr(char* str) {
    char* pattern_start = 0;

    if (!str) {
        return;
    }

    for (unsigned int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ';' && str[i + 1] == ';') {
            if (pattern_start == 0) {
                pattern_start = &str[i + 2];
            } else {
                char* delimiter = ft_strchr(pattern_start, ';');
                if (delimiter != 0L) {
                    *delimiter = '\0';
                    uint8_t fg = map_color(pattern_start);
                    tty_color = VGA_COLOR(fg, 0);
                    *delimiter = ';';
                }
                pattern_start = 0;
                i++;
            }
        } else if (pattern_start == 0) {
            kputchar(str[i]);
        }
    }
}

void set_tty_color(uint16_t color) {
    tty_color = color;
}