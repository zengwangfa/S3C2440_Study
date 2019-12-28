#include "s3c2440_soc.h"
#include "uart.h"
#include "printf.h"

//Nor Flash 地址线21：即可访问2M内存，`0x1FFFFF`，其范围地址为 0~0x1FFFFF
#define NOR_FLASH_BASE 0 /* Nor Flash基地址 nor-->cs0,base_addr = 0 */

/*===============================基本函数=================================================*/	
/* Nor Flash写入一个字
 * 基地址：base，偏移地址：offset，写入的值：value
 * eg: 55 98
 * 往(0 + (0x55)<<1 )写入0x98
*/
void nor_write_word(unsigned int base,unsigned int offset,unsigned short value)
{
	volatile unsigned short *p = (volatile unsigned short *) (base + offset<<1);
	*p = value;
}

//offset是基于nor的角度看到的地址
void nor_cmd(unsigned int offset,unsigned short cmd)
{
	nor_write_word(NOR_FLASH_BASE, offset, cmd);
}


/* Nor Flash读取一个字
 * 基地址：base，偏移地址：offset
 * eg: 55 98
 * 往(0 + (0x55)<<1 )写入0x98
*/
unsigned int nor_read_word(unsigned int base,unsigned int offset)
{
	volatile unsigned short *p = (volatile unsigned short *) (base + offset<<1);
	return *p;
}

unsigned int nor_dat(unsigned int offset)
{
	return nor_read_word(NOR_FLASH_BASE, offset);
}

/*===============================模式函数封装==============================================*/	

/* 进入CFI Mode */
void nor_enter_cfi_mode(void)
{
	nor_cmd(0x55,0x98); 
}

/* 复位模式 */
void nor_reset_mode(void)
{
	nor_cmd(0x00,0xF0);//复位(任何地址写入f0)
}

/* 解锁模式 */
void nor_unlock(void)
{
	nor_cmd(0x555,0xAA);
	nor_cmd(0x2AA,0x55);//解锁
}
/*================================应用函数封装============================================*/	
//等待读取或擦除完毕
void wait_ready(unsigned int addr)
{
	unsigned int pre_val;//上一次的值
	unsigned int cur_val;

	pre_val = nor_dat(addr>>1);
	cur_val = nor_dat(addr>>1);

	/* 两次读取的结果不一致，说明数据还在变化，继续等待 */
	while((cur_val & (1<<6) != (pre_val &(1<<6)))){//当前的Q6不等于上一次的Q6则等待
		pre_val = cur_val;//更新上一次的值
		val = nor_dat(addr>>1);//重新获取
	}
}

/* 进入NOR FLASH的CFI模式
 * 读取基本信息
 */
void scan_nor_flash(void)
{
	char str[4];
	unsigned int i,j,cnt;
	unsigned int manifa_id,device_id;//厂家ID、设备ID
	unsigned int regions; //region数量
	unsigned int nor_size;//nor flash总大小
	unsigned int region_info_base; //region基址
	unsigned int blocks,block_addr,block_size;//block数量、每个扇区的首地址、大小

	/* 1.打印 Manifacture ID、Device ID */
	nor_unlock();       //解锁
	nor_cmd(0x555,0x90);//读命令
	manifa_id = nor_dat(0x00); //读厂家ID
	device_id = nor_dat(0x01); //读设备ID
	nor_reset_mode(); //复位

	/* 2.进入CFI Mode */
	nor_enter_cfi_mode();

	/* 3.打印容量 */
	nor_size = 1<<(nor_dat(0x27));//获取nor总大小 2^n
	printf("Manifacture ID:0x%x, Device ID:0x%x,nor size = 0x%x, %dM, ",manifa_id,device_id,nor_size,nor_size>>20);
	cnt = 0;


	/* 4.打印各个扇区的起始地址 */

	/* erase block region :里面含有1个或多个block，它们大小都一样
     * 一个nor含有1个或多个region
     * 一个region含有1个或多个block(扇区)
     *
     * Erase block region information:
     * 低2字节+1：表示该region有多少个block
     * 高2字节*256：表示该block的大小(bytes)
     */
	regions = nor_dat(0x2C); //获得regions数量
	printf("regions:%d\r\n",regions);

	region_info_base = 0x2D;
	block_addr = 0;
	for(i = 0;i < regions; i++){

		/* 获取block的数量和大小 */
		blocks = 1 + nor_dat(region_info_base) + (nor_dat(region_info_base+1)<<8);//低2字节，获取block数量
		block_size = 256 * (nor_dat(region_info_base+2) + (nor_dat(region_info_base+3)<<8));//高2字节，获取block大小
		region_info_base += 4;//region读取的基址+4

		/* 打印每个block的起始地址 */
		for(j = 0;j < blocks; j++){
			printf("0x%08x ",block_addr);
			block_addr += block_size;
			if( ((++cnt) % 5) == 0){ //每打印5个换行
				printf("\r\n");
			}
		}
	}

	/* 5.退出CFI Mode */
	nor_reset_mode();//复位

}


