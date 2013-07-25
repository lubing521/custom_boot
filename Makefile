objs = start.o clock.o uart.o ddr.o nand.o boot.o
spl_objs = start.o clock.o uart.o ddr.o nand.o boot.o
CC := arm-linux-gcc
LD := arm-linux-ld
OBJCOPY := arm-linux-objcopy
CFLAGS := -fno-builtin -Wall -nostdlib

.PHONY: all
all: boot.bin spl.bin
	cat spl.bin boot.bin > my_boot.bin

boot.bin:$(objs)
	$(LD) -Tboot.lds -o boot.elf $^
	$(OBJCOPY) -O binary -S boot.elf $@
#	$(CC)objdump -D boot.elf > boot.dis

spl.bin: $(spl_objs)
	arm-linux-ld -Tboot.lds -o spl.elf $^
	arm-linux-objcopy -O binary -S spl.elf $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.S %.h
	$(CC) $(CFLAGS) -c -o $@ $<


.PHONY: clean
clean:
	-rm -f *.o *.bin *.elf *.dis
