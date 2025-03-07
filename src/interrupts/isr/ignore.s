.include "src/interrupts/isr/macros.s"

.globl _isr_ignore
_isr_ignore:
    SAVE_REGS
    cld
    mov $0x20, %al
    outb %al, $0x20
    RESTORE_REGS
    iret
