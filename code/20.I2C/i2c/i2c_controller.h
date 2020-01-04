#ifndef _I2C_CONTROLLER_H
#define _I2C_CONTROLLER_H

typedef struct i2c_msg{
    unsigned int addr; /* 7bits */
    int flags;/* 1读0写标志 */
    int len;
    int err;/* 错误状态 */
    int cnt_transferred; /* 已经传输的字节数 */
    unsigned char *buf;/* 存放数据的地址 */
}i2c_msg, *p_i2c_msg;


typedef struct i2c_controller{
    int (*init)(void);
    int (*master_xfer)(p_i2c_msg msgs,int num);
    char *name;
}i2c_controller, *p_i2c_controller;


int i2c_transfer(p_i2c_msg msgs,int num);
#endif /* _I2C_CONTROLLER_H */

