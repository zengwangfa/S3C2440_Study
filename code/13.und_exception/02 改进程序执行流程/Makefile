all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o init.o init.c
	arm-linux-gcc -c -o uart.o uart.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o printf.o printf.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-gcc -c -o lib1funcs.o lib1funcs.S
	arm-linux-gcc -c -o exception.o exception.c
	arm-linux-ld -T sdram.lds start.o led.o uart.o main.o lib1funcs.o printf.o init.o exception.o -o und_exception.elf
	arm-linux-objcopy -O binary -S und_exception.elf und_exception.bin
	arm-linux-objdump -D und_exception.elf > und_exception.dis
	rm *.o *.elf
clean:
	rm *.bin *.o *.elf *.dis
