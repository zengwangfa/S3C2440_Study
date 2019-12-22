all: start.o led.o uart.o main.o init.o interrupt.o
	arm-linux-ld -T sdram.lds $^ -o eint.elf
	arm-linux-objcopy -O binary -S eint.elf eint.bin
	arm-linux-objdump -D eint.elf > eint.dis
	rm *.o *.elf
clean:
	rm *.bin *.o *.elf *.dis
%.o: %.c
	arm-linux-gcc -c -o $@ $<
%.o: %.S
	arm-linux-gcc -c -o $@ $<