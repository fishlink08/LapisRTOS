CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OPENOCD = openocd

CFLAGS = -mcpu=cortex-m4 -mthumb -g -Ikernel/include

EXAMPLES_SRC = \
	$(wildcard examples/basic/*.c)

DEBUG_SRC = \
	$(wildcard debug_tools/*.c)

C_SRC = \
	$(wildcard *.c) \
	$(wildcard kernel/*.c) \
	$(wildcard kernel/src/*.c) \
	$(wildcard kernel/src/memory/*.c) \
	$(wildcard kernel/src/scheduler/*.c)

S_SRC = \
	$(wildcard kernel/src/*.s) \
	$(wildcard kernel/src/scheduler/*.s)
	

EXAMPLES_OBJ = $(patsubst %.c,bin/%.o,$(EXAMPLES_SRC))
DEBUG_OBJ = $(patsubst %.c,bin/%.o,$(DEBUG_SRC))
C_OBJ = $(patsubst %.c,bin/%.o,$(C_SRC))
S_OBJ = $(patsubst %.s,bin/%.o,$(S_SRC))

OBJ = $(EXAMPLES_OBJ) $(DEBUG_OBJ) $(C_OBJ) $(S_OBJ)

all: flash
NOFLASH: bin/firmware.elf


# Compile C
bin/%.o: %.c
	@if not exist "$(subst /,\,$(@D))" mkdir "$(subst /,\,$(@D))"
	$(CC) $(CFLAGS) -c $< -o $@

# Compile assembly
bin/%.o: %.s
	@if not exist "$(subst /,\,$(@D))" mkdir "$(subst /,\,$(@D))"
	$(CC) $(CFLAGS) -c $< -o $@


bin/firmware.elf: $(OBJ) kernel/linker.ld
	$(CC) $(CFLAGS) -nostdlib -nostartfiles $(OBJ) \
		-T kernel/linker.ld \
		-o bin/firmware.elf


bin/firmware.bin: bin/firmware.elf
	$(OBJCOPY) -O binary bin/firmware.elf bin/firmware.bin


flash: bin/firmware.bin
	$(OPENOCD) -f interface/stlink.cfg \
		-f target/stm32f1x.cfg \
		-c "program bin/firmware.bin verify reset exit"