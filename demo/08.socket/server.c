#include <sys/types.h>       
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define SERVER_PORT 8899 
#define BACKLOG     10   //最大连接数
//#define SERVER_IP   "192.168.1.105"

/* socket 创建
 * bind		绑定
 * listen 监听
 * accept 建立
 * send   发送数据
 * recv   接收数据
 */
int main(int argc, char **argv)
{
	int iSocketServer;
	int iSocketClient;
	int iAddrLen;
	int iRet;
	
	struct sockaddr_in tSocketServerAddr;
	struct sockaddr_in tSocketClientAddr; //用于保存客户端的地址信息

	int iClientNum = -1;
	int RecvLen;
	unsigned char RecvBuff[1000];

	/* 1.创建 */
 	iSocketServer = socket(AF_INET, SOCK_STREAM, 0); //IPV4、TCP
	if(-1 == iSocketServer){
		printf("socket error\n");
		return -1;
	}

	tSocketServerAddr.sin_family      = AF_INET;
	tSocketServerAddr.sin_port        = htons(SERVER_PORT); //将端口号转换为网络字节序 16位
	
#ifdef SERVER_IP
	tSocketServerAddr.sin_addr.s_addr = inet_addr(SERVER_IP);//固定ip
#else
	tSocketServerAddr.sin_addr.s_addr = INADDR_ANY; //表示本机上所有的IP
#endif

	memset(tSocketServerAddr.sin_zero, 0, 8); //填充0 以保持与struct sockaddr同样大小

	/* 2.绑定 */
  iRet = bind(iSocketServer, (struct sockaddr *)&tSocketServerAddr, sizeof(struct sockaddr));
  if(-1 == iRet){
		printf("bind error\n");
		return -1;
  }
  
	/* 3.绑定 */
	iRet = listen(iSocketServer, BACKLOG);
  if(iRet < 0){
		printf("listen error\n");
		return -1;
  }

  while(1)
  {
		/* 4.连接 */
		iAddrLen = sizeof(struct sockaddr);
		iSocketClient = accept(iSocketServer, (struct sockaddr *)&tSocketClientAddr, &iAddrLen);
		if(iSocketClient != -1){
			iClientNum++;
			printf("get connet from client %d : %s\n", iClientNum, inet_ntoa(tSocketClientAddr.sin_addr)); //将网络ip转换为ascii
			
			if(!fork()){
				/* 子进程 */
				
				while(1){
					/* 5.接收客户端的数据 */
					RecvLen = recv(iSocketClient, RecvBuff , 999, 0);
					
					if(RecvLen <= 0){//接收出错
					
						close(iSocketClient);
						return -1;
					}
					else{
						printf("get msg from clinet %d : %s\n", iClientNum, RecvBuff);
					}
				}
			}
		}
  }
	/* 6.关闭服务器 */
  close(iSocketServer);
	return 0;
}


