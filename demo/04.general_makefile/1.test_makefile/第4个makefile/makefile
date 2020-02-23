objs := a.o b.o

test:$(objs)
	gcc -o test $^
	
#生成存放依赖的空文件 .a.o.d 
dep_files := $(foreach f,$(objs),.$(f).d) #对objs内的内容变成.$(f).d
dep_files := $(wildcard $(dep_files)) #取出符合dep_files类型的文件 

ifneq ($(dep_files),)
  include $(dep_files)
endif

%.o:%.c
	gcc -Wp,-MD,.$@.d -c -o $@ $<  


clean:
	rm *.o test