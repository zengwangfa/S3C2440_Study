all:
	arm-linux-gnueabihf-gcc -c -o led_on.o led_on.S
	arm-linux-gnueabihf-ld -Ttext 0 led_on.o -o led_on.elf
	arm-linux-gnueabihf-objcopy -O binary -S led_on.elf led_on.bin
	arm-linux-gnueabihf-objdump -D led_on.elf > led_on.dis
clean:
	rm *.bin *.o *.elf