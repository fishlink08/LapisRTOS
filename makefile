CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OPENOCD = openocd

CFLAGS = -mcpu=cortex-m3 -mthumb -g

PRE = bin/main.o bin/boot.o bin/context.o bin/scheduler.o

all: flash
NOFLASH: bin/firmware.elf

bin/main.o : Kernel/main.c
	$(CC) $(CFLAGS) -c Kernel/main.c -o bin/main.o

bin/boot.o : Kernel/src/boot.c
	$(CC) $(CFLAGS) -c Kernel/src/boot.c -o bin/boot.o

bin/context.o : Kernel/src/context.s
	$(CC) $(CFLAGS) -c Kernel/src/context.s -o bin/context.o

bin/scheduler.o : Kernel/src/scheduler.c
	$(CC) $(CFLAGS) -c Kernel/src/scheduler.c -o bin/scheduler.o


bin/firmware.elf : $(PRE) Kernel/linker.ld
	$(CC) $(CFLAGS) -nostdlib -nostartfiles $(PRE) -T Kernel/linker.ld -o bin/firmware.elf -IUART

bin/firmware.bin : bin/firmware.elf
	$(OBJCOPY) -O binary bin/firmware.elf bin/firmware.bin

flash: bin/firmware.elf
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program bin/firmware.bin verify reset exit"
