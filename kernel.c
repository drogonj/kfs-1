#include <stdint.h>

volatile uint16_t * vbuff = (uint16_t *)0xb8000; // VGA buffer, 80*25 by default
const unsigned int VGA_X_SIZE = 80;
const unsigned int VGA_Y_SIZE = 25;

void clear_term() {
    unsigned int vbuff_size = VGA_X_SIZE * VGA_Y_SIZE;

    for (unsigned int i = 0; i < vbuff_size; i++) {
        vbuff[i] = ((uint16_t)0x0F << 8) | ' ';
    }
}

void disable_cursor() {
    __asm__ volatile (
        "mov $0x3D4, %%dx\n\t"      // Port VGA CRT Control (color)
        "mov $0x0A, %%al\n\t"       // Registre 0x0A : "Cursor Start"
        "out %%al, %%dx\n\t"        // Sélectionne le registre 0x0A
        "inc %%dx\n\t"              // Port 0x3D5 (data)
        "in %%dx, %%al\n\t"         // Lit la valeur actuelle
        "or $0x20, %%al\n\t"        // Active le bit 5 (désactive le curseur)
        "out %%al, %%dx\n\t"        // Écrit la nouvelle valeur
        : 
        : 
        : "eax", "edx", "memory"   // Indique les registres modifiés
    );
}

void enable_cursor() {
    __asm__ volatile (
        "mov $0x3D4, %%dx\n\t"      // Port VGA CRT Control (color)
        "mov $0x0A, %%al\n\t"       // Registre 0x0A : "Cursor Start"
        "out %%al, %%dx\n\t"        // Sélectionne le registre 0x0A
        "inc %%dx\n\t"              // Port 0x3D5 (data)
        "in %%dx, %%al\n\t"         // Lit la valeur actuelle
        "xor $0x20, %%al\n\t"
        // "xor $0x01, %%al\n\t"    // Taille
        // "xor $0x02, %%al\n\t"
        // "xor $0x04, %%al\n\t"
        // "xor $0x08, %%al\n\t"
        "out %%al, %%dx\n\t"        // Écrit la nouvelle valeur
        : 
        : 
        : "eax", "edx", "memory"   // Indique les registres modifiés
    );
}

void kmain() {
    clear_term();
    disable_cursor();
    enable_cursor();
}
