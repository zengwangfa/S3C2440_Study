
/*
 * drivers\hid\usbhid\usbmouse.c
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb/input.h>
#include <linux/hid.h>

static struct input_dev *uk_dev;
static char *usb_buf;
static dma_addr_t usb_buf_phys;
static int len;
static struct urb *uk_urb;

static struct usb_device_id usbmouse_as_key_id_table [] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_MOUSE) },
	//{USB_DEVICE(0x1234,0x5678)},
	{ }	/* Terminating entry */
};

static void usbmouse_as_key_irq(struct urb *urb)
{
	int i;
	static int cnt = 0;
	printk("data cnt %d: ", ++cnt);
	for (i = 0; i < len; i++)
	{
		printk("%02x ", usb_buf[i]);
	}
	printk("\n");

	/* 重新提交urb */
	usb_submit_urb(uk_urb, GFP_KERNEL);
}


//一个USB设备中可能有多个逻辑设备，用interface来表示
static int usbmouse_as_key_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);//通过接口获取usb_dev结构体
	struct usb_host_interface *interface;
	struct usb_endpoint_descriptor *endpoint;
	int pipe;

	interface = intf->cur_altsetting;
	endpoint = &interface->endpoint[0].desc;

	/* 1. 分配一个input_dev */
	uk_dev = input_allocate_device();

	/* 2.设置 */
	/* 2.1 能产生哪类事件 */
	set_bit(EV_KEY, uk_dev->evbit);//按键类事件
	set_bit(EV_REP, uk_dev->evbit);//重复类事件
	/* 2.2 能产生哪些事件 */
	set_bit(KEY_L, uk_dev->keybit);
	set_bit(KEY_S, uk_dev->keybit);
	set_bit(KEY_ENTER, uk_dev->keybit);
	
	/* 3.注册 */
	input_register_device(uk_dev);

	/* 4.硬件相关操作 */
	/* 数据传输3要素: 源,目的,长度 */
	
	/* 源: USB设备的某个端点 */
	pipe = usb_rcvintpipe(dev, endpoint->bEndpointAddress);
	/* 长度: */
	len = endpoint->wMaxPacketSize;
	/* 使用"3要素" */
	/* 分配usb request block */
	uk_urb = usb_alloc_urb(0, GFP_KERNEL);
	/* 使用"3要素设置urb" */
	usb_fill_int_urb(uk_urb, dev, pipe, usb_buf, len, usbmouse_as_key_irq, NULL, endpoint->bInterval);//bInterval查询的频率
	uk_urb->transfer_dma = usb_buf_phys;
	uk_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	
	/* 使用URB */
	usb_submit_urb(uk_urb, GFP_KERNEL);

	return 0;
}

static void usbmouse_as_key_disconnect(struct usb_interface *intf)
{


	printk("disconnect usbmouse!\n");

}

/* 1. 分配/设置usb_driver */
static struct usb_driver usbmouse_as_key_driver = {
	.name		    = "usbmouse_as_key_",
	.probe		  = usbmouse_as_key_probe,
	.disconnect	= usbmouse_as_key_disconnect,
	.id_table	  = usbmouse_as_key_id_table,
};


static int usbmouse_as_key_init(void)
{
	usb_register(&usbmouse_as_key_driver);
	return 0;
}

static void usbmouse_as_key_exit(void)
{
	usb_deregister(&usbmouse_as_key_driver);
}


module_init(usbmouse_as_key_init);
module_exit(usbmouse_as_key_exit);

MODULE_LICENSE("GPL");




