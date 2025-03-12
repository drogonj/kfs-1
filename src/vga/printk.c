#include "../../include/kernel.h"

uint8_t tty_color = 0x0F;

void set_tty_color(uint8_t color) {
    tty_color = color;
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
        if (prompt_enabled) {
            pr_scroll_down();
        } else {
            tty_y = 0;
            tty_x = 0;
        }
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

void kputhex(unsigned long int n)
{
	const char base[17] = "0123456789abcdef";

	if (n >= 16)
	{
		kputhex(n / 16);
		kputhex(n % 16);
	}
	else
	{
		kputchar(base[n]);
	}
}

void kputnbr(int n)
{
	unsigned int un;

	if (n < 0)
	{
        kputchar('-');
		un = -n;
	}
	else
		un = n;
	while (un > 9)
	{
		kputnbr(un / 10);
		un %= 10;
	}
    kputchar(un + '0');
}

void kputunsignednbr(unsigned int n)
{
	while (n > 9)
	{
		kputnbr(n / 10);
		n %= 10;
	}
    kputchar(n + '0');
}

void kputpointer(void *ptr)
{
	kputstr("0x");
	kputhex((unsigned long int)(ptr));
}

void printk(const char *fmt, ...) {
    unsigned int *args = (unsigned int *)&fmt;
    args++;

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 'd': {
                    int value = *(int *)args;
                    kputnbr(value);
                    args++;
                    break;
                }
				case 'u': {
					unsigned int value = *(int *)args;
					kputunsignednbr(value);
					args++;
					break;
				}
                case 'c': {
                    char value = *(char *)args;
                    kputchar(value);
                    args++;
                    break;
                }
                case 's': {
                    char *value = *(char **)args;
                    kputstr(value);
                    args++;
                    break;
                }
				case 'x': {
					char value = *(char *)args;
					kputhex(value);
					args++;
					break;
				}
				case 'p': {
					void *value = (void *)(*args);
					kputpointer(value);
					args++;
					break;
				}
                default:
                    kputchar('%');
                    kputchar(*fmt);
                    break;
            }
        } else {
            kputchar(*fmt);
        }
        fmt++;
    }
}
