
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

/* key_test
*/
int main(int argc,char **argv)
{
	int fd;
	int cnt = 0;
  char key_val;
	fd = open("/dev/buttons", O_RDWR);
	if(fd < 0){
		printf("can't open!\n\r");
	}
	/* ÅÐ¶ÏÊäÈë²ÎÊý */
	if(argc != 1){
		printf("Usage : \n");
		printf("%s \n",argv[0]);
		return -1;
	}
	
	while(1)
	{
		read(fd, &key_val, 1);
		printf("key_val = 0x%x\n", key_val);
	}

	return 0;
}
