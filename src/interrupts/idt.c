#include "../../include/kernel.h"

idt_entry_t idt[IDT_SIZE];
idt_ptr_t idt_ptr;

// see https://bitwisecmd.com/ to simulate bits operations
void init_idt_entry(uint16_t selector, uint32_t offset, uint8_t type, idt_entry_t * entry) {
    entry->isr_offset_low = (offset & 0xFFFF); // extract low part of uint32 to uint16
    entry->selector = selector;
    entry->zero = 0;
    entry->type = type;
    entry->isr_offset_high = (offset & 0xFFFF0000) >> 16; // high part

}

void init_idt() {
    idt_ptr.base = (uint32_t)&idt;
    idt_ptr.limit = IDT_SIZE * sizeof(idt_entry_t) - 1;

    for (unsigned int i = 0; i < IDT_SIZE; i++) {
        init_idt_entry(KERNEL_CS, (uint32_t)_isr_ignore, 0x8E, &idt[i]);
    }
    init_idt_entry(KERNEL_CS, (uint32_t)_isr_keyboard, 0x8E, &idt[33]);

    asm("lidt (%0)" : : "r" (&idt_ptr));
}

