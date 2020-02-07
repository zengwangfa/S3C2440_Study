
#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>


/* 分配/设置/注册一个platform_device */

/* 资源(用于修改寄存器) */
static struct resource s3c2440_led_resource[] = {
    [0] = {
        .start = 0x56000050, //led GPFCON起始地址
        .end   = 0x56000050 + 8 -1,//led GPFDAT起始地址
        .flags = IORESOURCE_MEM,//表示地址资源(貌似这个标准并不重要，只是用于索引)
    },
    [1] = {
        .start = 4,//哪一位开始(引脚) GPF4-GPF6
        .end   = 6,
        .flags = IORESOURCE_IRQ,//表示中断资源
    }

};

static void led_release(struct device *dev)
{
	printk("led_release\n");
}

static struct platform_device led_dev = {
    .name          = "s3c2440-led",//对应的platform_driver驱动的名字
    .id            = -1,//表示只有一个设备
    .num_resources = ARRAY_SIZE(s3c2440_led_resource),//资源数量,ARRAY_SIZE()函数:获取数量
    .resource      = s3c2440_led_resource,//资源数组led_resource
    .dev = {
			.release = led_release,//释放函数，必须向内核提供一个release函数,否则卸载时,内核找不到该函数会报错
    }
};

static int led_dev_init(void)
{
	platform_device_register(&led_dev);
	return 0;
}

static void led_dev_exit(void)
{
	platform_device_unregister(&led_dev);
}

module_init(led_dev_init);
module_exit(led_dev_exit);
MODULE_LICENSE("GPL");

