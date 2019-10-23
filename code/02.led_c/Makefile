all:
	arm-linux-gnueabihf-gcc -c -o led_on.o led_on.c
	arm-linux-gnueabihf-gcc -c -o start.o start.S
	
	arm-linux-gnueabihf-ld -Ttext 0 start.o led_on.o -o led.elf
	arm-linux-gnueabihf-objcopy -O binary -S led.elf led.bin
	arm-linux-gnueabihf-objdump -D led.elf > led.dis
clean:
	rm *.bin *.o *.elf *.dis