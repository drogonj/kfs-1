.include "src/interrupts/isr/macros.s"

.globl _isr_keyboard
_isr_keyboard:
    SAVE_REGS
    cld
    call isr_keyboard_handler
    RESTORE_REGS
    iret
