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

static struct class *keydrv_class;
static struct class_device *keydrv_class_dev;

volatile unsigned long *gpfcon;
volatile unsigned long *gpfdat;

volatile unsigned long *gpgcon;
volatile unsigned long *gpgdat;

static int s3c24xx_keys_open(struct inode *inode, struct file *file)
{
	/* 配置GPF0,2为输入引脚 */
	*gpfcon &= ~((0x3<<(0*2)) | (0x3<<(2*2)));

	/* 配置GPG3,11为输入引脚 */
	*gpgcon &= ~((0x3<<(3*2)) | (0x3<<(11*2)));
	
	return 0;
}
static ssize_t s3c24xx_keys_read (struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	/* 返回4个引脚的电平 */
	unsigned char key_vals[4];
	int regval;

	if (size != sizeof(key_vals))
		return -EINVAL;

	/* 读GPF0,2 */
	regval = *gpfdat;
	key_vals[0] = (regval & (1<<0))>>0;
	key_vals[1] = (regval & (1<<2))>>2;
	
	/* 读GPG3,11 */
	regval = *gpgdat;
	key_vals[2] = (regval & (1<<3))>>3;
	key_vals[3] = (regval & (1<<11))>>11;

	copy_to_user(buf, key_vals, sizeof(key_vals));
	
	return sizeof(key_vals);
}

/* 这个结构是字符设备驱动程序的核心
 * 当应用程序操作设备文件时所调用的open、read、write等函数，
 * 最终会调用这个结构中指定的对应函数
 */
static struct file_operations s3c24xx_keys_fops = {
  .owner = THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
  .open  = s3c24xx_keys_open,      
	.read  = s3c24xx_keys_read,	   
};

static int major;
static int key_drv_init(void)
{
	major = register_chrdev(0, "key_drv", &s3c24xx_keys_fops);//注册
	
	/* 给内核提供 设备信息，用于自动创建设备节点 */
	keydrv_class = class_create(THIS_MODULE, "key_drv");
	keydrv_class_dev = class_device_create(keydrv_class, NULL, MKDEV(major, 0), NULL, "buttons");

	gpfcon = (volatile unsigned long *)ioremap(0x56000050, 16);//映射虚拟地址
	gpfdat = gpfcon + 1;

	gpgcon = (volatile unsigned long *)ioremap(0x56000060, 16);
	gpgdat = gpgcon + 1;
	return 0;
}

static void key_drv_exit(void)
{
	unregister_chrdev(major, "key_drv");//卸载
	
	class_device_unregister(keydrv_class_dev);//注册信息删除
	class_destroy(keydrv_class);

	iounmap(gpfcon);//解除映射
	iounmap(gpgcon);
}


module_init(key_drv_init);
module_exit(key_drv_exit);

MODULE_LICENSE("GPL");


