#include "../include/kernel.h"

void kmain() {
    init_gdt();
    init_idt();
    init_pic();
    init_vga();
    init_prompt();

    asm __volatile__("sti");
    while (1);
}
