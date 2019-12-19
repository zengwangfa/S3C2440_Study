all: start.o led.o uart.o main.o init.o printf.o lib1funcs.o exception.o
	arm-linux-ld -T sdram.lds $^ -o swi_exception.elf
	arm-linux-objcopy -O binary -S swi_exception.elf swi_exception.bin
	arm-linux-objdump -D swi_exception.elf > swi_exception.dis
	rm *.o *.elf
clean:
	rm *.bin *.o *.elf *.dis
%.o: %.c
	arm-linux-gcc -c -o $@ $<
%.o: %.S
	arm-linux-gcc -c -o $@ $<