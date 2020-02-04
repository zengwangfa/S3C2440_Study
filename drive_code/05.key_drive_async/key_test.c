
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

 
int fd;
void signal_func(int signum)
{
	unsigned char key_val;
	read(fd, &key_val, 1);
	printf("key_val : 0x%x\n", key_val);

}


/* key_test
*/
int main(int argc,char **argv)
{
	int Oflags;

  signal(SIGIO, signal_func);//��ʾIO�ж�д

	fd = open("/dev/buttons", O_RDWR);
	if(fd < 0){
		printf("can't open!\n\r");
	}
	
	fcntl(fd, F_SETOWN, getpid()); //�����ںˣ�����˭

	Oflags = fcntl(fd, F_GETFL); 
	
	fcntl(fd, F_SETFL, Oflags | FASYNC); // �ı�fasync��ǣ����ջ���õ�������faync > fasync_helper����ʼ��/�ͷ�fasync_struct

	while(1)
	{
		sleep(1000);
	}
	return 0;
}