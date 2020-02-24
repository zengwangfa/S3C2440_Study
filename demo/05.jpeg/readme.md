### 1.1 libjpeg的使用
交叉编译libjpeg
```
$ tar xzf libjpeg-turbo-1.2.1.tar.gz
$ cd libjpeg-turbo-1.2.1
$ mkdir tmp

$ ./configure --prefix=/work/nfs_root/tmp/fs_mini_mdev_new/work/05.jpeg/libjpeg-turbo-1.2.1/tmp/ --host=arm-linux


$ make
$ make install 
```
### 1.2 交叉编译jpg2rgb.c
其中`-I`为指定头文件路径，`-L`为指定库文件路径
```c
arm-linux-gcc -o jpg2rgb jpg2rgb.c -I /work/nfs_root/tmp/fs_mini_mdev_new/work/05.jpeg/libjpeg-turbo-1.2.1/tmp/include -L /work/nfs_root/tmp/fs_mini_mdev_new/work/05.jpeg/libjpeg-turbo-1.2.1/tmp/lib -ljpeg
```

将动态库拷贝到文件系统的lib目录下
```c
cp jpg2rgb /work/nfs_root/tmp/fs_mini_mdev/

cp libjpeg-turbo-1.2.1/tmp/lib/*so* /work/nfs_root/tmp/fs_mini_mdev/lib/ -d
```


如果不想这么麻烦的指定头文件、库文件路径，可以将些复制到交叉编译工具链中：
- 1.把编译出的库文件复制
```c
cd /work/nfs_root/tmp/fs_mini_mdev_new/work/05.jpeg/libjpeg-turbo-1.2.1/tmp/lib

 cp * /work/tools/gcc-3.4.5-glibc-2.3.6/arm-linux/lib -d 


```
- 2.把编译出的头文件复制
```c
cd /work/nfs_root/tmp/fs_mini_mdev_new/work/05.jpeg/libjpeg-turbo-1.2.1/tmp/include

cp * /work/tools/gcc-3.4.5-glibc-2.3.6/arm-linux/include
cp * /work/tools/gcc-3.4.5-glibc-2.3.6/arm-linux/include 

```

最终只需要如下即可编译
```c
arm-linux-gcc -o jpg2rgb jpg2rgb.c -ljpeg
```
