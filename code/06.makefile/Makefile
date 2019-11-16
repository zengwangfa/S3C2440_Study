#函数

##foreach
A = a b c
B = $(foreach f,$(A),$(f).o)
C = a b c d/

##filter
D = $(filter %/,$(C))     #取出符合 %/的值
E = $(filter-out %/,$(C)) #取出不符合 %/的值
files = $(wildcard *.c)    #取出符合格式的文件 
all:
	@echo B = $(B)
	@echo D = $(D)
	@echo E = $(E)
	@echo files = $(files)
