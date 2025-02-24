#ifndef IDT_H
# define IDT_H

# define IDT_SIZE 256
# define kERNEL_CS 0x08

typedef struct idt_entry_s {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero; // Always zero
    uint8_t type;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_s {
    uint16_t limite;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

extern idt_entry_t idt[IDT_SIZE];
extern idt_ptr_t idt_ptr;

#endif