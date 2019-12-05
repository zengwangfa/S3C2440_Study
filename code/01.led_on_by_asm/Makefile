all:
	arm-linux-gnueabihf-gcc -c -o led_on.o led_on.S                #编译
	arm-linux-gnueabihf-ld -Ttext 0 led_on.o -o led_on.elf		   #链接
 	arm-linux-gnueabihf-objcopy -O binary -S led_on.elf led_on.bin #生成bin文件
	arm-linux-gnueabihf-objdump -D led_on.elf > led_on.dis         #反汇编
clean:
	rm *.bin *.o *.elf
	
