## 1.编写USB驱动程序
> 内核中的USB总线驱动程序，当usb设备接入，会自动帮我们注册一个usb_new_device，因此我们只需要写一个usb_driver注册进去即可。

程序目标：将USB鼠标上的按键作为实体按键（左键->"L"，右键->“S”，滚轮按键->“Enter”）

- 1.分配input_dev结构体
- 2.设置按键类事件
- 3.注册
- 4.硬件相关操作

### 1.1 分配
- 1.分配input_dev结构体
    - .id_table 支持的设备
    - .probe 适配
    - disconnect 
```c
/* 1. 分配/设置usb_driver */
static struct usb_driver usbmouse_as_key_driver = {
    .name		    = "usbmouse_as_key_",
    .probe		  = usbmouse_as_key_probe,
    .disconnect	= usbmouse_as_key_disconnect,
    .id_table	  = usbmouse_as_key_id_table,
};
```

### 1.2 获取USB信息
可以通过接口函数，获取usb_dev结构体，从而获取到USB具体信息
```c
//一个USB设备中可能有多个逻辑设备，用interface来表示
static int usbmouse_as_key_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
    struct usb_device *dev = interface_to_usbdev(intf);//通过接口获取usb_dev结构体
    printk("found usbmouse\n");

    printk("bcdUSB = %x\n", dev->descriptor.bcdUSB);
    printk("VID    = 0x%x\n", dev->descriptor.idVendor);
    printk("PID    = 0x%x\n", dev->descriptor.idProduct);
}
```