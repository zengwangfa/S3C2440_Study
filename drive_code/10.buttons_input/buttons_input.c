/* 参考 linux-2.6.22.6\drivers\input\keyboard\gpio_keys.c */

#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/irq.h>

#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>

struct pin_desc{//按键描述结构体
	int irq;
	char *name;
	unsigned int pin;
	unsigned int mode;//触发方式
	unsigned int key_val;
};

struct pin_desc pins_desc[4] = {
	{IRQ_EINT0,  "S2", S3C2410_GPF0, IRQT_BOTHEDGE, KEY_L},
	{IRQ_EINT2,  "S3", S3C2410_GPF2, IRQT_BOTHEDGE, KEY_S},
	{IRQ_EINT11, "S4", S3C2410_GPG3, IRQT_BOTHEDGE, KEY_ENTER},
	{IRQ_EINT19, "S5", S3C2410_GPG11,IRQT_BOTHEDGE, KEY_LEFTSHIFT},
};

static struct input_dev *buttons_dev;
static struct pin_desc *irq_pd;//发生中断时的引脚描述
static struct timer_list buttons_timer;

/*
 * 用于修改定时器超时时间
*/
static irqreturn_t buttons_irq(int irq, void *dev_id)
{
	/* 10ms后启动定时器(即HZ/100) */
	irq_pd = (struct pin_desc *)dev_id;
	mod_timer(&buttons_timer, jiffies+HZ/100);//jiffies为系统时钟中断的累加值(1HZ = 100)

	return IRQ_RETVAL(IRQ_HANDLED);
}


static void buttons_timer_function(unsigned long data)
{
	struct pin_desc *pindesc = irq_pd;
	unsigned int pinval;
	
	if(!pindesc)//无按键中断，返回
		return;
	
	pinval = s3c2410_gpio_getpin(pindesc->pin);
	
	if(pinval){
		/* 松开 上报事件 0-松开,1-按下 */
		input_event(buttons_dev, EV_KEY, pindesc->key_val, 0);
		input_sync(buttons_dev);//上报同步事件
	}
	else{
		/* 按下 */
		input_event(buttons_dev, EV_KEY, pindesc->key_val, 1);
		input_sync(buttons_dev);
	}
	
}

static int buttons_init(void)
{
	int i;
	/* 1.分配 input_dev结构体 */
	buttons_dev = input_allocate_device();
		
	/* 2.设置 */
	/* 2.1 能产生哪类事件(按键类) */
	set_bit(EV_KEY, buttons_dev->evbit);
	set_bit(EV_REP, buttons_dev->evbit);//重复上报(即支持连按)
	
	/* 2.2 能产生这类事件里的哪些事件 (L,S,ENTER,LEFTSHIFT) */
	set_bit(KEY_L,buttons_dev->keybit);
	set_bit(KEY_S,buttons_dev->keybit);	
	set_bit(KEY_ENTER,buttons_dev->keybit);
	set_bit(KEY_LEFTSHIFT,buttons_dev->keybit);	
	
	/* 3.注册 */
	input_register_device(buttons_dev);
	
	/* 4.硬件相关操作 */
	init_timer(&buttons_timer);
	buttons_timer.function = buttons_timer_function;
	add_timer(&buttons_timer);
	
	for(i = 0; i < 4; i++){//注册中断
		request_irq(pins_desc[i].irq, buttons_irq, pins_desc[i].mode, pins_desc[i].name, &pins_desc[i]);
	}
	return 0;
}

static void buttons_exit(void)
{
	int i;
	for(i = 0; i < 4; i++){
		free_irq(pins_desc[i].irq, &pins_desc);
	}
	del_timer(&buttons_timer);
	input_unregister_device(buttons_dev);//卸载设备
	input_free_device(buttons_dev);//释放设备空间
}


module_init(buttons_init);

module_exit(buttons_exit);

MODULE_LICENSE("GPL");

