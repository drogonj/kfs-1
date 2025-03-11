#ifndef GDT_H
# define GDT_H

# define GDT_SIZE 256
# define GDT_LOCATION 0x00000800

// https://wiki.osdev.org/Global_Descriptor_Table

// Access Flags
# define GDT_PRESENT 0x80
# define GDT_DPL0 0x00
# define GDT_DPL1 0x20
# define GDT_DPL2 0x40
# define GDT_DPL3 0x60
# define GDT_NOTSYSTEM_SEGMENT 0x10
# define GDT_EXECUTABLE 0x8
# define GDT_DC 0x4
# define GDT_WR 0x2
# define GDT_ACCESSED 0x1

// Flags
# define GDT_4KB 0x8
# define GDT_32BITS 0x4

typedef struct gdt_ptr_s {
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed)) gdt_ptr_t;

typedef struct gdt_entry_s {
    uint16_t limit_low;
    uint16_t base_low; // 0-15
    uint8_t base_high_low; // 16-23
    uint8_t access;
    uint8_t limit_high:4;
    uint8_t flags:4;
    uint8_t base_high_high; // 24-31
} __attribute__ ((packed)) gdt_entry_t;

// globals
extern gdt_entry_t gdt[GDT_SIZE];
extern gdt_ptr_t gdt_ptr;

void init_gdt_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags, gdt_entry_t * entry);
void init_gdt();

#endif