#include "i2c_controller.h"

#define I2C_CON_MAX_NUM  10

static p_i2c_controller p_i2c_controllers[I2C_CON_MAX_NUM];//存放所有的i2c控制器
static p_i2c_controller p_i2c_con_selected;//被选中的i2c控制器

/* 用一个i2c_controller数组存放各种不同芯片的操作结构体 */
void register_i2c_controller(p_i2c_controller p)
{
    int i;
    for(i = 0;i < I2C_CON_MAX_NUM; i++)
    {
        if(!p_i2c_controllers[i]){//如果为空，存放
            p_i2c_controllers[i] = p;
            return;
        }
    }
}


/* 根据名字选择某款i2c控制器 */
int select_i2c_controller(char *name)
{
    int i;
    for(i = 0;i < I2C_CON_MAX_NUM; i++)
    {
        /* 如果对应找到名字，则存放在全局变量p_i2c_con_selected */
        if(p_i2c_controllers[i] && !strcmp(p_i2c_controllers[i]->name,name)){
            p_i2c_con_selected = p_i2c_controllers[i];
            return 0;
        }
    }
    return -1;
}



/* 实现i2c_transter 接口函数 */
int i2c_transfer(p_i2c_msg msgs,int num)
{
    return p_i2c_con_selected->master_xfer(msgs,num);
}

void i2c_init(void)
{
    /* 注册i2c控制器 */
    s3c2440_i2c_con_add();
    /* 根据名字，选中自己需要的i2c控制器*/
    select_i2c_controller("s3c2440");
    /* 调用初始化函数 */
    p_i2c_con_selected->init();

}


