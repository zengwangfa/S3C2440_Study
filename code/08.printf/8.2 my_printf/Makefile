all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o uart.o uart.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o my_printf.o my_printf.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-gcc -c -o lib1funcs.o lib1funcs.S
	arm-linux-ld -Ttext 0 -Tdata 0xed0 start.o led.o uart.o main.o lib1funcs.o my_printf.o -o printf.elf
	arm-linux-objcopy -O binary -S printf.elf printf.bin
	arm-linux-objdump -D printf.elf > printf.dis
	rm *.o *.elf
clean:
	rm *.bin *.o *.elf *.dis
