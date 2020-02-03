#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <linux/poll.h>

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

/* 等待队列: 
 * 当没有按键被按下时，如果有进程调用s3c24xx_buttons_read函数，
 * 它将休眠
 */
static DECLARE_WAIT_QUEUE_HEAD(button_waitq);

/* 中断事件标志, 中断服务程序将它置1，s3c24xx_buttons_read将它清0 */
static volatile int ev_press = 0;

/* 键值: 按下时, 0x01, 0x02, 0x03, 0x04 */
/* 键值: 松开时, 0x81, 0x82, 0x83, 0x84 */
static unsigned char key_val;

struct pin_desc{
	unsigned int pin;
	unsigned int key_val;
};

struct pin_desc pins_desc[4] = {
	{S3C2410_GPF0, 0x01},
	{S3C2410_GPF2, 0x02},
	{S3C2410_GPG3, 0x03},
	{S3C2410_GPG11, 0x04},
};

static struct fasync_struct *button_async;
/* 
 * 确定键值
 * 定义4个按键，按下键值为: 0x01,0x02,0x03,0x04
 * 松开键值为: 0x81,0x82,0x83,0x84
*/
static irqreturn_t buttons_irq(int irq, void *dev_id)
{
	struct pin_desc *pindesc = (struct pin_desc *)dev_id;
	unsigned int pinval;
	
	pinval = s3c2410_gpio_getpin(pindesc->pin);

	if(pinval){
		/* 松开 */
		key_val = 0x80 | pindesc->key_val;
	}
	else{
		/* 按下 */
		key_val = pindesc->key_val;
	}

	ev_press = 1; //表示中断发生了
  /* 唤醒休眠的进程 */
  wake_up_interruptible(&button_waitq);

  kill_fasync(&button_async, SIGIO, POLL_IN);
  
	return IRQ_HANDLED;
}


static int s3c24xx_keys_open(struct inode *inode, struct file *file)
{
	/* 配置GPF0,2 GPG3,11为 外部中断模式 */
	request_irq(IRQ_EINT0,  buttons_irq, IRQT_BOTHEDGE, "S2", &pins_desc[0]);  
	request_irq(IRQ_EINT2,  buttons_irq, IRQT_BOTHEDGE, "S3", &pins_desc[1]);
	request_irq(IRQ_EINT11, buttons_irq, IRQT_BOTHEDGE, "S4", &pins_desc[2]);
	request_irq(IRQ_EINT19, buttons_irq, IRQT_BOTHEDGE, "S5", &pins_desc[3]);
	return 0;
}
static ssize_t s3c24xx_keys_read (struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	if(size != 1)
		return -EINVAL;
  /* 如果ev_press等于0，休眠 */
  wait_event_interruptible(button_waitq, ev_press);

	/* 如果有按键动作，返回键值 */
	copy_to_user(buf, &key_val, 1);
	ev_press = 0;//按键任务已经处理，清0进行休眠
	
	return 1; 
}

static int s3c24xx_keys_close(struct inode *inode, struct file *file)
{
	/* 释放中断，是根据中断号，以及设备ID */
	free_irq(IRQ_EINT0,  &pins_desc[0]);
	free_irq(IRQ_EINT2,  &pins_desc[1]);
	free_irq(IRQ_EINT11, &pins_desc[2]);	
	free_irq(IRQ_EINT19, &pins_desc[3]);
				
	return 0;
}

/* 等待一段时间直接返回 */
static unsigned int s3c24xx_keys_poll(struct file *file, struct poll_table_struct *wait)
{
	unsigned int mask = 0;
	poll_wait(file, &button_waitq, wait);
	if(ev_press){
		mask |= POLLIN;//普通或优先级带数据可读 标志
	}
	return mask;
}

static int s3c24xx_keys_fasync (int fd, struct file *filp, int on)
{
	printk("drive: s3c24xx_keys_fasync\n");
	return fasync_helper (fd, filp, on, &button_async);
}

/* 这个结构是字符设备驱动程序的核心
 * 当应用程序操作设备文件时所调用的open、read、write等函数，
 * 最终会调用这个结构中指定的对应函数
 */
static struct file_operations s3c24xx_keys_fops = {
  .owner   = THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
  .open    = s3c24xx_keys_open,      
	.read    = s3c24xx_keys_read,	 
	.release = s3c24xx_keys_close,
	.poll    = s3c24xx_keys_poll,
	.fasync  = s3c24xx_keys_fasync,
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


