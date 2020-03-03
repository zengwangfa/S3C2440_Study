
/*
 * drivers\hid\usbhid\usbmouse.c
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb/input.h>
#include <linux/hid.h>

static struct usb_device_id usbmouse_as_key_id_table [] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_MOUSE) },
	//{USB_DEVICE(0x1234,0x5678)},
	{ }	/* Terminating entry */
};

//一个USB设备中可能有多个逻辑设备，用interface来表示
static int usbmouse_as_key_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);//通过接口获取usb_dev结构体
	printk("found usbmouse\n");

	printk("bcdUSB = 0x%x\n", dev->descriptor.bcdUSB);
	printk("VID    = 0x%x\n", dev->descriptor.idVendor);
	printk("PID    = 0x%x\n", dev->descriptor.idProduct);
	
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




