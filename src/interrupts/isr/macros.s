
.macro SAVE_REGS
    pushal
    pushw %ds
    pushw %es
    pushw %fs
    pushw %gs
    pushl %ebx
    movw $0x10, %bx
    movw %bx, %ds
    popl %ebx
.endm

.macro RESTORE_REGS
    popw %gs
    popw %fs
    popw %es
    popw %ds
    popal
.endm

