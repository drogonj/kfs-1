.extern kmain
.global start
 
.set MB_MAGIC, 0x1BADB002
.set MB_FLAGS, (1 << 0) | (1 << 1)
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))
 
.section .multiboot
	.align 4
	.long MB_MAGIC
	.long MB_FLAGS
	.long MB_CHECKSUM
 
.section .bss
	.align 16
	stack_bottom:
		.skip 16384
	stack_top:
 
.section .text
	start:
		mov $stack_top, %esp
		cli
        call kmain
		hlt
