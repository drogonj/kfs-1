.include "src/interrupts/isr/macros.s"

.globl _isr_keyboard
_isr_keyboard:
    SAVE_REGS
    call isr_keyboard_handler
    movb $0x20, %al
    outb %al, $0x20
    RESTORE_REGS
    iret
