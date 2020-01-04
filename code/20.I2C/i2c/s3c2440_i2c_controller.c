#include "i2c_controller.h"
#include "../s3c2440_soc.h"
#include "../interrupt.h"
#include "../led.h"
#define WRITE 0
#define READ  1

static p_i2c_msg p_cur_msg;//当前传输的msg指针

int isLastData(void)
{
	if (p_cur_msg->cnt_transferred == p_cur_msg->len - 1)
		return 1;  /* ÕýÒª¿ªÊ¼´«Êä×îºóÒ»¸öÊý¾Ý */
	else 
		return 0;
}

void resume_iic_with_ack(void)
{
	unsigned int iiccon = IICCON;
	iiccon |= (1<<7); /* »ØÓ¦ACK */
	iiccon &= ~(1<<4); /* »Ö¸´IIC²Ù×÷ */
	IICCON =  iiccon;
}

void resume_iic_without_ack(void)
{
	unsigned int iiccon = IICCON;
	iiccon &= ~((1<<7) | (1<<4)); /* ²»»ØÓ¦ACK, »Ö¸´IIC²Ù×÷ */
	IICCON =  iiccon;
}

void i2c_irq(int irq)
{
    int index;
    /* 每传输完一个数据，将产生一个中断 */
    unsigned int iicstat = IICSTAT;//保存第一次中断的状态
    p_cur_msg->cnt_transferred++;

    /* 对于每次传输，第1个中断是“已经发出了设备地址” */
    if(p_cur_msg->flags == WRITE){ /* write */
        /* 对于第1个中断，是发出设备地址后产生的，需要判断是否有ACK信号
         * 有ACK：设备存在；
         * 无ACK：无设备，出错，结束传输
         */
        if(p_cur_msg->cnt_transferred == 0){/* 表示第一次中断 */
            if(iicstat & (1<<0)){/* no ack */ 
                IICSTAT = 0xd0;  // 停止传输
                /* 恢复I2C传输 */
                IICCON &= ~(1<<4);//清零pending bit
                p_cur_msg->err = -1;//无设备，错误状态
                delay(1000);//等待
                return;
            }
        }
        if(p_cur_msg->cnt_transferred < p_cur_msg->len){//未传输完毕
            IICDS = p_cur_msg->buf[p_cur_msg->cnt_transferred];
            /* 恢复I2C传输 */
            IICCON &= ~(1<<4);//清零pend bit
        }
        else{
            IICSTAT = 0xd0;  // 停止传输
            /* 恢复I2C传输 */
            IICCON &= ~(1<<4);//清零pending bit
            delay(1000);//等待
        }

         /* 对于其他中断，要继续发送下一个数据 */
    }


    else{ /* read */
        /* 对于第1个中断，是发出设备地址后产生的，需要判断是否有ACK信号
         * 有ACK：设备存在，恢复I2C传输，这样可以在下一个中断的得到第一个数据
         * 无ACK：无设备，出错，结束传输
         */


        if(p_cur_msg->cnt_transferred == 0){/* 表示第一次中断 */
            if(iicstat & (1<<0)){/* no ack */ 
                IICSTAT = 0x90;  // 停止传输
                /* 恢复I2C传输 */
                IICCON &= ~(1<<4);//清零pending bit
                p_cur_msg->err = -1;//无设备，错误状态
                delay(1000);//等待
                return;
            }
            else{/* ack */
				if (isLastData()){
					resume_iic_without_ack();
				}
				else{
					resume_iic_with_ack();
				}
				return;      
            }
        }
        /* 非第1个中断，表示得到一个新数据
         * 从IICDS读出、保存
        */
        else{
            if(p_cur_msg->cnt_transferred < p_cur_msg->len){//未传输完毕
                index = p_cur_msg->cnt_transferred - 1;
                p_cur_msg->buf[index] = IICDS;
				if (isLastData()){
					resume_iic_without_ack();
				}
				else{
					resume_iic_with_ack();
				}
            }  
            else{//传输完毕
                IICSTAT = 0x90;
                IICCON &= ~(1<<4);//清零pend bit
                delay(1000);//等待
            }  
        }
    }

}


