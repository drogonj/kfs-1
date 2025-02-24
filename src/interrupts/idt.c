#include "../../include/kernel.h"

idt_entry_t idt[IDT_SIZE];
idt_ptr_t idt_ptr;

void init_idt_desc(uint16_t selector, uint32_t offset, uint16_t type, idt_entry_t * entry) {
    
}