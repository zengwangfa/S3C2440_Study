#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

static struct class *leddrv_class;
static struct class_device	*leddrv_class_dev;

volatile unsigned int  *gpfcon = NULL;
volatile unsigned int  *gpfdat = NULL;

static int s3c24xx_leds_open(struct inode *inode, struct file *file)
{
	//配置GPF4、5、6为输出模式
	*gpfcon &= ~((0x3)<<(4*2) | (0x3)<<(5*2) | (0x3)<<(6*2));
	*gpfcon |=  ((0x1)<<(4*2) | (0x1)<<(5*2) | (0x1)<<(6*2));
	return 0;
}

static ssize_t s3c24xx_leds_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{
	int val;
	copy_from_user(&val, buf, count);//将用户空间的值获取存在val
	if(1 == val){//点灯
		*gpfdat &= ~(7<<4);
	}
	else{//灭灯
		*gpfdat |= (7<<4);
	}
	return 0;
}

/* 这个结构是字符设备驱动程序的核心
 * 当应用程序操作设备文件时所调用的open、read、write等函数，
 * 最终会调用这个结构中指定的对应函数
 */
static struct file_operations s3c24xx_leds_fops = {
  .owner = THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
  .open  = s3c24xx_leds_open,      
	.write = s3c24xx_leds_write,	   
};

int major;
int led_drv_init(void)
{
	major = register_chrdev(0,"led_drv",&s3c24xx_leds_fops);//注册字符驱动程序，告诉内核
	
	leddrv_class = class_create(THIS_MODULE, "leddrv");//创建设备信息，自动创建设备节点

	leddrv_class_dev = class_device_create(leddrv_class, NULL, MKDEV(major, 0), NULL, "led"); /* /dev/led */

	gpfcon = (volatile unsigned long *)ioremap(0x56000050, 16);
	gpfdat = gpfcon + 1;
	return 0;
}

void led_drv_exit(void)
{
	unregister_chrdev(major,"led_drv");//卸载驱动
	
	class_device_unregister(leddrv_class_dev);
	class_destroy(leddrv_class);
	iounmap(gpfcon);
}


module_init(led_drv_init);
module_exit(led_drv_exit);

MODULE_LICENSE("GPL");