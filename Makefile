BOOTLOADER = boot.s
KERNEL = kernel.c
LINKER = linker.ld

BOOTLOADER_OBJ = boot.o
KERNEL_OBJ = kernel.o

GCC_FLAGS = -march=i386 -m32 -ffreestanding -O2 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
LD_FLAGS = -m elf_i386
QEMU_FLAGS = -kernel

OUT = kfs-1.bin

all: build

build: 
	@gcc ${GCC_FLAGS} -c ${BOOTLOADER} -o ${BOOTLOADER_OBJ}
	@gcc ${GCC_FLAGS} -c ${KERNEL} -o ${KERNEL_OBJ}
	@ld ${LD_FLAGS} -T linker.ld -o ${OUT} ${BOOTLOADER_OBJ} ${KERNEL_OBJ}
	@printf "\033[32m Builded ✓ \033[0m\n"

run: build
	@qemu-system-i386 ${QEMU_FLAGS} ${OUT} | printf "\033[32m Running \033[0m\n"

clean:
	@rm -f ${BOOTLOADER_OBJ} ${KERNEL_OBJ}
	@printf "\033[32m Cleaned ✓ \033[0m\n"

fclean: clean
	@rm -f ${OUT}

re: fclean all

.PHONY: all build run clean fclean re