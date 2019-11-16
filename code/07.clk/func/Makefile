#函数

##foreach
A = a b c
B = $(foreach f,$(A),$(f).o)
C = a b c d/

##filter
D = $(filter %/,$(C))   #
E = $(filter-out %/,$(C))

all:
	@echo B = $(B)