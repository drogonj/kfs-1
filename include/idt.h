#ifndef IDT_H
# define IDT_H

# define IDT_SIZE 256
# define KERNEL_CS 0x08 // Kernel code segment (see GDT)

// https://wiki.osdev.org/Interrupt_Descriptor_Table

typedef struct idt_entry_s {
    uint16_t isr_offset_low;
    uint16_t selector;
    uint8_t zero; // Always zero
    uint8_t type;
    uint16_t isr_offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_s {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

// globals
extern idt_entry_t idt[IDT_SIZE];
extern idt_ptr_t idt_ptr;

// pic.c
void init_pic(void);

// idt.c
void init_idt_entry(uint16_t selector, uint32_t offset, uint8_t type, idt_entry_t * entry);
void init_idt();

// isr/
void _isr_keyboard();
void _isr_ignore();

// handlers/
void isr_keyboard_handler();


#endif