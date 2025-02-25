#include <stdint.h>

// Send a byte to an In/Out port
void outb(uint32_t port, uint8_t value) {
    asm __volatile__ (
        "outb %%al, %%dx"
        :
        : "d" (port), "a" (value)
    );
}

// Get a byte from an In/Out port and return it
uint8_t inb(uint32_t port) {
    uint8_t value;
    asm __volatile__ (
        "inb %%dx, %%al"
        : "=a" (value)
        : "d" (port)
    );
    return value;
}

// For 2 bytes word
void outw(uint32_t port, uint16_t value) {
    asm __volatile__ (
        "outw %%ax, %%dx"
        :
        : "d" (port), "a" (value)
    );
}

uint16_t inw(uint32_t port) {
    uint16_t value;
    asm __volatile__ (
        "inw %%dx, %%ax"
        : "=a" (value)
        : "d" (port)
    );
    return value;
}

// For 4 bytes word
void outl(uint32_t port, uint32_t value) {
    asm __volatile__ (
        "outl %%eax, %%dx"
        :
        : "d" (port), "a" (value)
    );
}

uint32_t inl(uint32_t port) {
    uint32_t value;
    asm __volatile__ (
        "inl %%dx, %%eax"
        : "=a" (value)
        : "d" (port)
    );
    return value;
}