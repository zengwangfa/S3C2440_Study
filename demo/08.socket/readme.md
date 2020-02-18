### 1.编译
```
$ gcc -o server server.c
$ gcc -o client client.c
```

### 2.运行
先运行服务器
```
$ ./server
```

再运行客户端
```
$ ./client <server_ip>
```
eg:
```
$ ./client 127.0.0.1
```

> 注：<server_ip>参数为服务器上拥有的任意ip


### 3.设置服务器为固定ip
在server.c中，取消第13行的注释，并修改为指定ip
```c
//eg:
#define SERVER_IP   "192.168.1.105"
```

