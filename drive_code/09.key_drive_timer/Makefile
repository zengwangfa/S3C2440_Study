KERN_DIR = /work/system/linux-2.6.22.6  //依赖的内核目录,前提内核是编译好的

all:
	make -C $(KERN_DIR) M=`pwd` modules // M=`pwd`:指定当前目录
// make -C $(KERN_DIR) 表示将进入(KERN_DIR)目录,执行: make M=(当前目录) modules
// modules:要编译的目标文件

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= key_drv.o
//obj-m:内核模块文件，指将key_drv.o编译成key_drv.ko