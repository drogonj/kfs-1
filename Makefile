KERNEL_SRC = $(shell find src -name '*.c') $(shell find src -name '*.s')
LIB_SRC =  $(shell find lib -name '*.c')

LINKER = linker.ld

KERNEL_OBJ = $(patsubst src/%.c, build/%.o, $(filter %.c,$(KERNEL_SRC))) \
             $(patsubst src/%.s, build/%.o, $(filter %.s,$(KERNEL_SRC)))
LIB_OBJ = $(patsubst lib/%.c, build/lib/%.o, $(LIB_SRC))

GCC_FLAGS = -g -march=i386 -m32 -ffreestanding -O2 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
LD_FLAGS = -g -m elf_i386
QEMU_FLAGS = -kernel

OUT = kfs-1.bin

OBJDIR = build

all: $(OUT)

$(OUT): $(KERNEL_OBJ) $(LIB_OBJ)
	@ld $(LD_FLAGS) -T $(LINKER) -o $@ $^
	@printf "\033[32mBuild successful ✓\033[0m\n"

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@gcc $(GCC_FLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

$(OBJDIR)/lib/%.o: lib/%.c
	@mkdir -p $(dir $@)
	@gcc $(GCC_FLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

$(OBJDIR)/%.o: src/%.s
	@mkdir -p $(dir $@)
	@as -32 $< -o $@
	@echo "Assembled $< -> $@"

run r: $(OUT)
	@qemu-system-i386 $(QEMU_FLAGS) $(OUT)
	@printf "\033[32mRunning... ✓\033[0m\n"

debug rd: $(OUT)
	@qemu-system-i386 $(QEMU_FLAGS) $(OUT) -s -S &
	@printf "\033[32mRunning... ✓\033[0m\n"
	@gdb -ex "target remote :1234" $(OUT)

clean:
	@rm -rf $(OBJDIR)/*
	@echo "\033[32mCleaned ✓\033[0m"

fclean: clean
	@rm -f $(OUT)
	@echo "\033[32mFull clean ✓\033[0m"

re: fclean all

rr: re run

rrd: re debug

.PHONY: all run clean fclean re rr rrd r
