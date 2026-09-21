CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OPENOCD = openocd

CFLAGS = -mcpu=cortex-m3 -mthumb -g

C_SRC = \
	$(wildcard *.c) \
	$(Wildcard LapisRTOS/*.c) \
	$(wildcard LapisRTOS/Kernel/*.c) \
	$(wildcard LapisRTOS/Kernel/src/*.c) \
	$(wildcard LapisRTOS/Kernel/src/memory/*.c) \
	$(wildcard LapisRTOS/Kernel/src/scheduler/*.c)

S_SRC = \
	$(wildcard LapisRTOS/Kernel/src/*.s) \
	$(wildcard LapisRTOS/Kernel/src/scheduler/*.s)
	

C_OBJ = $(patsubst %.c,bin/%.o,$(C_SRC))
S_OBJ = $(patsubst %.s,bin/%.o,$(S_SRC))

OBJ = $(C_OBJ) $(S_OBJ)

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


bin/firmware.elf: $(OBJ) LapisRTOS/Kernel/linker.ld
	$(CC) $(CFLAGS) -nostdlib -nostartfiles $(OBJ) \
		-T LapisRTOS/Kernel/linker.ld \
		-o bin/firmware.elf


bin/firmware.bin: bin/firmware.elf
	$(OBJCOPY) -O binary bin/firmware.elf bin/firmware.bin


flash: bin/firmware.bin
	$(OPENOCD) -f interface/stlink.cfg \
		-f target/stm32f1x.cfg \
		-c "program bin/firmware.bin verify reset exit"