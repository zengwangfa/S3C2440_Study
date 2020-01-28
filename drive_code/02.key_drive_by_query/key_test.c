
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
	unsigned char key_vals[4];
	fd = open("/dev/buttons", O_RDWR);
	if(fd < 0){
		printf("can't open!\n\r");
	}
	/* 判断输入参数 */
	if(argc != 1){
		printf("Usage : \n");
		printf("%s \n",argv[0]);
		return -1;
	}
	
	while(1)
	{
		read(fd, key_vals, sizeof(key_vals));//当为0时，按下
		if(!key_vals[0] || !key_vals[1] || !key_vals[2] || !key_vals[3])
		{
			printf("%04d key pressed: %d %d %d %d\n",cnt++,key_vals[0], key_vals[1], key_vals[2], key_vals[3]);
		}
	}

	return 0;
}