int s3c2440_i2c_init(void)
{
    /* 设置为I2C引脚 */
    GPECON &= ~((3<<28) | (3<<30));
	GPECON |= ((2<<28) | (2<<30));
    /* [7]: ACK信号使能位. 1-enable
     * [6]: 时钟源 ：0: IICCLK = fPCLK /16 ，1: IICCLK = fPCLK /512
     * [5]: 中断使能位.1-enable
     * [4]: 中断等待标志.读出1时表示中断发送，写入0清除，并恢复I2C
     * [3:0]: Tx clock = IICCLK/(IICCON[3:0]+1).
     *
     * TX CLOKC = 100KHz = 50M / 16 / (IICCON[3:0]+1)，得出I2CCON[3:0] = 30
     */
    IICCON = (1<<7) | (0<<6) | (1<<5) | (30<<0);

    /* 注册中断处理函数 */
    register_irq(27,i2c_irq);
}


int do_master_tx(p_i2c_msg msg)
{
    p_cur_msg = msg;
    msg->cnt_transferred = -1;//已传输数据，先-1，因为发送的1位为地址，不是数据
    msg->err = 0;
    /* 设置寄存器，启动传输 */
    /* 1.配置为master tx mode */
    IICCON  |= (1<<7);
    /* 2.IIC总线数据输出使能 */
    IICSTAT |= (1<<4); 
    /* 3.把从设备地址写入IICDC */
    IICDS = ((msg->addr)<<1)|(WRITE<<0); //高7位表示设备地址,最低位0表示write标志
    /* 4.IICSTAT = 0xf0,数据即将被发送，导致中断产生 */
    IICSTAT = 0xf0;
    /* 后续的传输，由中断驱动 */

    /* 等待中断处理完毕*/
    while(!msg->err && (msg->cnt_transferred != msg->len));//等待传输指定字节数
    if(msg->err){
        return -1;
    }
    else{
        return 0;
    }
}

int do_master_rx(p_i2c_msg msg)
{
    p_cur_msg = msg;
    msg->cnt_transferred = -1;//已传输数据，先-1，因为发送的1位为地址，不是数据
    
    /* 设置寄存器，启动传输 */
    /* 1.配置为master tx mode */
    IICCON  |= (1<<7);
    /* 2.IIC总线数据输出使能 */
    IICSTAT |= (1<<4); 
    /* 3.把从设备地址写入IICDC */
    IICDS = ((msg->addr)<<1)|(READ<<0); //高7位表示设备地址,最低位1表示read标志

    /* 4.IICSTAT = 0xf0,数据即将被发送，导致中断产生 */
    IICSTAT = 0xb0;
    /* 后续的传输，由中断驱动 */

    /* 等待中断处理完毕*/
    while(msg->cnt_transferred != msg->len);//等待传输指定字节数
    if(msg->err){
        return -1;
    }
    else{
        return 0;
    }
}
/* 1读0写 */
int s3c2440_i2c_xfer(p_i2c_msg msgs,int num)
{
    int i;
    int err;
    for(i = 0; i < num; i++){
        if(msgs[i].flags == WRITE){
            err = do_master_tx(&msgs[i]);
        }
        else{
            err = do_master_rx(&msgs[i]);
        }
        if(err){
            return err;
        }
    }
    return 0;
}

static i2c_controller s3c2440_i2c_controller = {
    .name = "s3c2440",
    .init = s3c2440_i2c_init,
    .master_xfer = s3c2440_i2c_xfer,
};

void s3c2440_i2c_con_add(void)
{
    register_i2c_controller(&s3c2440_i2c_controller);
}
