- 设置nor flash的访问时间 Tacc
	- 当Tacc数值变化，CPU读取nor上的数据与代码时的效率会不同

- 为了方便，使得`Addr、CS、OE`信号同时拉低使能，然后确保Tacc>=70ns，即可满足Nor Flash的时序
 

 #### 注意，该实验为`nor flash启动`