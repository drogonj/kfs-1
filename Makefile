BOOTLOADER = src/x86/boot.s
KERNEL = src/kernel.c \
         src/vga/cursor.c
LINKER = linker.ld

BOOTLOADER_OBJ = build/boot.o
KERNEL_OBJ = build/kernel.o \
			 build/vga/cursor.o

GCC_FLAGS = -march=i386 -m32 -ffreestanding -O2 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
LD_FLAGS = -m elf_i386
QEMU_FLAGS = -kernel

OUT = kfs-1.bin

OBJDIR = build

all: $(OUT)

$(OUT): $(BOOTLOADER_OBJ) $(KERNEL_OBJ)
	@ld $(LD_FLAGS) -T $(LINKER) -o $(OUT) $(BOOTLOADER_OBJ) $(KERNEL_OBJ)
	@printf "\033[32mBuild successful ✓\033[0m\n"

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@mkdir -p $(OBJDIR) $(OBJDIR)/vga
	@gcc $(GCC_FLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

$(OBJDIR)/%.o: src/x86/%.s | $(OBJDIR)
	@mkdir -p $(OBJDIR)
	@as -32 $< -o $@
	@echo "Assembled $< -> $@"

run: $(OUT)
	@qemu-system-i386 $(QEMU_FLAGS) $(OUT) | printf "\033[32mRunning... ✓\033[0m\n"

clean:
	@rm -rf $(OBJDIR)/*
	@echo "\033[32mCleaned ✓\033[0m"

fclean: clean
	@rm -f $(OUT)
	@echo "\033[32mFull clean ✓\033[0m"

re: fclean all

$(OBJDIR):
	@mkdir -p $(OBJDIR)

.PHONY: all build run clean fclean re
