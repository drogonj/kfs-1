#include "../../include/kernel.h"

gdt_entry_t gdt[GDT_SIZE];
gdt_ptr_t gdt_ptr;

void init_gdt_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags, gdt_entry_t * entry) {
    entry->limit_low = (limit & 0xFFFF);
    entry->base_low = (base & 0xFFFF);
    entry->base_high_low = (base & 0xFF0000) >> 16;
    entry->access = access;
    entry->flags = flags;
    entry->limit_high = (limit & 0xFFFF0000) >> 16;
    entry->base_high_high = (limit & 0xFFFFFF00) >> 8;
}
