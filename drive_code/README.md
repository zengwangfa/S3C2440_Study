# 1.程序文件夹说明

| 序号 | 文件夹名 | 注解 | 内容 | 
| :---: | :--- | :--- | :--- |
| 01 | led_drive | 点亮LED驱动 | 学习字符驱动结构及流程 | 
| 02 | key_drive_by_query | 按键驱动 | 按键查询方式 |
| 03 | key_drive_by_irq | 按键驱动 | 按键中断方式，休眠与唤醒 | 
| 04 | key_drive_poll_select | poll机制 | 在一定时间内返回 | 
| 05 | key_drive_async | 异步通知 | 驱动提醒应用读取数据 | 
| 06 | key_drive_atomic_operation | 原子操作 | 同一时刻只有一个APP打开驱动 | 
| 07 | key_drive_semaphore | 信号量 | 同一时刻只有一个APP打开驱动 | 
| 08 | key_drive_block | 阻塞 | 同一时刻只有一个APP打开驱动 | 
| 09 | key_drive_timer | 定时器 | 定时器去除抖动 | 