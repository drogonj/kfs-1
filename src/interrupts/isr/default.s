.include "src/interrupts/isr/macros.s"

.globl _isr_default
_isr_default:
    SAVE_REGS
    call isr_default_handler
    movb $0x20, %al
    outb %al, $0x20
    RESTORE_REGS
    iret
