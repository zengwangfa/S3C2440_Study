
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

  signal(SIGIO, signal_func);//表示IO有读写

	fd = open("/dev/buttons", O_RDWR);
	if(fd < 0){
		printf("can't open!\n\r");
		return -1;
	}
	
	fcntl(fd, F_SETOWN, getpid()); //告诉内核，发给谁

	Oflags = fcntl(fd, F_GETFL); 
	
	fcntl(fd, F_SETFL, Oflags | FASYNC); // 改变fasync标记，最终会调用到驱动的faync > fasync_helper：初始化/释放fasync_struct

	while(1)
	{
		sleep(1000);
	}
	return 0;
}