void erase_nor_flash(void)
{
	unsigned int addr;
	/* 获得地址*/
	printf("Enter the address of sector to erase:");
	addr = get_uint();
	printf("Erase...\r\n");

	nor_unlock();
	nor_cmd(0x555,0x80); //擦除扇区命令

	nor_unlock(); 
	nor_cmd(addr>>1,0x30); //发出扇区地址
	wait_ready(addr);
}

void write_nor_flash(void)
{
	int i = 0;
	unsigned int addr,data;
	unsigned char str[50];
	/* 获得地址*/
	printf("Enter the address of sector to write:");
	addr = get_uint();
    /* 获得要写入的数据 */
	printf("Enter the string to write:");
	gets(str);
	printf("Writing...\r\n");

	/* str[0],str[1]-->16bit 构造一个16bit的数据在写入
     * str[2],str[3]-->16bit
	*/

	while(str[i] && str[i+1]){//两个字符都不为0时
		data = str[i] + (str[i+1]<<8);
		nor_unlock();//解锁
		nor_cmd(0x555,0xA0); //写命令
		nor_cmd(addr>>1,data);

		/* 等待烧写完成:读数据Q6，无变化时表示完成*/
		wait_ready(addr);
		i += 2;
		addr += 2;
	}
	/*IF write_data[i]!=0 write_data[j]=0
	 * 说明还有数据，此时：
	 * data =  write_data[i]+ (write_data[j]<<8);
	 */
	 /*IF write_data[i]==0 write_data[j]!=0
	 * 说明已经结束了，0是结束符‘\0’
	 * data =  write_data[i]+ (0<<8); 此时data =0
	 */
	 /*IF write_data[i]==0 write_data[j]==0
	 * 说明已经结束了，0是结束符‘\0’
	 * data =  write_data[i]+ (0<<8); 此时data =0
	 */
	 /*已上三种情况都需要再写一个数据
	  *为了方便和保险起见，无论是三种的哪一种
	  *都让 data = write_data[i]; 把结束符写进去
	  */
	//构造一个16bit的数据
	data = str[i];
	nor_unlock();
	nor_cmd(0x555,0xA0); //写命令
	nor_cmd(addr>>1,data);
	/* 等待烧写完成:读数据Q6，无变化时表示完成*/
	wait_ready(addr);
}

//读取数据
void read_nor_flash(void)
{
	int i,j;
	unsigned int addr,hex_addr;
	unsigned char c,str[16];
	volatile unsigned char *p;

	/* 获得地址 */
	printf("Enter the address to read:");
	addr = get_uint();
	p = (volatile unsigned char *)(addr + NOR_FLASH_BASE);//获取到地址上的数据
	hex_addr = addr;
	printf("Read Data:\r\n");
	printf("            00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n\r");
 	/* 长度固定为64 bytes */	
	for(i = 0; i < 4; i++){
		printf("0x%08x  ",hex_addr);
		//每行打印16个字符
		for(j = 0; j < 16; j++){
			c = *p++;//读取16个
			str[j] = c;//保存字符
			//先打印数值
			printf("%02x ",c);
		}
		printf(" | ");
		//后打印字符
		for(j = 0; j < 16; j++){
			if(str[j] < 0x20 || str[j] > 0x7e){//不可视字符,打印.
				printf(".");
			}
			else{
				printf("%c",str[j]);
			}
		}
		hex_addr+=16;//换行+16
		printf("\n\r");
	}
}





//nor_flash菜单选择
void nor_flash_menu(void)
{
	char c;
	while(1){
		printf("[s] Scan nor flash\r\n");
		printf("[e] Erase nor flash\r\n");
		printf("[w] Write nor flash\r\n");
		printf("[r] Read nor flash\r\n");
		printf("[q] Quit nor flash\r\n");
		printf("Enter selection:");

		c = uart0_getchar();
		printf("%c\r\n",c); //回显

		/* 打印菜单 */
		/* 1.识别nor flash
	   	 * 2.擦除nor flash 某个扇区
	   	 * 3.写数据至某个地址
	   	 * 4.读某个地址数据
		 */
		switch(c){
			case 'q':
			case 'Q':
				return;
			case 's':
			case 'S':
				scan_nor_flash(); //识别nor flash
				break;
			case 'e':
			case 'E':
				erase_nor_flash();//擦除nor flash 某个扇区
				break;
			case 'w':
			case 'W':
				write_nor_flash();//写数据至某个地址
				break;
			case 'r':
			case 'R':
				read_nor_flash(); //读某个地址数据
				break;
			default:
				break;
		}

	}

}


