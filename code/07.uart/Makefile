all:
	arm-linux-gnueabihf-gcc -c -o led.o led.c  
	arm-linux-gnueabihf-gcc -c -o uart.o uart.c   
	arm-linux-gnueabihf-gcc -c -o main.o main.c   	
	arm-linux-gnueabihf-gcc -c -o start.o start.S   	
	arm-linux-gnueabihf-ld -Ttext 0 start.o led.o main.o uart.o -o uart.elf		  
	arm-linux-gnueabihf-objcopy -O binary -S uart.elf uart.bin 
	arm-linux-gnueabihf-objdump -D uart.elf > uart.dis         
clean:
	rm *.bin *.o *.elf *.dis
	
