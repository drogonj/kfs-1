#include "../include/kernel.h"
#include "../include/gdt.h"

gdt_entry_t gdt[GDT_SIZE] = {0};
gdt_ptr_t gdt_ptr = {0};

void init_gdt_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags, gdt_entry_t * entry) {
    entry->limit_low = (limit & 0xFFFF);
    entry->base_low = (base & 0xFFFF);
    entry->base_high_low = (base & 0xFF0000) >> 16;
    entry->access = access;
    entry->limit_high = (limit & 0xF0000) >> 16;
    entry->flags = flags & 0xf;
    entry->base_high_high = (base & 0xFF000000) >> 24;
}

void init_gdt() {
    // Invalid segment
    init_gdt_entry(0x0, 0x0, 0x0, 0x0, &gdt[0]);
    // Code segment
    init_gdt_entry(0, 0xFFFFF, (GDT_ACCESSED|GDT_WR|GDT_EXECUTABLE|GDT_NOTSYSTEM_SEGMENT|GDT_DPL0|GDT_PRESENT), (GDT_4KB|GDT_32BITS), &gdt[1]);
    // Data segment
    init_gdt_entry(0, 0xFFFFF, (GDT_ACCESSED|GDT_WR|GDT_NOTSYSTEM_SEGMENT|GDT_DPL0|GDT_PRESENT), (GDT_4KB|GDT_32BITS), &gdt[2]);
    // Stack segment
    init_gdt_entry(0, 0xFFFFF, (GDT_ACCESSED|GDT_WR|GDT_DC|GDT_NOTSYSTEM_SEGMENT|GDT_DPL0|GDT_PRESENT), (GDT_4KB|GDT_32BITS), &gdt[3]);

    gdt_ptr.base = (uint32_t)&gdt;
    gdt_ptr.limit = sizeof(gdt) - 1;

    for (unsigned i = 0; i <= gdt_ptr.limit; i++) {
        ((char *)gdt_ptr.base)[i] = ((char *)gdt)[i];
    }

    asm("lgdtl (gdt_ptr)");

    asm(
        "movw $0x10, %ax    \n" //Select Data segment and assign it to the following Segments registers
        "movw %ax, %ds      \n"
        "movw %ax, %es      \n"
        "movw %ax, %fs      \n"
        "movw %ax, %gs      \n"
        "ljmp $0x08, $next  \n" //load CS in Code segment and jmp to next
        "next:              \n"
    );
}