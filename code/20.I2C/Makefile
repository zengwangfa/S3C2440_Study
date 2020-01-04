objs = start.o init.o nand_flash.o uart.o main.o interrupt.o led.o uart.o printf.o string_utils.o lib1funcs.o


objs += lcd/lcd_controller.o
objs += lcd/s3c2440_lcd_controller.o
objs += lcd/lcd_4.3.o
objs += lcd/lcd.o
objs += lcd/lcd_test.o
objs += lcd/font.o
objs += lcd/framebuffer.o
objs += lcd/geometry.o
objs += lcd/font_8x16.o

objs += i2c/at24cxx.o
objs += i2c/i2c_controller.o
objs += i2c/i2c_test.o
objs += i2c/s3c2440_i2c_controller.o

all: $(objs)
	arm-linux-ld -T sdram.lds $^ libgcc.a -o project.elf
	arm-linux-objcopy -O binary -S project.elf project.bin
	arm-linux-objdump -D project.elf > project.dis
	rm -f *.o *.elf
	rm -f lcd/*.o
	rm -f i2c/*.o
clean:
	rm -f *.bin *.o *.elf *.dis

%.o: %.c
	arm-linux-gcc -mcpu=arm9tdmi -c -o $@ $<
%.o: %.S
	arm-linux-gcc -mcpu=arm9tdmi -c -o $@ $<
