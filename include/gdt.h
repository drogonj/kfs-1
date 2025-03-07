#ifndef GDT_H
# define GDT_H

# define GDT_SIZE 256
# define GDT_LOCATION 0x00000800

# define GDT_DPL
# define GDP 

// https://wiki.osdev.org/Global_Descriptor_Table

typedef struct gdt_ptr_s {
    uint16_t limite;
    uint32_t base;
} __attribute__ ((packed)) gdt_ptr_t;

typedef struct gdt_entry_s {
    uint16_t limit_low;
    uint16_t base_low; // 0-15
    uint8_t base_high_low; // 16-23
    uint8_t access;
    uint8_t flags;
    uint8_t limit_high;
    uint8_t base_high_high; // 24-31

} __attribute__ ((packed)) gdt_entry_t;

// globals
extern gdt_entry_t gdt[GDT_SIZE];
extern gdt_ptr_t gdt_ptr;

#endif