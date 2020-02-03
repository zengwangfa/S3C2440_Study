
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

 

/* key_test
*/
int main(int argc,char **argv)
{
	int fd;
	int ret;
	unsigned char key_val;
	
	fd = open("/dev/buttons", O_RDWR | O_NONBLOCK);
	if(fd < 0){
		printf("can't open!\n\r");
		return -1;
	}

	while(1)
	{
		ret = read(fd, &key_val, 1);
		printf("key_val : 0x%x, ret = %d\n", key_val, ret);
		sleep(5);
	}
	return 0;
}

