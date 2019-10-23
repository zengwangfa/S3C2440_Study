all:
	arm-linux-gnueabihf-gcc -c -o key_led.o key_led.c
	arm-linux-gnueabihf-gcc -c -o start.o start.S
	
	arm-linux-gnueabihf-ld -Ttext 0 start.o key_led.o -o key_led.elf
	arm-linux-gnueabihf-objcopy -O binary -S key_led.elf key_led.bin
	arm-linux-gnueabihf-objdump -D key_led.elf > key_led.dis
clean:
	rm *.bin *.o *.elf *.dis