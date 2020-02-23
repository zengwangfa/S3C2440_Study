
test:a.o b.o
	gcc -o test a.o b.o
	
a.o:a.c
	gcc -c -o a.o a.c
	
b.o:b.c
	gcc -c -o b.o b.c
	
#缺点:依赖的文件过多，就需要重复很多行