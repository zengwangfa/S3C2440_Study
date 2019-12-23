

all: start.o led.o uart.o main.o init.o interrupt.o nor_flash.o printf.o string_utils.o lib1funcs.o
	arm-linux-ld -T sdram.lds $^ -o project.elf
	arm-linux-objcopy -O binary -S project.elf project.bin
	arm-linux-objdump -D project.elf > project.dis
	rm *.o *.elf
clean:
	rm *.bin *.o *.elf *.dis
%.o: %.c
	arm-linux-gcc -c -o $@ $<
%.o: %.S
	arm-linux-gcc -c -o $@ $<