/*
 * 测试平台： ubuntu 16.04
 * 编译器： gcc 
 */
#include <stdio.h>
/*
由于在x86(32位机器)平台下，GCC编译器默认按4字节对齐，	
如：结构体4字节对齐,即结构体成员变量所在的内存地址是4的整数倍。

可以通过使用gcc中的__attribute__选项来设置指定的对齐大小。

1）：
__attribute__ ((packed))，让所作用的结构体取消在编译过程中的优化对齐，
按照实际占用字节数进行对齐。

2）：
__attribute((aligned (n)))，让所作用的结构体成员对齐在n字节边界上。
 如果结构体中有成员变量的字节长度大于n，
 则按照最大成员变量的字节长度来对齐。

*/
struct  person{
	char *name;
	int  age;
	char score;
	int  id;
};

struct  person1{
	char *name;
	int  age;
	char score;
	int  id;
}__attribute__ ((packed));

struct  person2{
	char *name;
	int  age;
	char score;
	int  id;
}__attribute((aligned (4)));

/*
 * 依据：x86平台，函数调用时参数传递是使用堆栈来实现的
 * 目的：将所有传入的参数打印出来
 */
int push_test(const char *format, ...)
{
	char *p = (char *)&format;
	struct person per;

	printf("arg0=%s\n",format);

	p += sizeof(char *);
	printf("arg1=%d\n",*(int *)p);

	p += sizeof(int);
	per = *((struct person *)p);
	printf("arg2:name=%s,age=%d,score=%c,id=%d\n",\
				per.name,per.age,per.score,per.id);

	p += sizeof(struct person);
	printf("arg3=%f\n",*(double *)p);
	return 0;
}

int main(void)
{
	struct person per = {"Ian",10,'A',075};
	//push_test("abcd");
	//push_test("abcd",1234);
	//push_test("abcd",1234,per); //打印结构体
	push_test("abcd",1234,per,3.14); //打印结构体
	return 0;
}